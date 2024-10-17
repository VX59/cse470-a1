import numpy as np

Ai = [[6,7,8],
      [10,11,12],
      [14,15,16]]
k = [[1,1,1],
      [1,1,1],
      [1,1,1]]

Azi = np.linalg.matmul(Ai,k)
print(Azi)

print(sum(sum(Azi)))