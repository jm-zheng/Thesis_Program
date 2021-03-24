#include <iostream>
#include <math.h>
#include<fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;
const int nMTCD = 50000;
const int simRAo = 2000; // 1=10ms 20s
const int Backoff_D2D = 40; //D2D backoff
const int Backoff_RA = 20; //D2D backoff
const int D2D_cycle =8; //D2D_cycle 80ms =8 RAO
const int D2DRB_Pool = 24; //D2D resource block pool 25/50
const uint8_t MAX_nRequest_D2D = 10; //D2D MAX nRequest_D2D
const uint8_t MAX_nTransmit_RA = 10; //RA MAX nTransmit_RA
const uint8_t nSharePre = 6;    	 // sharepreamle 數量
const int beta_a = 3;
const int beta_b = 4;
const int beta_RAo = 1000; // 1=10ms

int RAtime[6][nMTCD] = {{0}}; //0: initiate RA time   1: first RA time    2: success RA time  3: RA retransmission times 4:group index 5:Access Delay
int D2D_total_cumulation_request[simRAo + 1] = { 0 };//每次RAO可以發起D2D的數量
int PreStatus[5][simRAo]={0}; //0: number of device initiate RA    1: emtpyPre    2: colliPre    3: successPre 4:not ULgrant
double PACB_share_premble=0.005 ;  // 用於SIB2 cycle broadcast for PACB of MTCD


int beta_nMTCD[beta_RAo] = { 0 }; // number of device initiate RA in beta_RAo;
double beta_proability[beta_RAo] = { 0 }; // proability of beta in RA
double beta_proability_ac[beta_RAo] = {0}; // ac_proability of beta in RA
class DEVICE //記錄設備資訊
{
public:
	uint8_t group=0;
	int MTCD_number =0; //紀錄第幾MTCD

	int RA_initate_RAO =0;	//The RAO that initiated the RA
	int RA_first_RAO=0;		//第一次進行RA的RAO
	int RA_success_RAO=-1;	//成功RA的RAO  -1:初始狀態 -2:失敗
	uint8_t nTransmit_RA=0 ; //number of transmission

	int D2D_initate_request_RAO=0; //which RAO initate D2D request ;
	int D2D_first_request_RAO=0; //which RAO first D2D request ;
	uint8_t nRequest_D2D=0;  //time of each MTCD initate D2D  次數

	double P_sharePre_access=0.005; // Proability of share preamble access
	uint8_t Preamble_number=0; //Which preamble to use

	string MTCD_RA_status = "D2D_RA";  // MTCD狀態 D2D_RA  |  在Share pre pool 使用 share preamble RA :Sharepre_RA_InsidePool  | 未釋放到Share pre pool: Sharepre_OutsidePool
};




//double RTran = 0;
int D = 0;
int D2Dcounter = { 0 };//每個groupRA設備計數   0不用
vector<DEVICE> devTabley[19];
int eachgrouppre[19] = { 0 };	// 每個groupRA設備計數   0不用
int eachgrouppre_return[19] = { 0 };	// recover前 沒有preamble可以分配 或是 沒有group需要preamble 就要回復上一次preamble分配
int eachgrouppre_return_2[19] = { 0 };  //  recover後 沒有preamble可以分配 或是 沒有group需要preamble 就要回復上一次preamble分配
int utilizationtpre[simRAo + 1] = { 0 };//每個RAOpreamble 使用狀況
int request_pre[19] = { 0 };//每個RAOpreamble 使用狀況
int unusepre_times[19] = { 0 };
int groupstatus[19] = { 0 };// 1:滿載的群 2:preamble可以重新分配的群  -1:pre被拿走後，突然又發起ra的群
int pbg[55] = { 0 };// preamble belong group資訊
int pbg_return[55] = { 0 };
int pbg_return_2[55] = { 0 };
int r = 0;//可重新配置的preamble數量
int prer = 0;  //暫存recover前的可重新配置的preamble數量
int D2Dtime[simRAo + 1] = { 0 };//每次RAO可以發起D2D的數量

int SuccessnMTCDcul[simRAo + 1] = { 0 };//成功設備累積
double droprate;
int totaldelay = 0; //成功設備delay時間加總
int SuccessnMTCD = 0;//成功設備加總
int AccessDelay[simRAo + 1] = { 0 };//每個dealy時間累積完成的設備
int total_prb = 0;
int average_prb = 0;
vector<DEVICE>MTCD_Table ;

