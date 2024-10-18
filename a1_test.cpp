#include <algorithm>
#include <chrono>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

#include "a1.hpp"


int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "usage: " << argv[0] << " n m" << std::endl;
        return -1;
    }

    long long int n = std::atoll(argv[1]);
    long long int m = std::atoll(argv[2]);

    std::vector<float> A(n * m);

    const int KSIZE = 3 * 3;
    std::vector<float> K(KSIZE);

    // we hard-code const to be deterministic
    std::mt19937 gen(666);
    std::lognormal_distribution<float> N(0.0, 10.0);
    std::generate(std::begin(A), std::end(A), std::bind(N, gen));
    std::generate(std::begin(K), std::end(K), std::bind(N, gen));

    // now running your awesome code from a0.hpp
    auto t0 = std::chrono::system_clock::now();

    for (long long int i = 0; i < n; i++)
    {
        for (long long int j = 0; j < m; j++)
        {
            std::cout << (float)A[i*m+j] << " ";

        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (long long int i = 0; i < 3; i++)
    {
        for (long long int j = 0; j < 3; j++)
        {
            std::cout << (float)K[i*m+j] << " ";

        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    filter2d(n, m, K, A);

    auto t1 = std::chrono::system_clock::now();

    auto elapsed_par = std::chrono::duration<double>(t1 - t0);
    std::cout << elapsed_par.count() << std::endl;

    for (long long int i = 0; i < n; i++)
    {
        for (long long int j = 0; j < m; j++)
        {
            std::cout << (float)A[i*m+j] << " ";

        }
        std::cout << std::endl;
    }
    return 0;
} // main
