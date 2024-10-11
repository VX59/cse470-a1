#include "a1.hpp"
#include <vector>
#include <numeric>
#include <unistd.h>
#include <omp.h>

// memory efficient
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
    std::vector<float> A_prime = A;
    // row parallelism
    #pragma omp parallel for default(none) shared(A, A_prime, K, m, n)
    for (long long int i = 1; i < n-1; i++)
    {
        // iterate column cells in a row
        for (long long int j = 1; j < m-1; j++)
        {
            // check if its on the border
            A_prime[i*m+j] = kernel_convolution(A, K, n, i, j);
        }
    }

    A = A_prime;
} // filter2d