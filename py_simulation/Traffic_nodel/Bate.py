# import random
import pandas as pd
import numpy as np
from scipy.stats import beta
import matplotlib.pyplot as plt
import random

# dataframe of result of RA Time related
RA_Time = pd.DataFrame(
    columns=['RA_init', 'RA_first', 'RA_success', 'RA_transmit'])


# The number of MTC Devices
nMTCD = int(10000)

# time duration of simulation, 1 RAO = 10ms
simRAO = 2000

# number of RA in every system frame
nMTCD_frame = np.zeros(simRAO)

# generate cdf of beta distribution
a = 3
b = 4
x = np.linspace(0, 1, simRAO)
z = np.linspace(0, 2000, simRAO)
beta_cdf = beta.cdf(x, a, b)
random.seed(2020)

print(beta_cdf)

for device in range(nMTCD):
    p = random.random()
    for frame in range(simRAO):
        if p < beta_cdf[frame]:
            nMTCD_frame[frame] += 1
            break
    print(f'current progress: {device}')
print(nMTCD_frame)

plt.plot(z,nMTCD_frame)