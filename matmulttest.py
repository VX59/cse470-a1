A=[9,9,9,
   1,1,1,
   2,2,2,
   3,3,3]
K=[1,2,3,1,2,3,1,2,3]
n,m = 3,3

i=1
j=1

Z = [0,0,0,0,0,0,0,0,0]
k = 3
x = i-1
y = j-1
print(x,y)
A_start_index = x*m+y
print(A_start_index)
for a in range(k):
    for b in range(k):
        for c in range(k):
            Z[a*k+b] += A[A_start_index+(a*m+b)]*K[c*k+b]


print(Z)
print(sum(Z))