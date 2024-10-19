#include "a1.hpp"
#include <vector>
#include <numeric>
#include <unistd.h>
#include <omp.h>
#include <iostream>
#include <thread>
#include <cmath>

float kernel_filter(const std::vector<float>&A, const std::vector<float>&K, long long int m, long long int i, long long int j)
{
    float Zsum = 0;
    int k = 3;
    long int x = i-1;
    long int y = j-1;
    for (int a = 0; a < k; a++) 
    {
        for (int b = 0; b < k; b++)
        {
            for (int c = 0; c < k; c++)
            {
                Zsum += A[(x+a)*m+y+b]*K[c*k+b];
            }
        }
    }
    return  Zsum;
}

void filter2d(long long int n, long long int m, const std::vector<float>& K, std::vector<float>& A)
{
    // allocating 2m
    std::vector<float> Zi(m-2);
    std::vector<float> Zip(m-2);

    // first boundary .. calculate the initial values O(m/p)
    #pragma omp parallel for default(none) shared(A, K, m,       n, Zi, Zip) schedule(static)
    for (long long int j = 0; j < m-2; j++)
    {
        Zip[j] = kernel_filter(A, K, m, 1, j);
        if (n > 3)
        {
            Zi[j] = kernel_filter(A, K, m, 2, j);
        }
    }

    #pragma omp parallel default(none) shared(A, K, m, n, Zip, Zi)
    {
        // rows are processed sequentially O(n)
        for (long long int i = 3; i < n-1; i++)
        {
            #pragma omp for schedule(static) // O(m/p)
            for (long long int j = 1; j < m-1; j++)
            {
                int write_index = i-2;
                A[write_index*m+j] = Zip[j-1];
                Zip[j-1] = Zi[j-1];
                Zi[j-1] = kernel_filter(A, K, m, i, j);
            }
        }
    }
    
    // write Zi and Zip to A O(m/p)
    #pragma omp parallel for default(none) shared(A, K, m, n, Zi, Zip) schedule(static)
    for (long long int j = 1; j < m-1; j++)
    {
        if (n > 3)
        {
            A[(n-3)*m+j] = Zip[j-1];
        }
        A[(n-2)*m+j] = Zi[j-1];
    }

} // filter2d