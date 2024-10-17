#include "a1.hpp"
#include <vector>
#include <numeric>
#include <unistd.h>
#include <omp.h>
#include <iostream>
#include <thread>
#include <cmath>
// more memory efficient?
float kernel_convolution(const std::vector<float>&A, const std::vector<float>&K, long long int n, long long int i, long long int j)
{
    __uint8_t k = 3;
    float Zsum = 0;
    for (__uint8_t x = 0; x < k*k; x++) {
        __uint8_t col = (__uint8_t)(x%k);
        long long int kernel_row_index = i*n+j+(-n-1+(int)(x/k)*n);
        for (__uint8_t y = 0; y < k; y++) {
            Zsum += A[kernel_row_index+y]*K[col+k*y];
        }
    }
    return Zsum;
}

void filter2d(long long int n, long long int m, const std::vector<float>& K, std::vector<float>& A)
{

    long long int r = n/16;
    
    #pragma omp parallel for default(none) schedule(dynamic) shared(A,K,m,n,r)
    for (long long int q = 0; q < n; q+=r)
    {
        // allocating 2m
        std::vector<float> Zi(A.begin(),A.begin()+m-2);
        std::vector<float> Zip(A.begin(),A.begin()+m-2);

        // first boundary .. calculate the initial values
        #pragma omp parallel for default(none) shared(A, K, m, n, Zi, Zip,q) schedule(dynamic)
        for (long long int j = 0; j < m-2; j++)
        {
            Zip[j] = kernel_convolution(A, K, n, q+1, j);
            Zi[j] = kernel_convolution(A, K, n, q+2, j);
        }

        // execute the rows

        for (long long int i = 1; i < q+r-1; i++)
        {
            if (i > 2)
            {
                #pragma omp parallel for default(none) shared(A, K, m, n, Zi, Zip, i) schedule(dynamic)
                for (long long int j = 1; j < m-1; j++)
                {
                    int write_index = i-2;
                    A[write_index*m+j] = Zip[j-1];
                    Zip[j-1] = Zi[j-1];
                    Zi[j-1] = kernel_convolution(A, K, n, i, j);
                }
            }
        }
        
        // write Zi and Zip to A
        #pragma omp parallel for default(none) shared(A, K, m, n, Zi, Zip,q,r) schedule(dynamic)
        for (long long int j = 1; j < m-1; j++)
        {
            A[(q+r-3)*m+j] = Zip[j-1];
            A[(q+r-2)*m+j] = Zi[j-1];
        }
    }

} // filter2d