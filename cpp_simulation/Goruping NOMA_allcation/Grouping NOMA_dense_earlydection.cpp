#include<bits/stdc++.h>

using namespace std;

string directory_nMTCD ="150K";
const int nGroup =50; // group的數量
const int nMTCD =150000;
const int simRAo = 8800; // 1=10ms 20s
const int Backoff_D2D = 40; //D2D backoff
const int Backoff_RA = 20; //RA backoff
const int D2D_cycle =8; //D2D_cycle 80ms =8 RAO
const int SIB2_cycle =8; //SIB2_cycle 80ms =8 RAO
const int Preamble_format =8; //D2D_cycle 80ms =8 RAO
const int Threshold_PowerAllocation =12; //D2D request 的臨界值用於 NOMA 功率分配
const int D2DRB_Pool = 24; //D2D resource block pool 25/50
const int MAX_nRequest_D2D = 10; //D2D MAX nRequest_D2D
const int MAX_nTransmit_RA = 10; //RA MAX nTransmit_RA

const int beta_a = 3;
const int beta_b = 4;
const int beta_RAo = 1000; // 1=10ms

const int nSharePre = 4;    	 // sharepreamle 數量
double PACB_SharePremble=0 ;  // 用於SIB2 cycle broadcast for PACB of MTCD
double nMTCDinit_SharePremble[SIB2_cycle]={0}; //記錄一個SIB2週期面RAO有幾個MTCD使用Sharepreamble發起Msg1的數量  為了算出每個RAO的PACB
double PACB_RAO_SIB2cycle[SIB2_cycle]={0};      //記錄一個SIB2週期裡RAO PACB是多少                               為了算出PACB_SharePremble
double PACB_eachRAO[simRAo]={0};

double MTCD_RA_probility[nMTCD+1]={0}; //統一使用同一個RA set

int RAtime[6][nMTCD] = {{0}}; //0: initiate RA time   1: first RA time    2: success RA time  3: RA retransmission times 4:group index 5:Access Delay
int PreStatus[5][simRAo]={0}; //0: number of device initiate RA    1: emtpyPre    2: colliPre    3: successPre 4:not ULgrant

int D2D_total_cumulation_request[simRAo + 1] = { 0 };//每次RAO可以發起D2D的數量
int D2D_total_request_eachGroup[nGroup+1][simRAo + 1] = { 0 };
int Success_nMTCD =0;
int fail_nMTCD =0;

int finish_RAO =0;  //  RAO　of total MTCD finish


int beta_nMTCD[beta_RAo] = { 0 }; // number of device initiate RA in beta_RAo;
double beta_proability[beta_RAo] = { 0 }; // proability of beta in RA
double beta_proability_ac[beta_RAo] = {0}; // ac_proability of beta in RA
class DEVICE //記錄設備資訊
{
    public:
        int group=0;
        int MTCD_number =0; //紀錄第幾MTCD

        int RA_initate_RAO =-1;	//The RAO that initiated the RA 怕 第0次會一直紀錄PreStatus[0][0]
        int RA_first_RAO=0;		//第一次進行RA的RAO
        int RA_success_RAO=-1;	//成功RA的RAO  -1:初始狀態 -2:失敗
        int nTransmit_RA=0 ; //number of transmission

        int D2D_initate_request_RAO=0; //which RAO initate D2D request ;
        int D2D_first_request_RAO=-1; //which RAO first D2D request ;
        int D2D_request_allocation_index=-1;
        int nRequest_D2D=0;  //time of each MTCD initate D2D  次數
        int Power_level =-1;  //MTCD功率的等級 0 1 2

        double P_sharePre_access=0; // Proability of share preamble access
        int Preamble_number=0; //Which preamble to use

        string MTCD_RA_status = "D2D_init";  // MTCD狀態 D2D_init  |  在Share pre pool 使用 share preamble RA :Sharepre_RA_InsidePool  |
                                            //未釋放到Share pre pool的MTCD: Sharepre_OutsidePool | 壞到的設備 : Broken |Head分配可以發起RA的設備: RA_init
                                            //設備再進行RA程序: RACH

};




/*//double RTran = 0;
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
*/
int Success_nMTCD_cumulation_EachRAO[simRAo] = { 0 };//成功設備累積
int Successn_nMTCD_EachRAO [simRAo] ={0}; //each slot 的成功設備

double droprate;
int totalMTCD_Access_delay = 0; //成功設備delay時間加總
double Collide_probility_cumulation=0;


int AccessDelay[simRAo + 1] = { 0 };//每個dealy時間累積完成的設備
int total_D2D_nRequest_cumulation = 0;
int total_RA_nTransmission_cumulation = 0;
vector<DEVICE> MTCD_Table ;

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

    //-------RA 機率統一------------------------
    fstream file_RA_probility;
    file_RA_probility.open("..\\STD\\RA_probility\\"+directory_nMTCD+"\\RA_probility.csv" , fstream:: in);
    if (file_RA_probility.is_open())
	{
       // cout <<"XDD";
        string str1;
        int x=1;
        while(file_RA_probility>>str1)
        {
            MTCD_RA_probility[x]=stod(str1);
            x++;
        }
    }
    file_RA_probility.close();
    //-------------------

