/*  Jacob
 *  DeRosa
 *  jderosa3
 */

#ifndef A1_HPP
#define A1_HPP

#include <vector>

long long int flatten_index(long long int i, long long int j, long long int m, long long int n);

std::vector<float> kernel_matmult(std::vector<float>&A_k, const std::vector<float>&K);

void filter2d(long long int n, long long int m, const std::vector<float>& K, std::vector<float>& A);

#endif // A1_HPP