int main()
{
	srand(2021);
    //初始化
		//srand((unsigned)time(NULL));
		///////generate beta distribution
	for (int a = 0; a < beta_RAo - 1; ++a)
	{
		beta_proability[a + 1] = 60 * pow(a + 1, beta_a - 1)*pow(beta_RAo - a - 1, beta_b - 1) / pow(beta_RAo, beta_a + beta_b - 1);
		beta_proability_ac[a + 1] = beta_proability_ac[a] + beta_proability[a + 1];
		//cout<<a << ":"<< beta_proability_ac[a + 1]<<endl;
	}
	beta_proability_ac[beta_RAo] = 1;

	for(int i=1; i<=nMTCD; i++)
	{
		double P =(double)rand()/(RAND_MAX+1); //0~32767/32768 compare beta proability  機率最大必須小於1
		DEVICE dev;
		dev.MTCD_number=i;
		int g = (rand()%16)+1; // Get the group index
		dev.group = g;
		for(int b=0; b<beta_RAo; b++)
		{
			if(P <  beta_proability_ac[b])
			{
				dev.D2D_first_request_RAO=b;
				dev.D2D_initate_request_RAO=b;
				break;
			}
		}
		MTCD_Table.push_back(dev);
	}/*

	int D2D_eachgroup_request_time[17]={0};
	int D2D_1th_request_EachCycle=0;  //在每個D2D週期的第一個request的RAO

	for( int Now_RAO=1; Now_RAO<=simRAo; Now_RAO++)
	{

		if(Now_RAO % D2D_cycle ==1 ) D2D_1th_request_EachCycle=Now_RAO; 	//紀錄在每個D2D週期的第一個request的RAO

		for(int i=1; i<=nMTCD;i++ )
		{
			// Confirm D2D initate request RAO &&  確認 MTCD status 是 D2D_RA &&  Whether the number of MTCD RA transmissions exceeds && whether MTCD success RA
			if(MTCD_Table[i].D2D_initate_request_RAO == Now_RAO   && MTCD_Table[i].MTCD_RA_status == "D2D_RA"&& MTCD_Table[i].nTransmit_RA < MAX_nTransmit_RA && MTCD_Table[i].RA_success_RAO==-1)
			{
				MTCD_Table[i].nRequest_D2D +=1;  						//MTCD 的D2D Request 次數+1
				int D2D_cycle_status = Now_RAO % D2D_cycle ;


				if(Now_RAO % D2D_cycle <=4 && D2D_eachgroup_request_time[MTCD_Table[i].group] < D2DRB_Pool) // D2D 沒有超過RB pool
				{

					D2D_eachgroup_request_time[MTCD_Table[i].group] +=1; 				// 在D2D週期內 組內的 request 次數+1

					//head allocate RAO of initate RA

					//紀錄head分配第一次RA的RAO
					if(MTCD_Table[i].RA_first_RAO == 0)MTCD_Table[i].RA_first_RAO = D2D_1th_request_EachCycle+((D2D_eachgroup_request_time[MTCD_Table[i].group]-1)/3)+D2D_cycle;
					MTCD_Table[i].RA_initate_RAO = ((D2D_eachgroup_request_time[MTCD_Table[i].group]-1)/3)+D2D_cycle;		//紀錄head分配每次RA的RAO ex: 1+0+8 =9

					//head分配要RA的pramble
					if(D2D_eachgroup_request_time[MTCD_Table[i].group]%3==0) MTCD_Table[i].Preamble_number = 3 * MTCD_Table[i].group;

					else MTCD_Table[i].Preamble_number = D2D_eachgroup_request_time[MTCD_Table[i].group]%3 * MTCD_Table[i].group;

				}
				else if(Now_RAO % D2D_cycle <=4 && D2D_eachgroup_request_time[MTCD_Table[i].group] < D2DRB_Pool)  //D2D request fail
				{
					if(MTCD_Table[i].nRequest_D2D < MAX_nRequest_D2D) MTCD_Table[i].D2D_initate_request_RAO = Now_RAO+4; //D2D backoff
					else
					{
							//使用share preamble 先丟到 SharePre_OutsidePool 在此次D2D週期結束才會釋放到 SharePre_RA_InsidePool
							MTCD_Table[i].MTCD_RA_status = "SharePre_OutsidePool";
							MTCD_Table[i].RA_initate_RAO = D2D_1th_request_EachCycle +8; // 在下一個D2D釋放出去
					}
				}

			}
			// 使用share preamble RA的設備
			else if(MTCD_Table[i].MTCD_RA_status == "SharePre_RA_InsidePool" && MTCD_Table[i].RA_initate_RAO == Now_RAO
					&& MTCD_Table[i].nTransmit_RA < MAX_nTransmit_RA && MTCD_Table[i].RA_success_RAO==-1 )
			{
				MTCD_Table[i].P_sharePre_access = (double)rand()/(RAND_MAX+1);
				if(MTCD_Table[i].P_sharePre_access < PACB_share_premble)
				{
					MTCD_Table[i].RA_initate_RAO=Now_RAO;
					MTCD_Table[i].Preamble_number = (rand() %nSharePre)+1 + 54-nSharePre;
				}
			}
		}

		if(Now_RAO % D2D_cycle ==0)     // 一個D2D週期結束後 釋放新的設備到share pr新的設備到share preamble pool
		{
			for(int x=1; x<=16;x++ )D2D_total_cumulation_request[Now_RAO]+=D2D_eachgroup_request_time[x];  //紀錄每個週期的D2D request
			for(int x=1; x<=16;x++ )D2D_eachgroup_request_time[x]=0; //清空 這次D2D週期的request
			for(int i=1; i<=nMTCD;i++ )
				if(MTCD_Table[i].MTCD_RA_status=="SharePre_OutsidePool" ) MTCD_Table[i].MTCD_RA_status ="SharePre_RA_InsidePool";
		}


		int each_RAO_Premble[55] = {0};

		for(int i; i<= nMTCD ; i++)
		{
			if(MTCD_Table[i].RA_initate_RAO == Now_RAO)
			{
				each_RAO_Premble[MTCD_Table[i].Preamble_number]+=1;
			}
		}








	}



/*
    for (int a = 0; a < nMTCD; a++) {
		double i = (double)rand() / (RAND_MAX + 1);
		RAtime[4][a] = (rand() % 21 )%18 +1;
        cout << a<<" : "<<RAtime[4][a]<<endl;

		for (int b = 0; b < beta_RAo; ++b)
			if (i < beta_proability_ac[b]) {
				RAtime[0][a] = b ;// 紀錄設備發起RA time(會改變)
				RAtime[1][a] = b ;//記錄設備第一次設備發起RA time
				++beta_nMTCD[b + 1];//記錄設備第一次設備發起RA time
				break;
			}
	}

    /////
	for (int a = 0; a < nMTCD; ++a)RAtime[2][a] = -1; //2: success RA time 初始化

    //// 模擬開始
	//int ppap = 0;
    for (int a = 1; a <= simRAo; a++) {

        if(a % 8 <=4)
        {
            for (int g = 1; g <= 18; ++g) ///下載之後又變上傳   歸零
				D2Dcounter[g] = 0;
        }
        else
        {
            for (int g = 1; g <= 18; ++g) ///下載之後又變上傳   歸零
				D2Dcounter[g] = 100;
        }

        for (int g = 1; g <= 18; ++g) {
			for (int b = 0; b < nMTCD; ++b) {
				if (RAtime[0][b] == a && RAtime[4][b] == g && (D2Dcounter[g] < D2DRBP))//0: initiate RA time   1: first RA time    2: success RA time  3: RA retransmission times 4:group index
				{
					D2Dcounter[g]++;//計算D2D request成功的設備

					DEVICE dev;
					dev.time = a;
					dev.num = b;
					dev.group = g;
					devTabley[g].push_back(dev);
					D++;
				}
				else if (RAtime[0][b] == a && RAtime[4][b] == g && (D2Dcounter[g] >= D2DRBP))
				{
					//file<<"設備號"<<b<<" "<<"發起時間"<<a<<" "<<"group"<<g<<" ";
					RAtime[0][b] = RAtime[0][b] +(Backoff / 10);//12個RAO D2D delay + backoff時間
					//if (RAtime[0][b] > 1100) { cout << a << endl; }
					RAtime[3][b]++;//�؂�++
					//file<<"重傳幾次"<< RAtime[3][b]<<endl;
				}
			}
		}


        for (int g = 1; g <= 18; ++g) {
			for (int p = 0; p < eachgrouppre[g]; p++) {
				if (devTabley[g].empty()){break;}

				RAtime[2][devTabley[g][0].num] = a + 5;
				utilizationtpre[a]++;
				request_pre[g]++;
				SuccessnMTCD++;
				devTabley[g].erase(devTabley[g].begin());
			}
		}







    }*/















    system("pause");
	return 0;




}