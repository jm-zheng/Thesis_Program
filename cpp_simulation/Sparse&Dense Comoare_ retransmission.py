import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
dircectory_nMTCD = "50K"
MTCD_Position = "Dense"
Axis_index = 2 # 0:10k 1:30K 2:50k 3:100K

Group_nTransmit_Yaxis=[10000,30000,50000,1000000,1500000]  # 前5個sparse 後5個dense
Group_nTransmit_Yaxis_gap=[1000,3000,5000,10000,15000]  # 前5個sparse 後5個dense


Uniform_Grouping_NOMA_allocation_RAtime = pd.read_csv("Goruping NOMA_allcation/Uniform/"+dircectory_nMTCD+"/with_earlydection_RAtime.csv")
Dense_Grouping_NOMA_allocation_RAtime =pd.read_csv("Goruping NOMA_allcation/Dense/"+dircectory_nMTCD+"/Dense_with_earlydection_RAtime.csv")

Dense_Grouping_NOMA_nTransmit_RA = Dense_Grouping_NOMA_allocation_RAtime["nTransmit_RA"].value_counts().sort_index()
Uniform_Grouping_NOMA_nTransmit_RA = Uniform_Grouping_NOMA_allocation_RAtime["nTransmit_RA"].value_counts().sort_index()
print(Dense_Grouping_NOMA_nTransmit_RA)

print(Uniform_Grouping_NOMA_nTransmit_RA)
#Dense_Grouping_NOMA_nTransmit_RA.plot.bar(label='Proposal-Grouping NOMA(Dense)',color="blue")


plt.bar(np.arange(1,11), Uniform_Grouping_NOMA_nTransmit_RA,width=0.3,color="y")
plt.ylim(bottom=0)
plt.xlim(left=0.5)
plt.title('Distribution of MTCDs Position for '+MTCD_Position+' ( nMTCDs = '+ dircectory_nMTCD+" )",fontsize=26)

plt.xticks(np.arange(1,11))
plt.yticks(np.arange(0,Group_nTransmit_Yaxis[Axis_index],Group_nTransmit_Yaxis_gap[Axis_index]),fontsize=16)
plt.ylabel('Number of MTCDs ',fontsize=20)
plt.xlabel('i-th Group',fontsize=20)


plt.show()

'''plt.bar(group_index, group_Mtcd)
plt.xticks(group_index)
plt.ylabel('Number of MTCD',fontsize=22)
plt.xlabel('Index of group',fontsize=22)
plt.show()'''