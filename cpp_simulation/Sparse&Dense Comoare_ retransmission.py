import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
dircectory_nMTCD = "50K"
MTCD_Position = "Dense"
Axis_index = 0 # 0:10k 1:30K 2:50k 3:100K
bar_width = 0.15  # 有四項數據
bar_width_align=bar_width/2

Group_nTransmit_Yaxis=[10000,30000,35000,100000,1500000]  # 前5個sparse 後5個dense
Group_nTransmit_Yaxis_gap=[1000,3000,5000,10000,15000]  # 前5個sparse 後5個dense


Uniform_Grouping_NOMA_allocation_RAtime = pd.read_csv("Goruping NOMA_allcation/Uniform/"+dircectory_nMTCD+"/with_earlydection_RAtime.csv", index_col=False)
Uniform_Preamble_allocation_RAtime = pd.read_csv("Premble_allocation/Uniform/"+dircectory_nMTCD+"/PreambleAllocation_RAtime.csv",index_col=False)
Dense_Grouping_NOMA_allocation_RAtime = pd.read_csv("Goruping NOMA_allcation/Dense/"+dircectory_nMTCD+"/Dense_with_earlydection_RAtime.csv",index_col=False)
Dense_Preamble_allocationDense_RAtime = pd.read_csv("Premble_allocation/Dense/"+dircectory_nMTCD+"/Dense_PreambleAllocation_RAtime.csv", index_col=False)



Dense_Preamble_allocationDense_RAtime =Dense_Preamble_allocationDense_RAtime[Dense_Preamble_allocationDense_RAtime["group"].between(1,3)]
Uniform_Preamble_allocation_RAtime =Uniform_Preamble_allocation_RAtime[Uniform_Preamble_allocation_RAtime["group"].between(1,3)]

mask1 = (Uniform_Grouping_NOMA_allocation_RAtime["group"] <=3)
mask2 = (Uniform_Grouping_NOMA_allocation_RAtime["group"] >=26) & (Uniform_Grouping_NOMA_allocation_RAtime["group"] <=29)
Uniform_Grouping_NOMA_allocation_RAtime=Uniform_Grouping_NOMA_allocation_RAtime[mask1 | mask2]

mask1 = (Dense_Grouping_NOMA_allocation_RAtime["group"] <=3)
mask2 = (Dense_Grouping_NOMA_allocation_RAtime["group"] >=26) & (Dense_Grouping_NOMA_allocation_RAtime["group"] <=29)
Dense_Grouping_NOMA_allocation_RAtime=Dense_Grouping_NOMA_allocation_RAtime[mask1 | mask2]


Dense_Grouping_NOMA_nTransmit_RA = Dense_Grouping_NOMA_allocation_RAtime["nTransmit_RA"].value_counts().sort_index()
Uniform_Grouping_NOMA_nTransmit_RA = Uniform_Grouping_NOMA_allocation_RAtime["nTransmit_RA"].value_counts().sort_index()
Dense_Preamble_allocationDense_nTransmit_RA = Dense_Preamble_allocationDense_RAtime["nTransmit_RA"].value_counts().sort_index()
Uniform_Preamble_allocation_nTransmit_RA = Uniform_Preamble_allocation_RAtime["nTransmit_RA"].value_counts().sort_index()




print(Uniform_Grouping_NOMA_allocation_RAtime["nTransmit_RA"].value_counts().sort_index())
print(Dense_Grouping_NOMA_allocation_RAtime["nTransmit_RA"].value_counts().sort_index())

print(Uniform_Preamble_allocation_RAtime["nTransmit_RA"].value_counts().sort_index())
print(Dense_Preamble_allocationDense_RAtime["nTransmit_RA"].value_counts().sort_index())


plt.bar(np.arange(1,12)-(bar_width*2-bar_width_align), Uniform_Grouping_NOMA_nTransmit_RA,width=bar_width,color="yellow",label="Grouping NOMA(Uniform)")
plt.bar(np.arange(1,12)-(bar_width*1-bar_width_align), Dense_Grouping_NOMA_nTransmit_RA,width=bar_width,color="yellowgreen",label="Grouping NOMA(Dense)")
plt.bar(np.arange(1,12)+(bar_width*1-bar_width_align), Uniform_Preamble_allocation_nTransmit_RA,width=bar_width,color="r",label="Preamble allocationDense(Uniform)")
plt.bar(np.arange(1,12)+(bar_width*2-bar_width_align), Dense_Preamble_allocationDense_nTransmit_RA,width=bar_width,color="tomato",label="Preamble allocationDense(Dense)")

plt.legend(loc='upper left',fontsize=16)
plt.ylim(bottom=0)
plt.xlim(left=0.5)
plt.title('Distribution of MTCDs Position for '+MTCD_Position+' ( nMTCDs = '+ dircectory_nMTCD+" )",fontsize=26)

plt.xticks(np.arange(1,12))
plt.yticks(np.arange(0,Group_nTransmit_Yaxis[Axis_index],Group_nTransmit_Yaxis_gap[Axis_index]),fontsize=16)
plt.ylabel('Number of MTCDs ',fontsize=20)
plt.xlabel('i-th Group',fontsize=20)


plt.show()

'''plt.bar(group_index, group_Mtcd)
plt.xticks(group_index)
plt.ylabel('Number of MTCD',fontsize=22)
plt.xlabel('Index of group',fontsize=22)
plt.show()'''