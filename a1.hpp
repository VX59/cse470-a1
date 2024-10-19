/*  Jacob
 *  DeRosa
 *  jderosa3
 */

#ifndef A1_HPP
#define A1_HPP

#include <vector>

float kernel_filter(const std::vector<float>&A, const std::vector<float>&K, long long int m, long long int i, long long int j);
void filter2d(long long int n, long long int m, const std::vector<float>& K, std::vector<float>& A);

#endif // A1_HPP