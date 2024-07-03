#ifndef RECURSE_HPP
#define RECURSE_HPP

#include <algorithm>
#include <iostream>
#include <ostream>

inline unsigned int fibonacci_rec(unsigned int x);
inline unsigned int factorial_rec(unsigned int x);
unsigned int callatz_rec(unsigned int x);
unsigned int ackermann_rec(unsigned int i, unsigned int j);


unsigned int fibonacci(unsigned int x);
unsigned int factorial(unsigned int x);
unsigned int callatz(unsigned int x);

template <typename T>
T sum(T x[], const int n)
{
    if (n <= 0)
        return 0;
    return x[n - 1] + sum(x, n - 1);
}

template <typename T>
void permutations(T list[], const int k, const int m)
{
    if (k == m) {
        std::copy(list, list + m + 1, std::ostream_iterator<T>(std::cout, ""));
        std::cout << '\n';
    }
    else
    {
        for (int i = k; i <= m; i++)
        {
            swap(list[k], list[i]);
            permutations(list, k + 1, m);
            swap(list[k], list[i]);
        }
    }
}

#endif
