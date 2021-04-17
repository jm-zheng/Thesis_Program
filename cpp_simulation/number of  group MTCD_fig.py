import matplotlib.pyplot as plt
import random
import numpy as np



nMTCD = 50000
#random.seed(2020)

group_Mtcd = []
group_index= []

for group in range(50):
    group_Mtcd.append(int(0))

for group in range(50):
    group_index.append(group)

print(group_Mtcd)
print(group_index)



for i in range(10):
    random.seed(i)
    for device in range(nMTCD):
        x= random.randint(0,52)
        x = x % 50
        for group in range(50):
            if x == (group):
                group_Mtcd[group] += 1
                break

for group in range(50):
    group_Mtcd[group]= group_Mtcd[group]/10


print(group_Mtcd)
print(len(group_Mtcd))
print(len(group_index))
plt.bar(group_index, group_Mtcd)
plt.xticks(group_index)
plt.ylabel('Number of MTCD',fontsize=22)
plt.xlabel('Index of group',fontsize=22)
plt.show()