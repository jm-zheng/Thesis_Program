import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
import os
dircectory_nMTCD = "10K"
Sim_RAO = 15+1  #1000 RAO = 10s  +1是因為圖表好看

RA_time = pd.read_csv(dircectory_nMTCD+"/RATime.csv")
Pre_status = pd.read_csv(dircectory_nMTCD+"/PreStatus.csv")
CDF_MTCD = pd.read_csv(dircectory_nMTCD+"/Optimal_successdevice.csv")

print(RA_time.head())

print(Pre_status.head())

print(CDF_MTCD)


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

print(xlabe)

# each RAO Preamble status
plt.plot(Pre_status['collidePre'],label='Collision')
plt.plot(Pre_status['successPre'],label='Success')
plt.plot(Pre_status['grant fail'],label='Grant fail')

plt.legend(fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0)
plt.title('Preamble Status on each RAO for OptimalACB without SIB2 . nMTCD = '+dircectory_nMTCD,fontsize=22)
plt.xticks(np.arange(0,(Sim_RAO*100)+100,100),labels=xlabe,fontsize=16)
plt.yticks(np.arange(0,55,5),fontsize=16)
plt.ylabel('Number of preamble states',fontsize=22)
plt.xlabel('Simulation Time(second)',fontsize=22)
plt.grid()
plt.show()