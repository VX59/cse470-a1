A=[1,3,4,5,6,3,1,1,9]
K=[3,3,3,2,2,2,4,4,4]
n,m = 3,3

Z=[]
for theta in range(m*n):
    z = 0
    for b in range(0,n):
        z+=A[(int(theta/n)*m)+b]*K[int(theta/n)+(m*b)]
    Z.append(z)

print(Z, sum(Z))

Z = 0
k=3
i,j = 1,1

for x in range(k*k):
    col = x%k
    kernel_row_index = i*n+j+(-n-1+(int)(x/k)*n)
    z = 0
    for y in range(k):
        Z += A[kernel_row_index+y]*K[col+k*y]

print(Z)