//-------分配each MTCD D2D first initate---------------------------------------------------------------------------
	for(int i=1; i<=nMTCD; i++)  // 只有這裡是要i=1 因為配合 MTCD編號
	{

		//double P =(double)rand()/(RAND_MAX+1); //0~32767/32768 compare beta proability  機率最大必須小於1
        DEVICE dev;
        dev.MTCD_number=i;
        int g = ( rand()%(nGroup+10)); // Get the group index
        if(g >49)
        {
            if(g >=55 ){g = (g%55)+26; }
            else  {g = ((g%nGroup)+1);}
        }
        else if(g<=49) {g = g+1;}


        dev.group = g;
        for(int b=0; b<beta_RAo; b++)
        {
            if(MTCD_RA_probility[i] <  beta_proability_ac[b])
            {
                //cout <<"b:"<<b<<endl;
                dev.D2D_first_request_RAO=b;
                dev.D2D_initate_request_RAO=b;
                break;
            }
        }
        MTCD_Table.push_back(dev);
	}
    // cout <<MTCD_Table.size();

    //   fstream nMTCD_file ;

    //     nMTCD_file.open(directory_nMTCD+"\\RAtime.csv", fstream::out);
    //     if (nMTCD_file.is_open())
    //     {
    //         nMTCD_file <<"MTCD_number,group,D2D_first_request_RAO,D2D_initate_request_RAO,nRequest_D2D,";
    //         nMTCD_file <<"RA_first_RAO,RA_initate_RAO,RA_success_RAO,nTransmit_RA,Preamble_number,MTCD_RA_status "<<endl ;

    //         for(int i=0;i<nMTCD;i++)
    //         {
    //             nMTCD_file <<MTCD_Table[i].MTCD_number<<","<<MTCD_Table[i].group<<","<<MTCD_Table[i].D2D_first_request_RAO<<","<<MTCD_Table[i].D2D_initate_request_RAO<<",";
    //             nMTCD_file <<MTCD_Table[i].nRequest_D2D<<","<<MTCD_Table[i].RA_first_RAO<<","<<MTCD_Table[i].RA_initate_RAO<<","<<MTCD_Table[i].RA_success_RAO<<",";
    //             nMTCD_file <<MTCD_Table[i].nTransmit_RA<<","<<MTCD_Table[i].Preamble_number<<","<<MTCD_Table[i].MTCD_RA_status<<","<<endl;
    //         }
    //     }
    //     nMTCD_file.close();



