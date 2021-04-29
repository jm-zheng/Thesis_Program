#include <iostream>
#include <math.h>
#include<fstream>
#include <ctime>
using namespace std;

string directory_nMTCD ="150K";
const int nMTCD=150000;
const int simRAo = 8800; // 1=10ms
//const int interRAo = 5; // 10: index 3    5: index 6
//const int cell_r = 1000;
//const int d2d_r = 100;
const int Backoff =20;//20:20ms 960=960ms
const int beta_a = 3;
const int beta_b = 4;
const int beta_RAo = 1000; // 1=10ms
const int maxreTimes = 10; //最多重傳次數 10次數 20次數

int finish_RAO =0;

//double sd = 0; // standard deviation
int numMTCDfail = 0;
int RAtime[4][nMTCD]={0}; //0: initiate RA time   1: first RA time    2: success RA time  3: RA retransmission times
int PreStatus[5][simRAo]={0}; //0: number of device initiate RA    1: emtpyPre    2: colliPre    3: successPre 4:not ULgrant
int beta_nMTCD[beta_RAo]={0}; // number of device initiate RA in beta_RAo;
double beta_proability[beta_RAo]={0}; // proability of beta in RA
double beta_proability_ac[beta_RAo]={0}; // ac_proability of beta in RA
int SuccessnMTCD = 0;

double reRAtime=0;
int SuccessnMTCDslot[simRAo] = { 0 };
double droprate;
double collide_probility=0;
int totaldelay = 0;
int initiatedRA = 0;

