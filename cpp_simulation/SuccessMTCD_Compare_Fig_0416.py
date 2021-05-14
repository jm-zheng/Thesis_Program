import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
import os
dircectory_nMTCD = "10K"


Sim_RAO = 15+1  #1000 RAO = 10s  +1是因為圖表好看 15 20 30 65 88
Axis_index = 0 # 0:10k 1:30K 2:50k 3:100K 4:150K

MTCD_CDF_Yaxis=[10000,32500,50000,100000,150000]
MTCD_CDF_Yaxis_gap=[1000,2500,5000,10000,10000]
MTCD_CDF_Xaxis_gap=[100,100,100,200,200]
fig_legend=['upper left','center right','center right','center right','center right']




STD_withGrant_CDF = pd.read_csv("STD/Have_Grant/"+dircectory_nMTCD+"/STD_withGrant_stdsuccessdevice.csv")
OptimalACB_NoSIB_CDF = pd.read_csv("optimalACB/No_SIB/"+dircectory_nMTCD+"/OptimalACB_successdevice.csv")
NORA_CDF =pd.read_csv("NORA/Have_Grant/"+dircectory_nMTCD+"/NORA_withGrant_stdsuccessdevice.csv")
Uniform_Preamble_allocation_CDF = pd.read_csv("Premble_allocation/Uniform/"+dircectory_nMTCD+"/PreambleAllocation_SuccessMTCD.csv")
Uniform_Grouping_NOMA_CDF = pd.read_csv("Goruping NOMA_allcation/Uniform/"+dircectory_nMTCD+"/with_earlydection_SuccessMTCD.csv")
Dense_Preamble_allocation_CDF = pd.read_csv("Premble_allocation/Dense/"+dircectory_nMTCD+"/Dense_PreambleAllocation_SuccessMTCD.csv")
Dense_Grouping_NOMA_CDF = pd.read_csv("Goruping NOMA_allcation/Dense/"+dircectory_nMTCD+"/Dense_with_earlydection_SuccessMTCD.csv")
print(STD_withGrant_CDF.head())






# Cumulative MTCD


plt.plot(STD_withGrant_CDF['success'], label='STD', markevery=100, marker='^', color='dodgerblue')
plt.plot(OptimalACB_NoSIB_CDF['success'], label='Optimal ACB ', marker='D', markevery=100, color='m')
plt.plot(Uniform_Preamble_allocation_CDF['SuccessMTCD'],label='Preamble Allocation(Uniform)', markevery=100, marker='s', color='r')
plt.plot(Dense_Preamble_allocation_CDF['SuccessMTCD'], label='Preamble Allocation(Dense)', markevery=100, marker='d', color='navy')
plt.plot(NORA_CDF['success'],label='NORA', markevery=100, marker='P',color='c')
plt.plot(Uniform_Grouping_NOMA_CDF['SuccessMTCD'], label='Proposal-Grouping NOMA(Uniform)', markevery=100, marker='v', color='lime')
plt.plot(Dense_Grouping_NOMA_CDF['SuccessMTCD'], label='Proposal-Grouping NOMA(Dense)', markevery=100, marker='x', color='gold')

plt.legend(loc=fig_legend[Axis_index],fontsize=12)  #150K (0.75,0.1)
plt.ylim(bottom=0)
plt.xlim(left=0)
xlabe = []
if(Axis_index <3):
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

plt.title('Cumulative Success MTCDs  ( nMTCD = '+dircectory_nMTCD+', r = 10 )',fontsize=22)
plt.ylabel('Cumulative number of Successful MTCDs ',fontsize=22)
plt.xlabel('Simulation Time(second)',fontsize=22)
plt.grid()

plt.show()



