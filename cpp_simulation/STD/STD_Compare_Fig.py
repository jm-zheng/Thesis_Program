import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
import os
dircectory_nMTCD = "10K"
Sim_RAO = 10+1  #1000 RAO = 10s  +1是因為圖表好看
MTCD_init_Yaxis_index = 0 # 0:10k 1:30K 2:50k
MTCD_init_Yaxis =[250,800,1500]
MTCD_init_Yaxis_gap =[25,50,100]


Pre_status_withGrant = pd.read_csv("Have_Grant/"+dircectory_nMTCD+"/PreStatus.csv")
CDF_MTCD_withGrant = pd.read_csv("Have_Grant/"+dircectory_nMTCD+"/stdsuccessdevice.csv")
Pre_status_NoGrant = pd.read_csv("No_Grant/"+dircectory_nMTCD+"/PreStatus.csv")
CDF_MTCD_NoGrant = pd.read_csv("No_Grant/"+dircectory_nMTCD+"/stdsuccessdevice.csv")

print(Pre_status_withGrant.head())
print(CDF_MTCD_withGrant)




# Cumulative MTCD
plt.plot(CDF_MTCD_NoGrant['success'],label='STD - without Grant')
plt.plot(CDF_MTCD_withGrant['success'],label='STD - with Grant')

plt.legend(fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0)
xlabe=[]
for i in range(Sim_RAO):
    xlabe.append(str(i))

print(xlabe)

plt.xticks(np.arange(0,1100,100),labels=xlabe,fontsize=16)
plt.yticks(np.arange(0,10000,1000),fontsize=16)

#plt.grid(True, ls=':')
plt.title('Cumulative Success MTCDs with nMTCD = '+dircectory_nMTCD,fontsize=22)
plt.ylabel('Number of Success MTCD',fontsize=22)
plt.xlabel('Simulation Time(second)',fontsize=22)
plt.grid()

plt.show()

# each RAO initate MTCD
plt.plot(Pre_status_NoGrant['initate MTCD'],label= 'STD - without Grant')
plt.plot(Pre_status_withGrant['initate MTCD'],label= 'STD - with Grant')

plt.legend(fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0)
plt.xticks(np.arange(0,1100,100),labels=xlabe,fontsize=16)
plt.yticks(np.arange(0,MTCD_init_Yaxis[MTCD_init_Yaxis_index],MTCD_init_Yaxis_gap[MTCD_init_Yaxis_index]),fontsize=16)
plt.title('Initate MTCDs for each RAO with nMTCD = '+dircectory_nMTCD,fontsize=22)
plt.ylabel('Number of MTCD',fontsize=22)
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