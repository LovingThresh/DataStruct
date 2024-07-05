#ifndef STLFUNCTION_HPP
#define STLFUNCTION_HPP

#include <algorithm>
#include <functional>
#include <numeric>

template <typename  T>
T sum(T* plist, int n)
{
    T sumValue = T();
    return std::accumulate(plist, plist + n, sumValue);
}


template <typename  T>
T product(T* plist, int n)
{
    T theProduct = 1;
    return std::accumulate(plist, plist + n, theProduct, std::multiplies<T>());
}

template<typename  T >
void permutations(T list[], int k, int m)
{
    do
    {
        std::copy(list + k, list + m + 1, std::ostream_iterator<T>(std::cout, ""));
        std::cout << '\n';
    } while (std::next_permutation(list + k, list + m + 1));
}


#endif
