import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
import os
dircectory_nMTCD = "10K"
Sim_RAO = 15+1  #1000 RAO = 10s  +1是因為圖表好看

Yaxis_index = 0 # 0:10k 1:30K 2:50k

MTCD_CDF_Yaxis=[10000,30000,50000]
MTCD_CDF_Yaxis_gap=[1000,2500,5000]
MTCD_init_Yaxis =[250,800,1500]
MTCD_init_Yaxis_gap =[25,50,100]


STD_Pre_status_withGrant = pd.read_csv("STD/Have_Grant/"+dircectory_nMTCD+"/PreStatus.csv")
STD_CDF_MTCD_withGrant = pd.read_csv("STD/Have_Grant/"+dircectory_nMTCD+"/stdsuccessdevice.csv")
STD_Pre_status_NoGrant = pd.read_csv("STD/No_Grant/"+dircectory_nMTCD+"/PreStatus.csv")
STD_CDF_MTCD_NoGrant = pd.read_csv("STD/No_Grant/"+dircectory_nMTCD+"/stdsuccessdevice.csv")

OptimalACB_Pre_status_withSIB = pd.read_csv("optimalACB/Have_SIB/"+dircectory_nMTCD+"/PreStatus.csv")
OptimalACB_CDF_MTCD_withSIB = pd.read_csv("optimalACB/Have_SIB/"+dircectory_nMTCD+"/Optimal_successdevice.csv")
OptimalACB_Pre_status_NoSIB = pd.read_csv("optimalACB/No_SIB/"+dircectory_nMTCD+"/PreStatus.csv")
OptimalACB_CDF_MTCD_NoSIB = pd.read_csv("optimalACB/No_SIB/"+dircectory_nMTCD+"/Optimal_successdevice.csv")

print(STD_CDF_MTCD_withGrant.head())
print(STD_CDF_MTCD_NoGrant.head())





# Cumulative MTCD
plt.plot(STD_CDF_MTCD_NoGrant['success'],label='STD - without Grant',markevery=100,marker='.')
plt.plot(STD_CDF_MTCD_withGrant['success'],label='STD - with Grant',markevery=100,marker='v')
plt.plot(OptimalACB_CDF_MTCD_withSIB['success'],label='OptimalACB - with SIB2',markevery=100,marker='s')
plt.plot(OptimalACB_CDF_MTCD_NoSIB['success'],label='OptimalACB - without SIB2',marker='x',markevery=100)
plt.legend(fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0)
xlabe=[]
for i in range(Sim_RAO):
    xlabe.append(str(i))

print(xlabe)

plt.xticks(np.arange(0,(Sim_RAO*100),100),labels=xlabe,fontsize=16)
plt.yticks(np.arange(0,MTCD_CDF_Yaxis[Yaxis_index]+1000,MTCD_CDF_Yaxis_gap[Yaxis_index]),fontsize=16)

#plt.grid(True, ls=':')
plt.title('Cumulative Success MTCDs with nMTCD = '+dircectory_nMTCD,fontsize=22)
plt.ylabel('Number of MTCDs for Successful RA',fontsize=22)
plt.xlabel('Simulation Time(second)',fontsize=22)
plt.grid()

plt.show()

# each RAO initate MTCD
plt.plot(STD_Pre_status_NoGrant['initate MTCD'],label= 'STD - without Grant',markevery=1000,marker='8')
plt.plot(STD_Pre_status_withGrant['initate MTCD'],label= 'STD - with Grant',markevery=1000,marker='v')
plt.plot(OptimalACB_Pre_status_withSIB['initate MTCD'],label= 'OptimalACB - with SIB2',markevery=1000,marker='s')
plt.plot(OptimalACB_Pre_status_NoSIB['initate MTCD'],label= 'OptimalACB - without SIB2',markevery=1000,marker='x')

plt.legend(fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0)
plt.xticks(np.arange(0,(Sim_RAO*100),100),labels=xlabe,fontsize=16)
plt.yticks(np.arange(0,MTCD_init_Yaxis[Yaxis_index],MTCD_init_Yaxis_gap[Yaxis_index]),fontsize=16)
plt.title('Initate MTCDs for each RAO with nMTCD = '+dircectory_nMTCD,fontsize=22)
plt.ylabel('Number of MTCDs that initiated RA',fontsize=22)
plt.xlabel('Simulation Time(second)',fontsize=22)
plt.grid()
plt.show()

'''
# each RAO Preamble status
plt.plot(Pre_status_withGrant['collidePre'],label='Number of collision')
plt.plot(Pre_status_withGrant['successPre'],label='Number of success')
plt.plot(Pre_status_withGrant['grant fail'],label='Number of grant fail')

plt.legend(loc=2,fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0)
plt.title('Preamble Status for each RAO with nMTCD = 10000',fontsize=22)
plt.xticks(np.arange(0,1100,50))
plt.yticks(np.arange(0,55,1))
plt.ylabel('i-th Preamble',fontsize=22)
plt.xlabel('j-th RAO',fontsize=22)
plt.grid()
plt.show()
'''