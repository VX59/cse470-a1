import numpy as np

Ai = [[1,1,1],
      [2,2,2],
      [3,3,3]]
k = [[1,2,3],
      [1,2,3],
      [1,2,3]]

Azi = np.linalg.matmul(Ai,k)
print(Azi)

print(sum(sum(Azi)))