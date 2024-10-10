/*  Jacob
 *  DeRosa
 *  jderosa3
 */

#ifndef A1_HPP
#define A1_HPP

#include <vector>

long long int flatten_index(long long int i, long long int j, long long int m, long long int n) 
{
    return i*m-(n-j);
}

std::vector<float> kernel_matmult(std::vector<float>&A_k, const std::vector<float>&K) // O(k^3) -> k=3 always : O(1)
{   
    int k = 3;
    std::vector<float> Z;
    for(int theta = 0; theta < k*k; theta++)
    {
        float z = 0;
        for (int b = 0; b < k; b++)
        {
            z += A_k[(int)(theta/k)*k+b] * K[(int)(theta/k)+k*b];
        }
        Z.push_back(z);
    }
    return Z;
}

void filter2d(long long int n, long long int m, const std::vector<float>& K, std::vector<float>& A)
{
    // iterate rows
    #pragma omp parallel for collapse(2)
    for (long long int i = 0; i < n; i+=m)
    {
        // iterate column cells in a row
        for (long long int j = i; j < i+m; j++)
        {
            // check if its on the border
            if (i != 0 && i != n-1 && j !=0 && j != i+m-1)
            {
                long long int theta = flatten_index(i,j,m,n);
                // make A'
                //[(i-1,j-1), (i-1,j), (i-1,j+1), (i,j-1), (i,j), (i,j+1), (i+1,j-1), (i+1,j), (i+1,j+1)] .... O(1)
                std::vector<float> A_k = {A[flatten_index(i-1,j-1,m,n)], A[flatten_index(i-1,j,m,n)], A[flatten_index(i-1,j+1,m,n)],
                                          A[flatten_index(i,j-1,m,n)],   A[flatten_index(i,j,m,n)],   A[flatten_index(i,j+1,m,n)],
                                          A[flatten_index(i+1,j-1,m,n)], A[flatten_index(i+1,j,m,n)], A[flatten_index(i+1,j+1,m,n)]};
                std::vector<float> Z = kernel_matmult(A_k, K);
                float A_prime = std::accumulate(Z.begin(),Z.end(),0);
                A[theta] = A_prime;
            }
        }
    }
} // filter2d

#endif // A1_HPP
