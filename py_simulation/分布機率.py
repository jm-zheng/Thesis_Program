import scipy.io.wavfile as wav
import matplotlib.pyplot as plt
import numpy as np
import random
import pylab as pl
import math


n_preamble=54
preamble=np.zeros(n_preamble,int)
backoff=960#隨機選擇後幾ms再選
windows_size=50
D2D_windows_size=40
retransmission_times=20#RA嘗試次數
D2D_retransmission_times=42#組內嘗試次數
alpha=3
beta=4
n_group=16
n_ogroup=3
n_emergency=3

RAO=10#每幾ms一次機會
T=10000#10秒 發起時間
t_total_time=250000#總模擬時間

total_time=np.zeros(t_total_time)
x = np.zeros((T),float)#x
y = np.zeros((T),float)#y


n=100000 #設備數量
device=np.zeros((n,8),int)#設備資訊

sparse=np.zeros(n_group)#統計各組內的設備數量
dense=np.zeros(n_group)#各組結束時間(全部完成)

for i in range(n_group):
    sparse[i]=6.25

for i in range(0,3,1):
    dense[i]=10.52
for i in range(3,n_group,1):
    dense[i]=5.26



fig = plt.figure()
plt.xlim([-0.5,n_group-0.5])
plt.ylim([0,11])
plt.xticks(np.linspace(0, n_group-1, n_group))
ax1 = fig.add_subplot(111)
ax1.bar([0,1],[sparse[0],sparse[1]],color='BLUE',align="edge",width=-0.35, label='Sparse')
for i in range(1,n_group-1,1):
    ax1.bar([i,i+1],[sparse[i],sparse[i+1]],color='BLUE',width=-0.35,align="edge")
#ax1.yaxis.label.set_color('red')
ax1.yaxis.zoom
#ax1.tick_params(axis='y', colors='blue')
ax1.set_ylabel('Probability (%)')
ax1.set_xlabel('Group Index')

ax2 = ax1.twinx()
#ax2.tick_params(axis='y', colors='red')
ax2.set_ylim(0, 11)
ax2.bar(0,[sparse[1],sparse[1]],color='BLUE',align="edge",width=-0.35, label='Sparse')
ax2.bar(0,[dense[0],dense[1]],color='RED',width=0.35, label='Dense',align="edge")
for i in range(1,n_group-1,1):
    #ax2.bar([i,i+1],[group_n[i],group_n[i+1]],color='BLUE',width=-0.35,align="edge")
    ax2.bar([i,i+1],[dense[i],dense[i+1]],width=0.35,color='red',align="edge")
#ax2.set_ylabel('Complete Duration (second)',color='RED')


plt.grid(color='#666666', linestyle='--', linewidth=1,alpha=0.3)
plt.legend(loc =1)#圖例
plt.show()

