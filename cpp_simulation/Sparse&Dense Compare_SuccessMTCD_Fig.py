import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
import os
dircectory_nMTCD = "10K"
fig_nMTCD = "10k"

Sim_RAO = 15+1  #1000 RAO = 10s  +1是因為圖表好看 15 36 40 65 86
Axis_index = 0 # 0:10k 1:30K 2:50k 3:100K

MTCD_CDF_Yaxis=[10000,30000,50000,100000,150000]
MTCD_CDF_Yaxis_gap=[1000,2500,5000,10000,10000]
MTCD_CDF_Xaxis_gap=[100,100,200,200,200]




Preamble_allocationUniform_CDF = pd.read_csv("Premble_allocation/Uniform/"+dircectory_nMTCD+"/PreambleAllocation_SuccessMTCD.csv")
Preamble_allocationDense_CDF = pd.read_csv("Premble_allocation/Dense/"+dircectory_nMTCD+"/Dense_PreambleAllocation_SuccessMTCD.csv")
Grouping_NOMA_allocationUniform_CDF =pd.read_csv("Goruping NOMA_allcation/Uniform/"+dircectory_nMTCD+"/with_earlydection_SuccessMTCD.csv")
Grouping_NOMA_allocationDense_CDF =pd.read_csv("Goruping NOMA_allcation/Dense/"+dircectory_nMTCD+"/Dense_with_earlydection_SuccessMTCD.csv")







# Cumulative MTCD



plt.plot(Grouping_NOMA_allocationDense_CDF['SuccessMTCD'],label='Proposal-Grouping NOMA(Dense)',markevery=100,marker='x')
plt.plot(Grouping_NOMA_allocationUniform_CDF['SuccessMTCD'],label='Proposal-Grouping NOMA(Sparse)',markevery=100,marker='*')
plt.plot(Preamble_allocationDense_CDF['SuccessMTCD'],label='Preamble Allocation(Dense) ',marker='s',markevery=100)
plt.plot(Preamble_allocationUniform_CDF['SuccessMTCD'],label='Preamble Allocation(Sparse)',markevery=100,marker='^')

plt.legend(loc='lower right',fontsize=16)
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

plt.title('Cumulative success MTCDs between dense and uniform distribution.  \n( nMTCD='+fig_nMTCD+", r=10 )",fontsize=26)
plt.ylabel('Cumulative number of successful MTCDs ',fontsize=22)
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