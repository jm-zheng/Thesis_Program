import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
dircectory_nMTCD = "150K"
Axis_index = 2 # 0:50k 1:100K 2:150K
bar_width = 0.15  # 有四項數據
bar_width_align=bar_width/2

Group_nTransmit_Yaxis=[4000,10000,16000,33000,8000]  # 從30K: 16000開始
Group_nTransmit_Yaxis_gap=[500,1000,2000,3000,1000]  #


Uniform_Grouping_NOMA_allocation_RAtime = pd.read_csv("Goruping NOMA_allcation/Uniform/"+dircectory_nMTCD+"/with_earlydection_RAtime.csv", index_col=False)
Uniform_Preamble_allocation_RAtime = pd.read_csv("Premble_allocation/Uniform/"+dircectory_nMTCD+"/PreambleAllocation_RAtime.csv",index_col=False)
Dense_Grouping_NOMA_allocation_RAtime = pd.read_csv("Goruping NOMA_allcation/Dense/"+dircectory_nMTCD+"/Dense_with_earlydection_RAtime.csv",index_col=False)
Dense_Preamble_allocationDense_RAtime = pd.read_csv("Premble_allocation/Dense/"+dircectory_nMTCD+"/Dense_PreambleAllocation_RAtime.csv", index_col=False)


#aaa = Dense_Preamble_allocationDense_RAtime[Dense_Preamble_allocationDense_RAtime["group"].between(4,16)]
#bbb = Uniform_Preamble_allocation_RAtime[Uniform_Preamble_allocation_RAtime["group"].between(4,16)]
Dense_Preamble_allocationDense_RAtime =Dense_Preamble_allocationDense_RAtime[Dense_Preamble_allocationDense_RAtime["group"].between(1,3)]
Uniform_Preamble_allocation_RAtime =Uniform_Preamble_allocation_RAtime[Uniform_Preamble_allocation_RAtime["group"].between(1,3)]



mask1 = (Uniform_Grouping_NOMA_allocation_RAtime["group"] <=4)
mask2 = (Uniform_Grouping_NOMA_allocation_RAtime["group"] >=26) & (Uniform_Grouping_NOMA_allocation_RAtime["group"] <=30)
Uniform_Grouping_NOMA_allocation_RAtime=Uniform_Grouping_NOMA_allocation_RAtime[mask1 | mask2]

mask1 = (Dense_Grouping_NOMA_allocation_RAtime["group"] <=4)
mask2 = (Dense_Grouping_NOMA_allocation_RAtime["group"] >=26) & (Dense_Grouping_NOMA_allocation_RAtime["group"] <=30)
Dense_Grouping_NOMA_allocation_RAtime=Dense_Grouping_NOMA_allocation_RAtime[mask1 | mask2]


Dense_Grouping_NOMA_nTransmit_RA = Dense_Grouping_NOMA_allocation_RAtime["nTransmit_RA"].value_counts().sort_index()
Uniform_Grouping_NOMA_nTransmit_RA = Uniform_Grouping_NOMA_allocation_RAtime["nTransmit_RA"].value_counts().sort_index()
Dense_Preamble_allocationDense_nTransmit_RA = Dense_Preamble_allocationDense_RAtime["nTransmit_RA"].value_counts().sort_index()
Uniform_Preamble_allocation_nTransmit_RA = Uniform_Preamble_allocation_RAtime["nTransmit_RA"].value_counts().sort_index()



print(Uniform_Grouping_NOMA_allocation_RAtime["nTransmit_RA"].value_counts().sort_index())
print(Dense_Grouping_NOMA_allocation_RAtime["nTransmit_RA"].value_counts().sort_index())
print(Uniform_Preamble_allocation_nTransmit_RA)
print(Dense_Preamble_allocationDense_nTransmit_RA)
print(Uniform_Grouping_NOMA_allocation_RAtime["nTransmit_RA"].value_counts().sort_index().sum())
print(Dense_Grouping_NOMA_allocation_RAtime["nTransmit_RA"].value_counts().sort_index().sum())
print(Uniform_Preamble_allocation_nTransmit_RA.sum())
print(Dense_Preamble_allocationDense_nTransmit_RA.sum())


plt.bar(np.arange(1,12)-(bar_width*2-bar_width_align), Uniform_Grouping_NOMA_nTransmit_RA,width=bar_width,color="yellow",label="Grouping NOMA(Uniform)")
plt.bar(np.arange(1,12)-(bar_width*1-bar_width_align), Dense_Grouping_NOMA_nTransmit_RA,width=bar_width,color="yellowgreen",label="Grouping NOMA(Dense)")
plt.bar(np.arange(1,12)+(bar_width*1-bar_width_align), Uniform_Preamble_allocation_nTransmit_RA,width=bar_width,color="r",label="Preamble allocation(Uniform)")
plt.bar(np.arange(1,12)+(bar_width*2-bar_width_align), Dense_Preamble_allocationDense_nTransmit_RA,width=bar_width,color="tomato",label="Preamble allocation(Dense)")

plt.legend(loc='upper center',fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0.5)
plt.grid()
plt.title('The Influence of Different Position Distributions on the Number of transmissions \n ( nMTCD='+ dircectory_nMTCD+", ${M_{RA\_rt}}$=10)" ,fontsize=26)

plt.xticks(np.arange(1,12),fontsize=22)
plt.yticks(np.arange(0,Group_nTransmit_Yaxis[Axis_index],Group_nTransmit_Yaxis_gap[Axis_index]),fontsize=16)
plt.ylabel('Number of MTCDs ',fontsize=20)
plt.xlabel('RA transmission times',fontsize=20)


plt.show()

'''plt.bar(group_index, group_Mtcd)
plt.xticks(group_index)
plt.ylabel('Number of MTCD',fontsize=22)
plt.xlabel('Index of group',fontsize=22)
plt.show()'''