int main()
{
	int ACBP_flag=0;

//初始化
	srand(2021);
	//srand((unsigned)time(NULL));
    ////////// generate beta distribution
    for( int a=0; a<beta_RAo-1; ++a ){
        beta_proability[a+1] = 60*pow(a+1,beta_a-1)*pow( beta_RAo-a-1, beta_b-1)/pow(beta_RAo,beta_a+beta_b-1);
        beta_proability_ac[a+1] = beta_proability_ac[a] + beta_proability[a+1];
    }
    beta_proability_ac[beta_RAo] = 1;
    ////////// generate RAtime in each MTCD
    for( int a=0; a <nMTCD; ++a ){
        double i = (double)rand()/(RAND_MAX+1);
        for( int b=0; b <beta_RAo; ++b )
            if( i < beta_proability_ac[b] ){
                RAtime[0][a] = b;
                RAtime[1][a] = b;
                ++beta_nMTCD[b+1];
                break;
			}
	}
    /////
    for( int a=0; a <nMTCD; ++a )
        RAtime[2][a] = -1;



   //// STD模擬開始
  double ACBP =1;

	for (int a = 0; a < simRAo; ++a) {
		initiatedRA = 0;

		for (int b = 0; b < nMTCD; ++b) {
			if (RAtime[0][b] == a) { initiatedRA++; }
		}

		if (initiatedRA < 54) { ACBP = 1; }
		else { ACBP = static_cast < double>(54) / initiatedRA; }


		int eachRAoPre[55] = { 0 };
		int SelectPre[nMTCD] = { 0 };

		for (int b = 0; b < nMTCD; ++b) {
			if (RAtime[0][b] == a) {
				double i = (double)rand() / (RAND_MAX + 1);//設備產生的機率
				if (i <= ACBP){//改成機率
					++PreStatus[0][a];          //這次rao成功發??
					SelectPre[b] = rand() % 54 + 1;
					++eachRAoPre[SelectPre[b]];
				}
				else
				{
					RAtime[0][b] = RAtime[0][b] + (Backoff / 10);
				}
			}
		}

		int eachRAOPre_transmit[55]	={0},used_Pre=1; //  eachRAOPre_transmit:在RAO裡哪一個Pre發送 used_pre:總共有幾個pre發送


		for (int c = 1; c < 55; ++c)
		{
			if(eachRAoPre[c] != 0)
			{
				eachRAOPre_transmit[used_Pre] =c;
				//cout<<eachRAOPre_transmit[used_Pre] << " ";
 				used_Pre++;
			}
		}

		//cout<<endl<<"used_Pre:"<<used_Pre<<endl;

		int eachRAOPre_transmit_shuffle[used_Pre]={0}; //
		int shuffle_arr[used_Pre]={0},shuffle_index=0; //洗牌紀錄的陣列

		for( int c=1;c<used_Pre;c++)
		{
			do {
					shuffle_index = (rand() % (used_Pre-1))+1;
			}
			while(shuffle_arr[shuffle_index]!=0 );

			shuffle_arr[shuffle_index]=1;
			eachRAOPre_transmit_shuffle[c] = eachRAOPre_transmit[shuffle_index];
			/*cout<<"eachRAOPre_transmit_index:"<<shuffle_index<<endl;
			cout<<"shuffle_index[c]:";
			for(int c=0;c<used_Pre;c++) cout << shuffle_arr[c]<<" ";
			cout <<endl;*/
		}
		/*cout << "eachRAOPre_transmit_shuffle: ";

		for(int c=1;c<used_Pre;c++) cout << eachRAOPre_transmit_shuffle[c]<<" ";
		cout <<endl;*/

		if(used_Pre>30) used_Pre=30; //能使用的grant傳送的pre最多就是30個 10*3


		for (int c = 1; c < 55; ++c) {
			if (eachRAoPre[c] == 0)
			{
				++PreStatus[1][a];
			}
			else if (eachRAoPre[c] > 1) {
				++PreStatus[2][a];
				for (int d = 0; d < nMTCD; ++d){
					if (c == SelectPre[d])
					{
						++RAtime[3][d]; //傳輸次數+1
						if (RAtime[3][d] < maxreTimes) {
								RAtime[0][d] = RAtime[0][d] + (Backoff / 10);
						}
						else{
							++RAtime[3][d]; //區隔成功跟失敗的設備重傳次數
							++numMTCDfail;
						}
					}
				}
			}
			else if (eachRAoPre[c] == 1) {   // 該個preamble只有1個設備發??
				bool grant_check_index =0;
				for( int x=1; x<=used_Pre; x++)
				{
					if(c == eachRAOPre_transmit_shuffle[x] )
					{
						grant_check_index =1;
						++PreStatus[3][a];
						++SuccessnMTCD;
						SuccessnMTCDslot[a]++;
						for (int d = 0; d < nMTCD; ++d) {
							if (SelectPre[d] == c){  //第幾個MTCD
								++RAtime[3][d]; //傳輸次數+1
								RAtime[2][d] = a ;//5為 RAR windows size + Contention resolution timer
							}
						}
					}
				}
				if(grant_check_index == 0)  // 沒有分配到grant
				{
					++PreStatus[4][a];
					for (int d = 0; d < nMTCD; ++d)
						if (c == SelectPre[d])
						{
							++RAtime[3][d];//傳輸次數+1
							if (RAtime[3][d] < maxreTimes) {
								RAtime[0][d] = RAtime[0][d] + (Backoff / 10);
							}
							else{
								++RAtime[3][d];//區隔成功跟失敗的設備重傳次數
								++numMTCDfail;
							}
						}

				}
			}
		}

		/*for (int c = 1; c < 55; ++c) {
			if (eachRAoPre[c] == 0)
			{
				++PreStatus[1][a];
			}
			else if (eachRAoPre[c] == 1) {   // 該個preamble只有1個設備發??
				++PreStatus[3][a];
				++SuccessnMTCD;
				SuccessnMTCDslot[a]++;
				for (int d = 0; d < nMTCD; ++d) {
					if (SelectPre[d] == c)
						RAtime[2][d] = a + 5;//5為 RAR windows size + Contention resolution timer
				}
			}
			else if (eachRAoPre[c] > 1) {
				++PreStatus[2][a];
				for (int d = 0; d < nMTCD; ++d)
					if (c == SelectPre[d])
						if (RAtime[3][d] < maxreTimes) {
								RAtime[0][d] = RAtime[0][d] + (Backoff / 10);
								++RAtime[3][d];
							}
							else
								++numMTCDfail;
						}
			}*/
		if ((SuccessnMTCD + numMTCDfail) == nMTCD) {
			finish_RAO =a;
			cout <<"rao"<<finish_RAO<<endl;
			cout << "Complete Time:" << static_cast<double>(finish_RAO) /100 << "s" << endl;
			break;
		}

    }////模擬結束

	for (int i = 0; i < nMTCD; i++)
	{

		if ((RAtime[2][i] != -1))//失敗率
		{
			totaldelay += RAtime[2][i] - RAtime[1][i];
		}
	}


	fstream file1;
	file1.open("No_SIB\\"+directory_nMTCD+"\\OptimalACB_successdevice.csv", fstream::out);
	if (file1.is_open())
	{
		int SuccessnMTCDslotclu[simRAo] = { 0 };
		file1<<"success"<<endl;
		for (int a = 1; a < simRAo; ++a) {
			SuccessnMTCDslotclu[a] = SuccessnMTCDslotclu[a-1] + SuccessnMTCDslot[a];
			file1 << SuccessnMTCDslotclu[a] << endl;
		}
	}
	file1.close();



	file1.open("No_SIB\\"+directory_nMTCD+"\\OptimalACB_PreStatus.csv" , fstream:: out);
	file1<< "initate MTCD,emtpyPre,collidePre,successPre,grant fail,collide probility"<< endl;

	for(int i=0;i<simRAo;i++)
	{
		collide_probility += (static_cast<double>(PreStatus[2][i])/54);
		file1 <<PreStatus[0][i]<<","<<PreStatus[1][i]<<","<<PreStatus[2][i]<<","<<PreStatus[3][i]
			  << ","<<PreStatus[4][i]<<","<<(static_cast<double>(PreStatus[2][i])/54) <<endl;
	}
	file1.close();

	file1.open("No_SIB\\"+directory_nMTCD+"\\OptimalACB_RAtime.csv" , fstream:: out);
	file1<< "initateRA,firstRA,successRA,retranmission"<< endl;

	for(int i=0;i<nMTCD;i++)
	{
		file1 <<RAtime[0][i]<<","<<RAtime[1][i]<<","<<RAtime[2][i]<<","<<RAtime[3][i]
			  <<endl;
	}
	file1.close();

	cout <<"success"<< SuccessnMTCD <<" fail: "<<numMTCDfail << endl;
	cout << "Average Access Delay:" << (double(totaldelay) / double(SuccessnMTCD) /100)+0.016 << endl;//除以100專換成秒
	cout << SuccessnMTCD+ numMTCDfail << endl;
	cout <<"collide probility:"<<collide_probility/finish_RAO<<endl;
	cout << "Drop rate:" << (double(numMTCDfail) / double(nMTCD)) * 100 << "%" << endl;

	fstream result_file;
	result_file.open("No_SIB\\"+directory_nMTCD+"\\OptimalACB_result.txt",fstream :: out);

	result_file <<"rao"<<finish_RAO<<endl;
	result_file <<"success"<< SuccessnMTCD <<" fail: "<<numMTCDfail << endl;
	result_file << "Complete Time:" << static_cast<double>(finish_RAO) /100 << "s" << endl;
	result_file  << "Average Access Delay:" << (double(totaldelay) / double(SuccessnMTCD) /100)+0.016 << endl;
	result_file << SuccessnMTCD+ numMTCDfail << endl;
	result_file <<"collide probility:"<<collide_probility/finish_RAO<<endl;
	result_file << "Drop rate:" << (double(numMTCDfail) / double(nMTCD)) * 100 << "%" << endl;

	result_file.close();


	system("pause");
	return 0;
}

