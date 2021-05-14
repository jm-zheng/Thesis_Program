import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd

Axis_index = 2 # 0:50k 1:100K 2:150K
bar_width = 0.15  # 有四項數據
bar_width_align=bar_width/2
dircectory_nMTCD=["50K","100K","150K"]


Uniform_Grouping_NOMA_grantBroken_Yaxis=[]  # 從30K: 16000開始
Uniform_Grouping_NOMA_Broken_Yaxis=[]  #


Uniform_Grouping_NOMA_allocation_RAtime_50K = pd.read_csv("Goruping NOMA_allcation/Uniform/50K/with_earlydection_RAtime.csv", index_col=False)
Uniform_Preamble_allocation_RAtime_50K = pd.read_csv("Premble_allocation/Uniform/50K/PreambleAllocation_RAtime.csv",index_col=False)
Dense_Grouping_NOMA_allocation_RAtime_50K = pd.read_csv("Goruping NOMA_allcation/Dense/50K/Dense_with_earlydection_RAtime.csv",index_col=False)
Dense_Preamble_allocationDense_RAtime_50K = pd.read_csv("Premble_allocation/Dense/50K/Dense_PreambleAllocation_RAtime.csv", index_col=False)


Uniform_Grouping_NOMA_grantBroken_50K = (Uniform_Grouping_NOMA_allocation_RAtime_50K["MTCD_status"] == "Grant Broken")
Uniform_Grouping_NOMA_Broken_50K = (Uniform_Grouping_NOMA_allocation_RAtime_50K["MTCD_status"] == "Broken")
Dense_Grouping_NOMA_grantBroken_50K = (Dense_Grouping_NOMA_allocation_RAtime_50K["MTCD_status"] == "Grant Broken")
Dense_Grouping_NOMA_Broken_50K = (Dense_Grouping_NOMA_allocation_RAtime_50K["MTCD_status"] == "Broken")
Uniform_Preamble_grantBroken_50K = (Uniform_Preamble_allocation_RAtime_50K["MTCD_RA_status "] == "Grant Broken")
Uniform_Preamble_Broken_50K = (Uniform_Preamble_allocation_RAtime_50K["MTCD_RA_status "] == "Broken")
Dense_Preamble_grantBroken_50K = (Dense_Preamble_allocationDense_RAtime_50K["MTCD_RA_status "] == "Grant Broken")
Dense_Preamble_Broken_50K = (Dense_Preamble_allocationDense_RAtime_50K["MTCD_RA_status "] == "Broken")

print("Unifrom")
print(len(Uniform_Grouping_NOMA_allocation_RAtime_50K[Uniform_Grouping_NOMA_grantBroken_50K]))
print(len(Uniform_Grouping_NOMA_allocation_RAtime_50K[Uniform_Grouping_NOMA_Broken_50K]))
print(len(Uniform_Preamble_allocation_RAtime_50K[Uniform_Preamble_grantBroken_50K]))
print(len(Uniform_Preamble_allocation_RAtime_50K[Uniform_Preamble_Broken_50K]))
print("dense")
print(len(Dense_Grouping_NOMA_allocation_RAtime_50K[Dense_Grouping_NOMA_grantBroken_50K]))
print(len(Dense_Grouping_NOMA_allocation_RAtime_50K[Dense_Grouping_NOMA_Broken_50K]))
print(len(Dense_Preamble_allocationDense_RAtime_50K[Dense_Preamble_grantBroken_50K]))
print(len(Dense_Preamble_allocationDense_RAtime_50K[Dense_Preamble_Broken_50K]))

Uniform_Grouping_NOMA_grantBroken_Yaxis.append(len(Dense_Grouping_NOMA_allocation_RAtime_50K[Dense_Grouping_NOMA_grantBroken_50K]))
Uniform_Grouping_NOMA_Broken_Yaxis.append(len(Uniform_Grouping_NOMA_allocation_RAtime_50K[Uniform_Grouping_NOMA_Broken_50K]))

Uniform_Grouping_NOMA_allocation_RAtime_100K = pd.read_csv("Goruping NOMA_allcation/Uniform/100K/with_earlydection_RAtime.csv", index_col=False)
Uniform_Preamble_allocation_RAtime_100K = pd.read_csv("Premble_allocation/Uniform/100K/PreambleAllocation_RAtime.csv",index_col=False)
Dense_Grouping_NOMA_allocation_RAtime_100K = pd.read_csv("Goruping NOMA_allcation/Dense/100K/Dense_with_earlydection_RAtime.csv",index_col=False)
Dense_Preamble_allocationDense_RAtime_100K = pd.read_csv("Premble_allocation/Dense/100K/Dense_PreambleAllocation_RAtime.csv", index_col=False)


