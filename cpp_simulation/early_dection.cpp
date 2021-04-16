#include<bits/stdc++.h>

using namespace std;
int main()
{
    srand(2021);

    int each_RAO_Premble[55] = {0};
    for(int i=1; i<55;i++)
    {
        each_RAO_Premble[i] = rand()%4;
        cout << i <<" : "<<each_RAO_Premble[i]<<endl;
    }
    each_RAO_Premble[54] = 1;
    each_RAO_Premble[52] = 1;
    each_RAO_Premble[51] = 3;
     each_RAO_Premble[53] = 2;
     each_RAO_Premble[50] = 1;
    int used_Pre=1; //  eachRAOPre_transmit:在RAO裡哪一個Pre發送 used_pre:總共有幾個pre發送
	int number_grant=31 ;    // grant 30個限制 因為used_Pre從1開始
    vector<int> eachRAOPre_transmit_shuffle ={0};  //eachRAOPre_transmit_shuffle :洗牌過後的Pre的Preamble
    vector<int> Preamble_load3 , Preamble_load2 ,Preamble_load1; // Preamble_load3:1個Preamble有3個用 Preamble_load2:1個Preamble有2個用  Preamble_load1:1個Preamble有1個用
    for(int c=1 ; c<55 ; c++)
        {
            if(each_RAO_Premble[c] != 0)
			{
                if(c > 50 && each_RAO_Premble[c]==1) eachRAOPre_transmit_shuffle.push_back(c);

                else if ( c<=50 )
                {
                    if(each_RAO_Premble[c] == 3)
                    {
                        Preamble_load3.push_back(c);
                    }
                    else if(each_RAO_Premble[c] == 2)
                    {
                        Preamble_load2.push_back(c);
                    }
                    else if (each_RAO_Premble[c] == 1)
                    {
                        Preamble_load1.push_back(c);
                    }
                }

 				used_Pre++;
			}
        }

    cout <<"load1"<<endl;
    for(int i=0 ;i<Preamble_load1.size(); i++) cout<<i<<" : "<<Preamble_load1.at(i) << endl;
    cout <<"load2"<<endl;
    for(int i=0 ;i<Preamble_load2.size(); i++) cout<<i<<" : "<<Preamble_load2.at(i) << endl;
    cout <<"load3"<<endl;
    for(int i=0 ;i<Preamble_load3.size(); i++) cout<<i<<" : "<<Preamble_load3.at(i) << endl;
    cout<<endl<<"used_Pre:"<<used_Pre<<endl;
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
    for(int i=0 ;i<eachRAOPre_transmit_shuffle.size(); i++) {
        cout<<i<<" : "<<eachRAOPre_transmit_shuffle[i] << endl;
    }


   system("pause");

}
