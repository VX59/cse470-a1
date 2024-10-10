A=[1,1,1,2,2,2,3,3,3]
B=[3,3,3,2,2,2,4,4,4]
n,m = 3,3

Z=[]
for theta in range(m*n):
    z = 0
    for b in range(0,n):
        z+=A[(int(theta/n)*m)+b]*B[int(theta/n)+(m*b)]
    Z.append(z)

print(Z)
