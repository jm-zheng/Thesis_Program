import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
import os
dircectory_nMTCD = "10K"
Sim_RAO = 35+1  #1000 RAO = 10s  +1是因為圖表好看

Yaxis_index = 2 # 0:10k 1:30K 2:50k
Pre_status_withGrant = pd.read_csv("Have_Grant/"+dircectory_nMTCD+"/PreStatus.csv")

Pre_status_NoGrant = pd.read_csv("No_Grant/"+dircectory_nMTCD+"/PreStatus.csv")

print(Pre_status_withGrant.head())

print(Pre_status_NoGrant.head())




'''
# Cumulative MTCD
plt.plot(CDF_MTCD['success'],label='STD with Grant')
plt.legend(fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0)
plt.xticks(np.arange(0,1100,100))
plt.yticks(np.arange(0,10000,1000))
#plt.grid(True, ls=':')
plt.title('Cumulative Success MTCDs with nMTCD = 10000',fontsize=22)
plt.ylabel('Number of MTCD',fontsize=22)
plt.xlabel('i-th RAO',fontsize=22)
plt.grid()

plt.show()

# each RAO initate MTCD
plt.plot(Pre_status['initate MTCD'],label= 'STD with Grant')
plt.legend(fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0)
plt.xticks(np.arange(0,1100,50))
plt.yticks(np.arange(0,250,25))
plt.title('Initate MTCDs for each RAO with nMTCD = 10000',fontsize=22)
plt.ylabel('Number of MTCD',fontsize=22)
plt.xlabel('i-th RAO',fontsize=22)
plt.grid()
plt.show()
'''
xlabe=[]
for i in range(Sim_RAO):
    xlabe.append(str(i))
# each RAO Preamble status
plt.plot(Pre_status_NoGrant['collidePre'],label='Collision-without Grant')
plt.plot(Pre_status_NoGrant['successPre'],label='Success-without Grant')
plt.plot(Pre_status_NoGrant['grant fail'],label='Grant fail-without Grant')
plt.plot(Pre_status_withGrant['collidePre'],label='Collision-wit Grant',linestyle='--')
plt.plot(Pre_status_withGrant['successPre'],label='Success-with Grant',linestyle='--')
plt.plot(Pre_status_withGrant['grant fail'],label='Grant fail-with Grant',linestyle='--')

plt.legend(fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0)
plt.title('Preamble Status for each RAO with nMTCD = '+dircectory_nMTCD,fontsize=22)
plt.xticks(np.arange(0,Sim_RAO*100+100,100),labels=xlabe,fontsize=16)
plt.yticks(np.arange(0,55,5))
plt.ylabel('Number of Preamble',fontsize=22)
plt.xlabel('j-th RAO',fontsize=22)
plt.grid()
plt.show()