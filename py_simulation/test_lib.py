

import numpy as np
import matplotlib.pyplot as plt
import time
colormap = np.array(['chartreuse', 'aqua','burlywood','cadetblue','chocolate','cornflowerblue','black','crimson','blue','brown',
                     'cyan', 'darkblue','darkcyan','darkgoldenrod','darkgreen','cornflowerblue','darkkhaki','darkolivegreen','darkred','darkseagreen',
                     'darkviolet', 'deepskyblue','dimgray','darkgoldenrod','dodgerblue','cornflowerblue','firebrick','green','fuchsia','gold',
                     'gray', 'greenyellow','hotpink','mediumaquamarine','dodgerblue','orange','magenta','lawngreen','maroon','lightcoral',
                     'royalblue', 'olivedrab', 'seagreen', 'mediumvioletred', 'skyblue', 'peru', 'slategray','thistle', 'purple', 'yellowgreen',
            ])


'''a=50
y=np.unique(a)
print(y[1])'''




x = list(range(1, 51))
for index, node in enumerate(x):
    plt.scatter(node, node, c=colormap[index])
aaa = np.array([[1,2,3],[1,2,5]])
print(aaa)
plt.show()