Uniform_Grouping_NOMA_grantBroken_100K = (Uniform_Grouping_NOMA_allocation_RAtime_100K["MTCD_status"] == "Grant Broken")
Uniform_Grouping_NOMA_Broken_100K = (Uniform_Grouping_NOMA_allocation_RAtime_100K["MTCD_status"] == "Broken")
Dense_Grouping_NOMA_grantBroken_100K = (Dense_Grouping_NOMA_allocation_RAtime_100K["MTCD_status"] == "Grant Broken")
Dense_Grouping_NOMA_Broken_100K = (Dense_Grouping_NOMA_allocation_RAtime_100K["MTCD_status"] == "Broken")
Uniform_Preamble_grantBroken_100K = (Uniform_Preamble_allocation_RAtime_100K["MTCD_RA_status "] == "Grant Broken")
Uniform_Preamble_Broken_100K = (Uniform_Preamble_allocation_RAtime_100K["MTCD_RA_status "] == "Broken")
Dense_Preamble_grantBroken_100K = (Dense_Preamble_allocationDense_RAtime_100K["MTCD_RA_status "] == "Grant Broken")
Dense_Preamble_Broken_100K = (Dense_Preamble_allocationDense_RAtime_100K["MTCD_RA_status "] == "Broken")

print("Unifrom")
print(len(Uniform_Grouping_NOMA_allocation_RAtime_100K[Uniform_Grouping_NOMA_grantBroken_100K]))
print(len(Uniform_Grouping_NOMA_allocation_RAtime_100K[Uniform_Grouping_NOMA_Broken_100K]))
print(len(Uniform_Preamble_allocation_RAtime_100K[Uniform_Preamble_grantBroken_100K]))
print(len(Uniform_Preamble_allocation_RAtime_100K[Uniform_Preamble_Broken_100K]))
print("dense")
print(len(Dense_Grouping_NOMA_allocation_RAtime_100K[Dense_Grouping_NOMA_grantBroken_100K]))
print(len(Dense_Grouping_NOMA_allocation_RAtime_100K[Dense_Grouping_NOMA_Broken_100K]))
print(len(Dense_Preamble_allocationDense_RAtime_100K[Dense_Preamble_grantBroken_100K]))
print(len(Dense_Preamble_allocationDense_RAtime_100K[Dense_Preamble_Broken_100K]))

Uniform_Grouping_NOMA_grantBroken_Yaxis.append(len(Uniform_Grouping_NOMA_allocation_RAtime_100K[Uniform_Grouping_NOMA_grantBroken_100K]))
Uniform_Grouping_NOMA_Broken_Yaxis.append(len(Uniform_Grouping_NOMA_allocation_RAtime_100K[Uniform_Grouping_NOMA_Broken_100K]))

Uniform_Grouping_NOMA_allocation_RAtime_150K = pd.read_csv("Goruping NOMA_allcation/Uniform/150K/with_earlydection_RAtime.csv", index_col=False)
Uniform_Preamble_allocation_RAtime_150K = pd.read_csv("Premble_allocation/Uniform/150K/PreambleAllocation_RAtime.csv",index_col=False)
Dense_Grouping_NOMA_allocation_RAtime_150K = pd.read_csv("Goruping NOMA_allcation/Dense/150K/Dense_with_earlydection_RAtime.csv",index_col=False)
Dense_Preamble_allocationDense_RAtime_150K = pd.read_csv("Premble_allocation/Dense/150K/Dense_PreambleAllocation_RAtime.csv", index_col=False)


