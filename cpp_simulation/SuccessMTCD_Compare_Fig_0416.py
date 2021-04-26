import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
import os
dircectory_nMTCD = "100K"
MTCD_Position = "Sparse"

Sim_RAO = 65+1  #1000 RAO = 10s  +1是因為圖表好看 15 36 40 65
Axis_index = 3 # 0:10k 1:30K 2:50k 3:100K

MTCD_CDF_Yaxis=[10000,30000,50000,100000]
MTCD_CDF_Yaxis_gap=[1000,2500,5000,10000]
MTCD_CDF_Xaxis_gap=[100,100,200,200]

MTCD_init_Yaxis =[250,800,1500]
MTCD_init_Yaxis_gap =[25,50,100]


STD_Pre_status_withGrant = pd.read_csv("STD/Have_Grant/"+dircectory_nMTCD+"/STD_withGrant_PreStatus.csv")
STD_CDF_MTCD_withGrant = pd.read_csv("STD/Have_Grant/"+dircectory_nMTCD+"/STD_withGrant_stdsuccessdevice.csv")


OptimalACB_Pre_status_NoSIB = pd.read_csv("optimalACB/No_SIB/"+dircectory_nMTCD+"/OptimalACB_PreStatus.csv")
OptimalACB_CDF_MTCD_NoSIB = pd.read_csv("optimalACB/No_SIB/"+dircectory_nMTCD+"/OptimalACB_successdevice.csv")
Preamble_allocation_CDF = pd.read_csv("Premble_allocation/"+dircectory_nMTCD+"/PreambleAllocation_SuccessMTCD.csv")
Grouping_NOMA_allocation_CDF =pd.read_csv("Goruping NOMA_allcation/"+MTCD_Position+"/"+dircectory_nMTCD+"/with_earlydection_SuccessMTCD.csv")

print(STD_CDF_MTCD_withGrant.head())






# Cumulative MTCD


plt.plot(STD_CDF_MTCD_withGrant['success'],label='STD - with Grant',markevery=100,marker='^')
plt.plot(OptimalACB_CDF_MTCD_NoSIB['success'],label='Optimal ACB ',marker='s',markevery=100)
plt.plot(Preamble_allocation_CDF['SuccessMTCD'],label='Preamble Allocation',markevery=100,marker='x')
plt.plot(Grouping_NOMA_allocation_CDF['SuccessMTCD'],label='Proposal-Grouping NOMA',markevery=100,marker='*')

plt.legend(loc=7,fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0)
xlabe=[]
if(Axis_index <2):
    for i in range(Sim_RAO):
        xlabe.append(str(i))
else:

    for i in range(Sim_RAO):
        if(i%2==0):
            xlabe.append(str(i))

print(xlabe)

plt.xticks(np.arange(0,(Sim_RAO*100),MTCD_CDF_Xaxis_gap[Axis_index]),labels=xlabe,fontsize=12)
plt.yticks(np.arange(0,MTCD_CDF_Yaxis[Axis_index]+1000,MTCD_CDF_Yaxis_gap[Axis_index]),fontsize=16)

#plt.grid(True, ls=':')

plt.title('Cumulative Success MTCDs with nMTCD = '+dircectory_nMTCD,fontsize=22)
plt.ylabel('Number of Successful MTCDs ',fontsize=22)
plt.xlabel('Simulation Time(second)',fontsize=22)
plt.grid()

plt.show()
'''
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