#include <iostream>
#include <math.h>
#include<fstream>
#include <ctime>
using namespace std;
double A=0;
const int nMTCD=30000;
const int simRAo = 10000; // 1=10ms
//const int interRAo = 5; // 10: index 3    5: index 6
//const int cell_r = 1000;
//const int d2d_r = 100;
const int Backoff =20;//20:20ms 960=960ms
const int beta_a = 3;
const int beta_b = 4;
const int beta_RAo = 1000; // 1=10ms
const int maxreTimes = 10; //³Ì¦h­«¶Ç¦¸¼Æ 10¦¸¼Æ 20¦¸¼Æ


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
int totaldelay = 0;
int initiatedRA = 0;

int main()
{
	int ACBP_flag=0;

//ªì©l¤Æ
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



   //// STD¼ÒÀÀ¶}©l
  double ACBP =1;

	for (int a = 0; a < simRAo; ++a) {
		initiatedRA = 0;

		for (int b = 0; b < nMTCD; ++b) {
			if (RAtime[0][b] == a) { initiatedRA++; }
		}

		//if (initiatedRA < 54) { ACBP = 1; }
		//else { ACBP = static_cast < double>(54) / initiatedRA; }
		//ACBP_flag ++;
		//cout <<"ACBP_flag: "<<ACBP_flag<< ACBP << endl;

		int eachRAoPre[55] = { 0 };
		int SelectPre[nMTCD] = { 0 };

		for (int b = 0; b < nMTCD; ++b) {
			if (RAtime[0][b] == a) {
				double i = (double)rand() / (RAND_MAX + 1);//³]³Æ²£¥Íªº¾÷²v
				if (i <= ACBP){//§ï¦¨¾÷²v
					++PreStatus[0][a];          //³o¦¸rao¦¨¥\µoþ
					SelectPre[b] = rand() % 54 + 1;
					++eachRAoPre[SelectPre[b]];
				}
				else
				{
					RAtime[0][b] = RAtime[0][b] + (Backoff / 10);
				}
			}
		}

		int eachRAOPre_transmit[55]	={0},used_Pre=1; //  eachRAOPre_transmit:¦bRAO¸Ì­þ¤@­ÓPreµo°e used_pre:Á`¦@¦³´X­Ópreµo°e
		int number_grant=10 ; //

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
		int shuffle_arr[used_Pre]={0},shuffle_index=0; //¬~µP¬ö¿ýªº°}¦C

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

		if(used_Pre>30) used_Pre=30;


		for (int c = 1; c < 55; ++c) {
			if (eachRAoPre[c] == 0)
			{
				++PreStatus[1][a];
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
			else if (eachRAoPre[c] == 1) {   // ¸Ó­Ópreamble¥u¦³1­Ó³]³Æµoþ
				bool grant_check_index =0;
				for( int x=0; x<used_Pre; x++)
				{
					if(c == eachRAOPre_transmit_shuffle[x] )
					{
						grant_check_index =1;
						++PreStatus[3][a];
						++SuccessnMTCD;
						SuccessnMTCDslot[a]++;
						for (int d = 0; d < nMTCD; ++d) {
							if (SelectPre[d] == c)  //²Ä´X­ÓMTCD
								RAtime[2][d] = a + 5;//5¬° RAR windows size + Contention resolution timer
							}
					}
				}
				if(grant_check_index == 0)
				{
					++PreStatus[4][a];
					for (int d = 0; d < nMTCD; ++d)
						if (c == SelectPre[d])
							if (RAtime[3][d] < maxreTimes) {
									RAtime[0][d] = RAtime[0][d] + (Backoff / 10);
									++RAtime[3][d];
								}
								else
									++numMTCDfail;
				}
			}
		}

		/*for (int c = 1; c < 55; ++c) {
			if (eachRAoPre[c] == 0)
			{
				++PreStatus[1][a];
			}
			else if (eachRAoPre[c] == 1) {   // ¸Ó­Ópreamble¥u¦³1­Ó³]³Æµoþ
				++PreStatus[3][a];
				++SuccessnMTCD;
				SuccessnMTCDslot[a]++;
				for (int d = 0; d < nMTCD; ++d) {
					if (SelectPre[d] == c)
						RAtime[2][d] = a + 5;//5¬° RAR windows size + Contention resolution timer
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
			cout <<"rao"<<a<<endl;
			cout << "Complete Time:" << static_cast<double>(a) /100 << "s" << endl;
			break;
		}

    }////¼ÒÀÀµ²§ô

	for (int i = 0; i < nMTCD; i++)
	{

		if ((RAtime[2][i] != -1))//¥¢±Ñ²v
		{
			totaldelay += RAtime[2][i] - RAtime[1][i];
		}
	}
	cout << "Average Access Delay:" << double(totaldelay) / double(SuccessnMTCD) / 100 << endl;//°£¥H100±M´«¦¨¬í

	fstream file1;
	file1.open(" stdsuccessdevice.txt", fstream::out);
	if (!file1.is_open())
	{
		cout << "ÀÉ®×ÃöÃö" << endl;
		return 0;
	}

	int SuccessnMTCDslotclu[simRAo] = { 0 };
	for (int a = 1; a < simRAo; ++a) {
		SuccessnMTCDslotclu[a] = SuccessnMTCDslotclu[a-1] + SuccessnMTCDslot[a];
		file1 << SuccessnMTCDslotclu[a] << endl;
	}
	cout << SuccessnMTCD+ numMTCDfail << endl;
	cout << "Drop rate:" << (double(numMTCDfail) / double(nMTCD)) * 100 << "%" << endl;
	file1.close();

	system("pause");
	return 0;
}