Uniform_Grouping_NOMA_grantBroken_150K = (Uniform_Grouping_NOMA_allocation_RAtime_150K["MTCD_status"] == "Grant Broken")
Uniform_Grouping_NOMA_Broken_150K = (Uniform_Grouping_NOMA_allocation_RAtime_150K["MTCD_status"] == "Broken")
Dense_Grouping_NOMA_grantBroken_150K = (Dense_Grouping_NOMA_allocation_RAtime_150K["MTCD_status"] == "Grant Broken")
Dense_Grouping_NOMA_Broken_150K = (Dense_Grouping_NOMA_allocation_RAtime_150K["MTCD_status"] == "Broken")
Uniform_Preamble_grantBroken_150K = (Uniform_Preamble_allocation_RAtime_150K["MTCD_RA_status "] == "Grant Broken")
Uniform_Preamble_Broken_150K = (Uniform_Preamble_allocation_RAtime_150K["MTCD_RA_status "] == "Broken")
Dense_Preamble_grantBroken_150K = (Dense_Preamble_allocationDense_RAtime_150K["MTCD_RA_status "] == "Grant Broken")
Dense_Preamble_Broken_150K = (Dense_Preamble_allocationDense_RAtime_150K["MTCD_RA_status "] == "Broken")

print("Unifrom")
print(len(Uniform_Grouping_NOMA_allocation_RAtime_150K[Uniform_Grouping_NOMA_grantBroken_150K]))
print(len(Uniform_Grouping_NOMA_allocation_RAtime_150K[Uniform_Grouping_NOMA_Broken_150K]))
print(len(Uniform_Preamble_allocation_RAtime_150K[Uniform_Preamble_grantBroken_150K]))
print(len(Uniform_Preamble_allocation_RAtime_150K[Uniform_Preamble_Broken_150K]))
print("dense")
print(len(Dense_Grouping_NOMA_allocation_RAtime_150K[Dense_Grouping_NOMA_grantBroken_150K]))
print(len(Dense_Grouping_NOMA_allocation_RAtime_150K[Dense_Grouping_NOMA_Broken_150K]))
print(len(Dense_Preamble_allocationDense_RAtime_150K[Dense_Preamble_grantBroken_150K]))
print(len(Dense_Preamble_allocationDense_RAtime_150K[Dense_Preamble_Broken_150K]))

Uniform_Grouping_NOMA_grantBroken_Yaxis.append(len(Uniform_Grouping_NOMA_allocation_RAtime_150K[Uniform_Grouping_NOMA_grantBroken_150K]))
Uniform_Grouping_NOMA_Broken_Yaxis.append(len(Uniform_Grouping_NOMA_allocation_RAtime_150K[Uniform_Grouping_NOMA_Broken_150K]))
'''
plt.bar(x=np.arange(len(dircectory_nMTCD))-(bar_width*2-bar_width_align),height=Uniform_Grouping_NOMA_Broken_Yaxis ,width=bar_width,color="r",label="Broken")
plt.bar(x=np.arange(len(dircectory_nMTCD))-(bar_width*2-bar_width_align),height=Uniform_Grouping_NOMA_grantBroken_Yaxis,width=bar_width,color="yellow",label="Grouping NOMA(Uniform)")

for x, y in enumerate(Uniform_Grouping_NOMA_Broken_Yaxis):
    plt.text(x, y + 100, '%s' % y, ha='center', va='bottom')
for x, y in enumerate(Uniform_Grouping_NOMA_grantBroken_Yaxis):
    plt.text(x, y + 100, '%s' % y, ha='center', va='top')

#plt.bar(np.arange(1,12)-(bar_width*1-bar_width_align), Dense_Grouping_NOMA_nTransmit_RA,width=bar_width,color="yellowgreen",label="Grouping NOMA(Dense)")
#plt.bar(np.arange(1,12)+(bar_width*1-bar_width_align), Uniform_Preamble_allocation_nTransmit_RA,width=bar_width,color="r",label="Preamble allocationDense(Uniform)")
#plt.bar(np.arange(1,12)+(bar_width*2-bar_width_align), Dense_Preamble_allocationDense_nTransmit_RA,width=bar_width,color="tomato",label="Preamble allocationDense(Dense)")

plt.legend(loc='upper center',fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=-0.5)
plt.grid()
plt.title("The Influence of Different Position Distributions on the Number of transmissions \n ( nMTCD= 10K, r=10) ",fontsize=26)


plt.yticks(np.arange(0,4000,200),fontsize=16)
plt.ylabel('Number of MTCDs ',fontsize=20)
plt.xlabel('RA transmission times',fontsize=20)


plt.show()
'''
'''plt.bar(group_index, group_Mtcd)
plt.xticks(group_index)
plt.ylabel('Number of MTCD',fontsize=22)
plt.xlabel('Index of group',fontsize=22)
plt.show()'''