//-------------------------------------------------------------------------------
	int D2D_eachgroup_request_time[nGroup+1]={0};
	int D2D_1th_request_EachCycle=0;  //在每個D2D週期的第一個request的RAO

	for( int Now_RAO=0; Now_RAO<simRAo; Now_RAO++)
	{
        D2D_total_request_eachGroup[0][Now_RAO] = Now_RAO; //紀錄file D2D Request的RAO
		if(Now_RAO % SIB2_cycle ==0 )
        {
            PACB_SharePremble =0;

            //--------------算出SIB週期RAO裡的PACB是多少-----------------------------------------------------
            for( int x=0 ; x<SIB2_cycle ; x++)
            {
                if(nMTCDinit_SharePremble[x] >nSharePre) PACB_RAO_SIB2cycle[x] = nSharePre / nMTCDinit_SharePremble[x];
                else PACB_RAO_SIB2cycle[x] =1;
            }

            //--------------累加SIB週期RAO裡的PACB----------------------------------------------------
            for( int x=0 ; x<SIB2_cycle ; x++)
            {
                PACB_SharePremble+=PACB_RAO_SIB2cycle[x];
                nMTCDinit_SharePremble[x]=0;                //清空SIB2週期紀錄的設備數量-
            }
            PACB_SharePremble = PACB_SharePremble /SIB2_cycle;
            PACB_SharePremble =PACB_SharePremble / D2D_cycle;  //算出PACB後再除於D2D_cycle，讓設備可以平均一點發起
        }
        PACB_eachRAO[Now_RAO] =PACB_SharePremble;  //一個SIB週期更新一次  做紀錄

        if(Now_RAO % D2D_cycle ==0 ) { D2D_1th_request_EachCycle=Now_RAO; } 	//紀錄在每個D2D週期的第一個request的RAO



         //------------MTCD for begin----------------------######
		for(int i=0; i<nMTCD;i++ )
		{
			// Confirm D2D initate request RAO &&  確認 MTCD status 是 D2D_RA &&  Whether the number of MTCD RA transmissions exceeds && whether MTCD success RA
			if(MTCD_Table[i].D2D_initate_request_RAO == Now_RAO  && MTCD_Table.at(i).MTCD_RA_status == "D2D_init" && MTCD_Table[i].nTransmit_RA < MAX_nTransmit_RA )
			{
				MTCD_Table.at(i).nRequest_D2D +=1;  						//MTCD 的D2D Request 次數+1
                D2D_total_request_eachGroup[MTCD_Table.at(i).group][Now_RAO] +=1;  //記錄D2D各組的Request次數，為了輸出檔案用的
				if((Now_RAO % D2D_cycle) <4 && D2D_eachgroup_request_time[MTCD_Table[i].group] < D2DRB_Pool ) // D2D 沒有超過RB pool
				{
                    MTCD_Table.at(i).D2D_request_allocation_index= D2D_eachgroup_request_time[MTCD_Table.at(i).group];
                    D2D_eachgroup_request_time[MTCD_Table.at(i).group] +=1; 				// 在D2D週期內 組內的 request 次數+1
                    MTCD_Table.at(i).MTCD_RA_status = "RA_init";
					//head allocate RAO of initate RA

					//紀錄head分配第一次RA的RAO
					/*if(MTCD_Table[i].RA_first_RAO == 0)MTCD_Table[i].RA_first_RAO = D2D_1th_request_EachCycle + ((D2D_eachgroup_request_time[MTCD_Table[i].group]-1)/3) + D2D_cycle;
					MTCD_Table[i].RA_initate_RAO = D2D_1th_request_EachCycle + ((D2D_eachgroup_request_time[MTCD_Table[i].group]-1)/3) + D2D_cycle;		//紀錄head分配每次RA的RAO ex: 0+1+8 =9 下次D2D週期第2個RAO發起

					//head分配要RA的pramble
					if(D2D_eachgroup_request_time[MTCD_Table[i].group]%3==0) MTCD_Table[i].Preamble_number = 3 * MTCD_Table[i].group;

					else MTCD_Table[i].Preamble_number =  3* MTCD_Table[i].group-(3-D2D_eachgroup_request_time[MTCD_Table[i].group]%3);*/

				}
				else //if(Now_RAO % D2D_cycle >=4 && D2D_eachgroup_request_time[MTCD_Table[i].group] > D2DRB_Pool)  //D2D request fail
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
			if(MTCD_Table[i].MTCD_RA_status == "SharePre_RA_InsidePool" && MTCD_Table[i].RA_initate_RAO == Now_RAO&& MTCD_Table[i].nTransmit_RA < MAX_nTransmit_RA  )
			{
				MTCD_Table[i].P_sharePre_access = (double)rand()/(RAND_MAX+1);
				if(MTCD_Table[i].P_sharePre_access < PACB_SharePremble)
				{
                    //MTCD_Table[i].MTCD_RA_status = "D2D_RA";
                    if(MTCD_Table.at(i).RA_first_RAO == 0){MTCD_Table.at(i).RA_first_RAO = Now_RAO;}    //有可能設備第一次使用的是share preamle access
					MTCD_Table[i].RA_initate_RAO=Now_RAO;
					MTCD_Table[i].Preamble_number = (rand() %nSharePre)+1 + 54-nSharePre;  //使用哪個SharePreamble發起RA
                    nMTCDinit_SharePremble[Now_RAO % SIB2_cycle]+=1;   //記錄這個RAO使用sharepreamble的MTCD數量累加
				}
                else
                {
                    MTCD_Table[i].RA_initate_RAO = Now_RAO+1;
                }
			}
		}
        //--------------------------------------------------------------------
        //head allocation RAO Preamble Power_levle
        if(Now_RAO % D2D_cycle ==4 )
        {
            for(int i=0; i<nMTCD ; i++ )
            {
                if(MTCD_Table.at(i).MTCD_RA_status =="RA_init" && MTCD_Table.at(i).nTransmit_RA < 10)
                {
                    //-----------Grouping NOMA--------------------------------------------------------------------------------------------
                    MTCD_Table.at(i).MTCD_RA_status ="RACH";
                    if(MTCD_Table.at(i).group <26) //組別小於26
                    {
                        if(D2D_eachgroup_request_time[MTCD_Table.at(i).group] < D2D_cycle)  //D2D_cycle次數
                        {
                            //紀錄head分配第一次RA的RAO
                            if(MTCD_Table.at(i).RA_first_RAO == 0){MTCD_Table.at(i).RA_first_RAO = D2D_1th_request_EachCycle + MTCD_Table.at(i).D2D_request_allocation_index + D2D_cycle;}
                            MTCD_Table.at(i).RA_initate_RAO = D2D_1th_request_EachCycle + MTCD_Table.at(i).D2D_request_allocation_index + D2D_cycle;	//紀錄head分配每次RA的RAO ex: 0+(total request-1)1+8 =9 下次D2D週期第2個RAO發起
                            MTCD_Table.at(i).Preamble_number = MTCD_Table.at(i).group;
                            MTCD_Table.at(i).Power_level =0;
                        }
                        else  //大於D2D_cycle次數
                        {
                            if(MTCD_Table.at(i).D2D_request_allocation_index< Threshold_PowerAllocation )  //在index 16 或19的演算法
                            {
                                if(MTCD_Table.at(i).RA_first_RAO == 0){MTCD_Table.at(i).RA_first_RAO = D2D_1th_request_EachCycle + (MTCD_Table.at(i).D2D_request_allocation_index %4) + D2D_cycle;}
                                    MTCD_Table.at(i).RA_initate_RAO = D2D_1th_request_EachCycle +(MTCD_Table.at(i).D2D_request_allocation_index %4) + D2D_cycle;	//紀錄head分配每次RA的RAO ex: 0+(total request % 4)1+8 =9 下次D2D週期第2個RAO發起
                                    MTCD_Table.at(i).Preamble_number = MTCD_Table.at(i).group;
                                    MTCD_Table.at(i).Power_level =(MTCD_Table.at(i).D2D_request_allocation_index/4);
                            }
                            else
                            {
                                    if(MTCD_Table.at(i).RA_first_RAO == 0){MTCD_Table.at(i).RA_first_RAO = D2D_1th_request_EachCycle + ((MTCD_Table.at(i).D2D_request_allocation_index%Threshold_PowerAllocation%4)+4) + D2D_cycle;}
                                    MTCD_Table.at(i).RA_initate_RAO = D2D_1th_request_EachCycle +((MTCD_Table.at(i).D2D_request_allocation_index % Threshold_PowerAllocation%4)+4) + D2D_cycle;	//紀錄head分配每次RA的RAO ex: 0+(total request %4 + 4)1+8 =9 下次D2D週期第2個RAO發起
                                    MTCD_Table.at(i).Preamble_number = MTCD_Table.at(i).group;
                                    MTCD_Table.at(i).Power_level =((MTCD_Table.at(i).D2D_request_allocation_index % Threshold_PowerAllocation)/4);
                            }
                        }

                    }
                    else //組別大於26
                    {
                        if(D2D_eachgroup_request_time[MTCD_Table.at(i).group] < D2D_cycle)  //D2D_cycle次數
                        {
                            //紀錄head分配第一次RA的RAO
                            if(MTCD_Table.at(i).RA_first_RAO == 0){MTCD_Table.at(i).RA_first_RAO = D2D_1th_request_EachCycle + (D2D_cycle -1 - MTCD_Table.at(i).D2D_request_allocation_index ) + D2D_cycle;}  //從26group開始從D2D週期的最後一個RA開始分配
                            MTCD_Table.at(i).RA_initate_RAO = MTCD_Table.at(i).RA_first_RAO = D2D_1th_request_EachCycle + (D2D_cycle -1 - MTCD_Table.at(i).D2D_request_allocation_index ) + D2D_cycle;	//紀錄head分配每次RA的RAO ex: 0+(total request-1)1+8 =9 下次D2D週期第2個RAO發起
                            MTCD_Table.at(i).Preamble_number = MTCD_Table.at(i).group;
                            MTCD_Table.at(i).Power_level =0;

                        }
                        else  //大於D2D_cycle次數
                        {
                            if(MTCD_Table.at(i).D2D_request_allocation_index < Threshold_PowerAllocation )  //在index 16 或19的演算法
                            {
                                if(MTCD_Table.at(i).RA_first_RAO == 0){MTCD_Table.at(i).RA_first_RAO = D2D_1th_request_EachCycle + D2D_cycle -1 -(MTCD_Table.at(i).D2D_request_allocation_index%4) + D2D_cycle;}  // D2D週期起始RAO + (從第7個RAO)D2D週期的最後一個RA開始分配 + 下個D2D週期的時候發
                                    MTCD_Table.at(i).RA_initate_RAO = D2D_1th_request_EachCycle + (D2D_cycle -1 - MTCD_Table.at(i).D2D_request_allocation_index%4) + D2D_cycle;	//紀錄head分配每次RA的RAO ex: 0+(total request % 4)1+8 =9 下次D2D週期第2個RAO發起
                                    MTCD_Table.at(i).Preamble_number = MTCD_Table.at(i).group;
                                    MTCD_Table.at(i).Power_level =(MTCD_Table.at(i).D2D_request_allocation_index /4);

                            }
                            else
                            {
                                    if(MTCD_Table.at(i).RA_first_RAO == 0){MTCD_Table.at(i).RA_first_RAO = D2D_1th_request_EachCycle + (D2D_cycle -5 -(MTCD_Table.at(i).D2D_request_allocation_index %Threshold_PowerAllocation)%4) + D2D_cycle;} // D2D週期起始RAO + (從第3個RAO開始)D2D週期的最後一個RA開始分配 + 下個D2D週期的時候發
                                    MTCD_Table.at(i).RA_initate_RAO = D2D_1th_request_EachCycle + (D2D_cycle -5 -(MTCD_Table.at(i).D2D_request_allocation_index %Threshold_PowerAllocation)%4) + D2D_cycle;	//紀錄head分配每次RA的RAO ex: 0+(total request %4 + 4)1+8 =9 下次D2D週期第2個RAO發起
                                    MTCD_Table.at(i).Preamble_number = MTCD_Table.at(i).group;
                                    MTCD_Table.at(i).Power_level =((MTCD_Table.at(i).D2D_request_allocation_index %Threshold_PowerAllocation)/4);
                            }
                        }
                    }
                }
            }
        }


        //------------MTCD foe END----------------------######
        //------------------------------紀錄每次D2D的狀況-----------------------------------------------------------------------------------------------------

            for(int x=1; x<=nGroup;x++ )
            {
                //D2D_total_request_eachGroup[x][Now_RAO] =D2D_eachgroup_request_time[x];  //紀錄每個週期的D2D request，移到上面207
                D2D_total_cumulation_request[Now_RAO] += D2D_total_request_eachGroup[x][Now_RAO];
                //D2D_request_file << D2D_total_request_eachGroup[x][Now_RAO] <<",";

            }
            //D2D_request_file<<D2D_total_cumulation_request[Now_RAO]<<endl;
        //----------紀錄END------------------------------------------------------------------------

		if(Now_RAO % D2D_cycle ==7)     // 一個D2D週期結束後 釋放新的設備到share pr新的設備到share preamble pool
		{
			for(int x=1; x<=nGroup;x++ )D2D_eachgroup_request_time[x]=0; //清空 這次D2D週期的request
			for(int i=0; i<nMTCD;i++ )
				if(MTCD_Table[i].MTCD_RA_status=="SharePre_OutsidePool" )
                {
                    MTCD_Table[i].MTCD_RA_status ="SharePre_RA_InsidePool";
                    MTCD_Table[i].RA_initate_RAO =Now_RAO+1;
                }
		}

//----------------分配grant-----------------------------------------------------------------------------------------------------------

        int each_RAO_Premble[55] = {0};
        // cout << "RAO:"<<Now_RAO<<endl;
		for(int i=0; i< nMTCD ; i++)
		{
			if(MTCD_Table[i].RA_initate_RAO == Now_RAO && MTCD_Table[i].nTransmit_RA < MAX_nTransmit_RA )
			{
				each_RAO_Premble[MTCD_Table[i].Preamble_number]+=1;
                PreStatus[0][Now_RAO]+=1;
			}
		}

		int number_grant=30 ,used_Pre=1 ;    // grant 30個限制 因為used_Pre從1開始 //   used_pre:總共有幾個pre發送
        vector<int> eachRAOPre_transmit_shuffle ={0};  //eachRAOPre_transmit_shuffle :洗牌過後的Pre的Preamble
        vector<int> Preamble_load3 , Preamble_load2 ,Preamble_load1; // Preamble_load3:1個Preamble有3個用 Preamble_load2:1個Preamble有2個用  Preamble_load1:1個Preamble有1個用
        for(int c=1 ; c<55 ; c++)
        {
            if(each_RAO_Premble[c] != 0)
			{
                if(c > 50 && each_RAO_Premble[c]==1) eachRAOPre_transmit_shuffle.push_back(c);
                else if( c <= 50 )
                {
                    if(each_RAO_Premble[c] == 3) Preamble_load3.push_back(c);
                    else if(each_RAO_Premble[c] == 2) Preamble_load2.push_back(c);
				    else if (each_RAO_Premble[c] == 1)Preamble_load1.push_back(c);
                }


 				used_Pre++;
			}
        }

        /*cout <<"load1"<<endl;
        for(int i=0 ;i<Preamble_load1.size(); i++) cout<<i<<" : "<<Preamble_load1.at(i) << endl;
        cout <<"load2"<<endl;
        for(int i=0 ;i<Preamble_load2.size(); i++) cout<<i<<" : "<<Preamble_load2.at(i) << endl;
        cout <<"load3"<<endl;
        for(int i=0 ;i<Preamble_load3.size(); i++) cout<<i<<" : "<<Preamble_load3.at(i) << endl;
        cout<<endl<<"used_Pre:"<<used_Pre<<endl;*/

        shuffle (Preamble_load1.begin(), Preamble_load1.end(), default_random_engine(2021));
        shuffle (Preamble_load2.begin(), Preamble_load2.end(), default_random_engine(2021));
        shuffle (Preamble_load3.begin(), Preamble_load3.end(), default_random_engine(2021));


        //cout <<"load3"<<endl;
        for(int i=0 ;i<Preamble_load3.size(); i++) {
            //cout<<i<<" : "<<Preamble_load3[i] << endl;
            eachRAOPre_transmit_shuffle.push_back(Preamble_load3[i]);
        }
        //cout <<"load2"<<endl;
        for(int i=0 ;i<Preamble_load2.size(); i++) {
            //cout<<i<<" : "<<Preamble_load2[i] << endl;
            eachRAOPre_transmit_shuffle.push_back(Preamble_load2[i]);
        }
        //cout <<"load1"<<endl;
        for(int i=0 ;i<Preamble_load1.size(); i++)
        {
            //cout<<i<<" : "<<Preamble_load1[i] << endl;
            eachRAOPre_transmit_shuffle.push_back(Preamble_load1[i]);
        }

        //cout <<"eachRAOPre_transmit_shuffle"<<endl;
        /*for(int i=0 ;i<55; i++) {
            cout<<i<<" : "<<eachRAOPre_transmit_shuffle[i] << endl;
        }*/


		 if(used_Pre>number_grant) {used_Pre=number_grant;}




//--------確認發起RA後的狀態----------------------------------------------------------------------------------------
        vector<int> collision_Share_Preamble={51,52,53,54};  //每個RAO碰撞的Sharepmble 為了算出Collision
        vector<int>::iterator collision_Share_Preamble_it;   //iterator of collision_Share_Preamble
        for(int each_RAO_Pre_index=1 ;each_RAO_Pre_index<55 ;each_RAO_Pre_index++)
        {
            if(each_RAO_Premble[each_RAO_Pre_index] ==0) PreStatus[1][Now_RAO]+=1;
            else
            {
                for(int i=0; i<nMTCD ; i++)
                {
                    if(MTCD_Table[i].RA_initate_RAO == Now_RAO && MTCD_Table[i].Preamble_number == each_RAO_Pre_index )
                    {
                        MTCD_Table[i].nTransmit_RA +=1 ;
                        if(each_RAO_Premble[each_RAO_Pre_index] > 1 && MTCD_Table[i].Preamble_number> nGroup)  //如果share preamble發生碰撞 就 backoff
                        {
                            collision_Share_Preamble_it = find(collision_Share_Preamble.begin(),collision_Share_Preamble.end(),MTCD_Table[i].Preamble_number);
                            if( collision_Share_Preamble_it != collision_Share_Preamble.end()) //只要那個sharepreanle碰撞
                            {
                                collision_Share_Preamble.erase(collision_Share_Preamble_it); //刪除這次collision_Share_Preamble list中已經出現過碰撞ShearPreamble
                                 PreStatus[2][Now_RAO] += 1;           //collision +1;
                            }
                            //cout <<Now_RAO <<"collision_Share_Preamble:"<<collision_Share_Preamble.size()<<endl;

                            if(MTCD_Table[i].nTransmit_RA<10)
                            {
                                MTCD_Table[i].D2D_initate_request_RAO = Now_RAO +(Backoff_RA / 10);
                                MTCD_Table[i].MTCD_RA_status = "D2D_init";
                            }
                            else
                            {
                                fail_nMTCD +=1;
                                MTCD_Table.at(i).nTransmit_RA +=1 ;//區隔成功跟失敗的設備重傳次數
                                MTCD_Table[i].MTCD_RA_status = "Broken";
                            }
                        }
                        else if (each_RAO_Premble[each_RAO_Pre_index] <= 3 && MTCD_Table[i].Preamble_number <= nGroup)  //Group裡面分配成功的
                        {
                            bool grant_check_index =0;

                            for(int x=1 ; x<=used_Pre;x++ )
                            {
                                //  cout<<"Preamble:"<<MTCD_Table[i].Preamble_number<<"  vs  " <<eachRAOPre_transmit_shuffle[x]<<endl;
                                if (MTCD_Table[i].Preamble_number == eachRAOPre_transmit_shuffle[x] )
                                {
                                    grant_check_index =1;

                                    Success_nMTCD +=1;
                                    Successn_nMTCD_EachRAO[Now_RAO] +=1;   //Msg3 成功傳送
                                    MTCD_Table[i].RA_success_RAO = Now_RAO ; //Msg4 結束RA
                                    MTCD_Table[i].MTCD_RA_status ="Success";
                                    if(MTCD_Table[i].Power_level == 0){ PreStatus[3][Now_RAO] +=1;}    // Success Preamble +=1
                                    break;
                                }
                            }

                            if(grant_check_index == 0)
                            {
                                if(MTCD_Table[i].Power_level == 0){PreStatus[4][Now_RAO]+=1;} //Grant fail +=1

                                if(MTCD_Table[i].nTransmit_RA < MAX_nTransmit_RA)
                                {
                                    MTCD_Table[i].D2D_initate_request_RAO = Now_RAO + (Backoff_RA/10);
                                    MTCD_Table[i].MTCD_RA_status = "D2D_init";
                                }
                                else
                                {
                                    fail_nMTCD +=1;
                                    MTCD_Table.at(i).nTransmit_RA +=1 ;//區隔成功跟失敗的設備重傳次數
                                    MTCD_Table[i].MTCD_RA_status = "Grant Broken";
                                }

                            }
                        }
                        else if (each_RAO_Premble[each_RAO_Pre_index] == 1 && MTCD_Table[i].Preamble_number > nGroup)  // 使用sharePreamble 成功
                        {
                            bool grant_check_index =0;

                            for(int x=1 ; x<=used_Pre;x++ )
                            {
                                //  cout<<"Preamble:"<<MTCD_Table[i].Preamble_number<<"  vs  " <<eachRAOPre_transmit_shuffle[x]<<endl;
                                if (MTCD_Table[i].Preamble_number == eachRAOPre_transmit_shuffle[x] )
                                {
                                    grant_check_index =1;
                                    Success_nMTCD +=1;
                                    Successn_nMTCD_EachRAO[Now_RAO] +=1;   //Msg3 成功傳送
                                    MTCD_Table[i].RA_success_RAO = Now_RAO ; //Msg4 結束RA
                                    PreStatus[3][Now_RAO] +=1;
                                    MTCD_Table.at(i).MTCD_RA_status ="share_Success";

                                    break;
                                }
                            }

                            if(grant_check_index == 0)
                            {
                                PreStatus[4][Now_RAO]+=1;

                                if(MTCD_Table[i].nTransmit_RA< MAX_nTransmit_RA)
                                {
                                    MTCD_Table[i].MTCD_RA_status = "D2D_init";
                                    MTCD_Table[i].D2D_initate_request_RAO = Now_RAO + (Backoff_RA/10);
                                }
                                else
                                {
                                    fail_nMTCD +=1;
                                    MTCD_Table.at(i).nTransmit_RA +=1 ;//區隔成功跟失敗的設備重傳次數
                                    MTCD_Table[i].MTCD_RA_status = "Grant Broken";
                                }

                            }
                        }

                    }
                }
            }


        }

        if((Success_nMTCD + fail_nMTCD) == nMTCD)
        {
            finish_RAO = Now_RAO ;
            cout << "finish: " << finish_RAO;
            cout << "Complete Time:" << static_cast<double>(finish_RAO) /100 << "s" << endl;
            break;
        }


	}
    cout <<"Success_nMTCD:"<<Success_nMTCD<<endl;
    cout <<"fail_nMTCD:"<<fail_nMTCD<<endl;



    for (int i = 0; i < nMTCD; i++)
	{
		if (MTCD_Table[i].RA_success_RAO != -1)//失敗率
		{
			//totalMTCD_Access_delay += MTCD_Table[i].RA_success_RAO - MTCD_Table[i].RA_first_RAO;   // frist RA_RAO - Success RA_RAO
            totalMTCD_Access_delay += MTCD_Table[i].RA_success_RAO - MTCD_Table[i].D2D_first_request_RAO;   // Success RA_RAO - D2D_first_request_RAO
		}
	}

    fstream nMTCD_file ;

    nMTCD_file.open("Dense\\"+directory_nMTCD+"\\Dense_with_earlydection_RAtime.csv", fstream::out);
    if (nMTCD_file.is_open())
	{
        nMTCD_file <<"MTCD_number,group,D2D_first_request_RAO,D2D_initate_request_RAO,nRequest_D2D,";
        nMTCD_file <<"RA_first_RAO,RA_initate_RAO,RA_success_RAO,nTransmit_RA,Preamble_number,Power_level,MTCD_status,D2D_request_allocation_index "<<endl ;

        for(int i=0;i<nMTCD;i++)
        {
            nMTCD_file <<MTCD_Table[i].MTCD_number<<","<<MTCD_Table[i].group<<","<<MTCD_Table[i].D2D_first_request_RAO<<","<<MTCD_Table[i].D2D_initate_request_RAO<<",";
            nMTCD_file <<MTCD_Table[i].nRequest_D2D<<","<<MTCD_Table[i].RA_first_RAO<<","<<MTCD_Table[i].RA_initate_RAO<<","<<MTCD_Table[i].RA_success_RAO<<",";
            nMTCD_file <<MTCD_Table[i].nTransmit_RA<<","<<MTCD_Table[i].Preamble_number<<","<<MTCD_Table[i].Power_level<<","<<MTCD_Table[i].MTCD_RA_status<<",";
            nMTCD_file <<MTCD_Table[i].D2D_request_allocation_index<<endl;

            total_D2D_nRequest_cumulation += MTCD_Table[i].nRequest_D2D ; //記錄所有設備的D2D重傳次數
             if(MTCD_Table[i].nTransmit_RA > 10)
            {
                total_RA_nTransmission_cumulation += 10;
            }
            else
            {
                total_RA_nTransmission_cumulation += MTCD_Table[i].nTransmit_RA;
            }
        }
    }



    fstream PreStatus_file;
    PreStatus_file.open("Dense\\"+directory_nMTCD+"\\Dense_with_earlydection_PreStatus.csv", fstream::out);
    if (PreStatus_file.is_open())
	{
        PreStatus_file <<"initate MTCD,emtpyPre,collidePre,successPre,grant fail,collide probility,PACB"<<endl;
        for(int i=0 ; i<simRAo ; i++)
        {
            Collide_probility_cumulation += (static_cast<double>(PreStatus[2][i])/54);
		    PreStatus_file <<PreStatus[0][i]<<","<<PreStatus[1][i]<<","<<PreStatus[2][i]<<","<<PreStatus[3][i]
			  << ","<<PreStatus[4][i] <<","<<(static_cast<double>(PreStatus[2][i])/54)<<","<<PACB_eachRAO[i] <<endl;
        }

    }


    fstream SuccessMTCD_cumulation_file;
    SuccessMTCD_cumulation_file.open("Dense\\"+directory_nMTCD+"\\Dense_with_earlydection_SuccessMTCD.csv", fstream::out);
    if (SuccessMTCD_cumulation_file.is_open())
	{
        SuccessMTCD_cumulation_file <<"SuccessMTCD"<<endl;
        for(int a = 1; a <= simRAo; a++)
        {
            Success_nMTCD_cumulation_EachRAO[a] = Success_nMTCD_cumulation_EachRAO[a-1] + Successn_nMTCD_EachRAO[a];
            SuccessMTCD_cumulation_file <<  Success_nMTCD_cumulation_EachRAO[a]<<endl;
        }
    }

    fstream D2D_request_file ;
    D2D_request_file.open("Dense\\"+directory_nMTCD+"\\Dense_with_earlydection_D2D_request.csv", fstream::out);
    if (D2D_request_file.is_open())
    {
        D2D_request_file<<"RAO,";
        for(int x=1; x<=nGroup; x++)
        {
            D2D_request_file <<x<<",";
        }
        D2D_request_file << "total_request"<<endl;
        for(int i=0 ; i<simRAo ; i++)
        {
            D2D_request_file<<D2D_total_request_eachGroup[0][i]<<",";
            for(int x=1; x<=nGroup;x++ )
            {
                D2D_request_file << D2D_total_request_eachGroup[x][i] <<",";
            }
            D2D_request_file <<D2D_total_cumulation_request[i]<<endl;
        }

    }

    double nMTCDs =nMTCD;  //讓變數=常數做處理
    cout <<"success"<< Success_nMTCD <<" fail: "<<fail_nMTCD << endl;
    cout << "Average Access Delay:" << (double(totalMTCD_Access_delay) / double(Success_nMTCD) /100)+0.016 << endl;//除以100專換成秒
    cout <<"total MTCD"<< Success_nMTCD +fail_nMTCD << endl;
	cout <<"collide probility:"<<Collide_probility_cumulation/finish_RAO<<endl;
    cout <<"D2D total nRequest:"<<total_D2D_nRequest_cumulation<<endl;
    cout <<"D2D Average nRequest:"<<double(total_D2D_nRequest_cumulation)/nMTCDs<<endl;
    cout <<"RA total nTransmission:"<<total_RA_nTransmission_cumulation<<endl;
    cout <<"RA Average nTransmission:"<<double(total_RA_nTransmission_cumulation)/nMTCDs<<endl;
	cout << "Drop rate:" << (double(fail_nMTCD) / double(nMTCDs)) * 100 << "%" << endl;

	fstream result_file;
	result_file.open("Dense\\"+directory_nMTCD+"\\Dense_with_earlydection_result.txt",fstream :: out);

	result_file <<"rao"<<finish_RAO<<endl;
    result_file <<"success"<< Success_nMTCD <<" fail: "<<fail_nMTCD << endl;
	result_file << "Complete Time:" << static_cast<double>(finish_RAO) /100 << "s" << endl;
	result_file  << "Average Access Delay:" << (double(totalMTCD_Access_delay) / double(Success_nMTCD) /100)+0.016 << endl;
	result_file << Success_nMTCD+ fail_nMTCD << endl;
	result_file <<"collide probility:"<<Collide_probility_cumulation/finish_RAO<<endl;
    result_file <<"D2D total nRequest:"<<total_D2D_nRequest_cumulation<<endl;
    result_file <<"D2D Average nRequest:"<<double(total_D2D_nRequest_cumulation)/nMTCDs<<endl;
    result_file <<"RA total nTransmission:"<<total_RA_nTransmission_cumulation<<endl;
    result_file <<"RA Average nTransmission:"<<double(total_RA_nTransmission_cumulation)/nMTCDs<<endl;
	result_file << "Drop rate:" << (double(fail_nMTCD) / double(nMTCD)) * 100 << "%" << endl;

	result_file.close();
    D2D_request_file.close();
    SuccessMTCD_cumulation_file.close();
    PreStatus_file.close();
    nMTCD_file.close();

    system("pause");
	return 0;




}