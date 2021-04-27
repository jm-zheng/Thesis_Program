import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
import os
dircectory_nMTCD = "50K"
MTCD_Position = "Dense"  # Sparse Dense
Sim_RAO = 10+1  #1000 RAO = 10s  +1是因為圖表好看 15 36 40 65

Axis_index = 0 # 0:10k 1:30K 2:50k 3:100K

MTCD_init_Yaxis=[400]
MTCD_init_Yaxis_gap=[25]
MTCD_init_Xaxis_gap=[100]




Beta_10k = pd.read_csv("NORA/Have_Grant/10K/MTCD_beta_distribution.csv")
Beta_30k = pd.read_csv("NORA/Have_Grant/30K/MTCD_beta_distribution.csv")
Beta_50k = pd.read_csv("NORA/Have_Grant/50K/MTCD_beta_distribution.csv")
Beta_100k = pd.read_csv("NORA/Have_Grant/100K/MTCD_beta_distribution.csv")
Beta_150k = pd.read_csv("NORA/Have_Grant/150K/MTCD_beta_distribution.csv")






# Cumulative MTCD

plt.plot(Beta_150k['beta_nMTCD'],label='150k MTCDs')
plt.plot(Beta_100k['beta_nMTCD'],label='100k MTCDs')
plt.plot(Beta_50k['beta_nMTCD'],label='50k MTCDs')
plt.plot(Beta_30k['beta_nMTCD'],label='30k MTCDs')
plt.plot(Beta_10k['beta_nMTCD'],label='10k MTCDs')




#plt.plot(Grouping_NOMA_allocation_Pre_status['D2D_first_request_RAO'],label='STD - with Grant',markevery=100,marker='^')
'''
plt.plot(OptimalACB_CDF_MTCD_NoSIB['success'],label='Optimal ACB ',marker='s',markevery=100)
plt.plot(Preamble_allocation_Pre_staus['SuccessMTCD'],label='Preamble Allocation',markevery=100,marker='x')
plt.plot(Grouping_NOMA_allocation_Pre_status['SuccessMTCD'],label='Proposal-Grouping NOMA',markevery=100,marker='*')
'''
plt.legend(loc=7,fontsize=12)
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

plt.xticks(np.arange(0,(Sim_RAO*100),MTCD_init_Xaxis_gap[Axis_index]),labels=xlabe,fontsize=12)
plt.yticks(np.arange(0,MTCD_init_Yaxis[Axis_index],MTCD_init_Yaxis_gap[Axis_index]),fontsize=12)

#plt.grid(True, ls=':')
plt.legend(fontsize=16)
plt.title('Distribution of MTCDs initiated RA.  Beta( 3,4,10s )    ',fontsize=18)
plt.ylabel('Number of MTCDs initiated RA.  ',fontsize=16)
plt.xlabel('Simulation Time(second).',fontsize=16)
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