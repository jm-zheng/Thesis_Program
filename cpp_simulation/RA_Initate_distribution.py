import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
import os
dircectory_nMTCD = "150K"
Sim_RAO = 88+1  #1000 RAO = 10s  +1是因為圖表好看 15 20 30 65 88
Axis_index = 4 # 0:10k 1:30K 2:50k 3:100K

MTCD_init_Yaxis=[250,700,1200,2300,3500]
MTCD_init_Yaxis_gap=[25,50,100,200,250]
MTCD_init_Xaxis_gap=[100,100,100,200,200]




STD_withGrant_PreStatus = pd.read_csv("STD/Have_Grant/"+dircectory_nMTCD+"/STD_withGrant_PreStatus.csv")
OptimalACB_NoSIB_PreStatus = pd.read_csv("optimalACB/No_SIB/"+dircectory_nMTCD+"/OptimalACB_PreStatus.csv")
NORA_PreStatus =pd.read_csv("NORA/Have_Grant/"+dircectory_nMTCD+"/NORA_withGrant_PreStatus.csv")
Uniform_Preamble_allocation_PreStatus = pd.read_csv("Premble_allocation/Uniform/"+dircectory_nMTCD+"/PreambleAllocation_PreStatus.csv")
Uniform_Grouping_NOMA_PreStatus = pd.read_csv("Goruping NOMA_allcation/Uniform/"+dircectory_nMTCD+"/with_earlydection_PreStatus.csv")
Dense_Preamble_allocation_PreStatus = pd.read_csv("Premble_allocation/Dense/"+dircectory_nMTCD+"/Dense_PreambleAllocation_PreStatus.csv")
Dense_Grouping_NOMA_PreStatus = pd.read_csv("Goruping NOMA_allcation/Dense/"+dircectory_nMTCD+"/Dense_with_earlydection_PreStatus.csv")


xlabe=[]
if( Axis_index < 3):
    for i in range(Sim_RAO):
        xlabe.append(str(i))
else:
    for i in range(Sim_RAO):
        if(i%2==0):
            xlabe.append(str(i))



MaxGrant =pd.DataFrame(STD_withGrant_PreStatus['initate MTCD'])
MaxGrant.insert(0,'STD_max',30)
MaxGrant.insert(1,'NOMA_max',90)

print(MaxGrant)
# each RAO initate MTCD


plt.plot(Uniform_Preamble_allocation_PreStatus['initate MTCD'],label= 'Preamble Allocation(Uniform)', color='r')
plt.plot(Dense_Preamble_allocation_PreStatus['initate MTCD'],label= 'Preamble Allocation(Dense)',color='navy')
plt.plot(OptimalACB_NoSIB_PreStatus['initate MTCD'],label= 'Optimal ACB',color='c')
plt.plot(STD_withGrant_PreStatus['initate MTCD'],label= 'STD',color='dodgerblue')
plt.plot(MaxGrant['STD_max'],label='Maximal Success MTCDs(30)',color='black')

plt.legend(fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0)
plt.xticks(np.arange(0,(Sim_RAO*100),MTCD_init_Xaxis_gap[Axis_index]),labels=xlabe,fontsize=16)
plt.yticks(np.arange(0,MTCD_init_Yaxis[Axis_index],MTCD_init_Yaxis_gap[Axis_index]),fontsize=16)
plt.title('Distribution of the cumulative number of MTCDs initiating RA. \n( nMTCD = '+dircectory_nMTCD+', r = 10, Mechanism without NOMA )',fontsize=22)
plt.ylabel('Number of MTCDs initiating RA.',fontsize=22)
plt.xlabel('Simulation Time(second)',fontsize=22)
plt.grid()
plt.show()




plt.plot(Uniform_Grouping_NOMA_PreStatus['initate MTCD'],label= 'Proposal-Grouping NOMA(Uniform)',color='lime')
plt.plot(Dense_Grouping_NOMA_PreStatus['initate MTCD'],label= 'Proposal-Grouping NOMA(Dense)',color='gold')
plt.plot(NORA_PreStatus['initate MTCD'],label= 'NORA',color='m')
plt.plot(MaxGrant['NOMA_max'],label='Maximal Success MTCDs(90)',color='black')

plt.legend(fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0)
plt.xticks(np.arange(0,(Sim_RAO*100),MTCD_init_Xaxis_gap[Axis_index]),labels=xlabe,fontsize=16)
plt.yticks(np.arange(0,MTCD_init_Yaxis[Axis_index],MTCD_init_Yaxis_gap[Axis_index]),fontsize=16)
plt.title('Distribution of the cumulative number of MTCDs initiating RA. \n ( nMTCD = '+dircectory_nMTCD+', r = 10, Mechanism with NOMA )',fontsize=22)
plt.ylabel('Number of MTCDs initiating RA.',fontsize=22)
plt.xlabel('Simulation Time(second)',fontsize=22)
plt.grid()
plt.show()


plt.plot(STD_withGrant_PreStatus['initate MTCD'],label= 'STD',color='dodgerblue')
plt.plot(OptimalACB_NoSIB_PreStatus['initate MTCD'],label= 'Optimal ACB',color='c')
plt.plot(NORA_PreStatus['initate MTCD'],label= 'NORA',color='m')
plt.plot(Dense_Preamble_allocation_PreStatus['initate MTCD'],label= 'Preamble Allocation(Dense)',color='navy')
plt.plot(Uniform_Preamble_allocation_PreStatus['initate MTCD'],label= 'Preamble Allocation(Uniform)',color='r' )
plt.plot(Dense_Grouping_NOMA_PreStatus['initate MTCD'],label= 'Proposal-Grouping NOMA(Dense)',color='gold')
plt.plot(Uniform_Grouping_NOMA_PreStatus['initate MTCD'],label= 'Proposal-Grouping NOMA(Uniform)',color='lime')

plt.legend(fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0)
plt.xticks(np.arange(0,(Sim_RAO*100),MTCD_init_Xaxis_gap[Axis_index]),labels=xlabe,fontsize=16)
plt.yticks(np.arange(0,MTCD_init_Yaxis[Axis_index],MTCD_init_Yaxis_gap[Axis_index]),fontsize=16)
plt.title('Distribution of the cumulative number of MTCDs initiating RA. \n ( nMTCD = '+dircectory_nMTCD+', r = 10 )',fontsize=22)
plt.ylabel('Number of MTCDs initiating RA.',fontsize=22)
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