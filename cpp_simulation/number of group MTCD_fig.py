import matplotlib.pyplot as plt
import random
import numpy as np
import pandas as pd
dircectory_nMTCD = "30K"
MTCD_Position = "Dense"
Axis_index = 7 # 0:10k 1:30K 2:50k 3:100K

nMTCD_group_Yaxis=[300,700,1100,2300,3500,450,1200,2000]  # 前5個sparse 後5個dense
nMTCD_group_Yaxis_gap=[50,100,100,500,500,50,100,200]  # 前5個sparse 後5個dense


#Grouping_NOMA_allocation_RAtime = pd.read_csv("Goruping NOMA_allcation/Sparse/"+dircectory_nMTCD+"/with_earlydection_RAtime.csv")
Grouping_NOMA_allocation_RAtime =pd.read_csv("Goruping NOMA_allcation/Dense/"+dircectory_nMTCD+"/Dense_with_earlydection_RAtime.csv")

nMTCD_group = Grouping_NOMA_allocation_RAtime["group"].value_counts().sort_index().plot.bar()



plt.ylim(bottom=0)
plt.xlim(left=-1)
plt.title('Distribution of MTCDs Position for '+MTCD_Position+' ( nMTCDs = '+ dircectory_nMTCD+" )",fontsize=26)

plt.xticks(rotation=0)
plt.yticks(np.arange(0,nMTCD_group_Yaxis[Axis_index],nMTCD_group_Yaxis_gap[Axis_index]),fontsize=16)
plt.ylabel('Number of MTCDs ',fontsize=20)
plt.xlabel('i-th Group',fontsize=20)


plt.show()

'''plt.bar(group_index, group_Mtcd)
plt.xticks(group_index)
plt.ylabel('Number of MTCD',fontsize=22)
plt.xlabel('Index of group',fontsize=22)
plt.show()'''