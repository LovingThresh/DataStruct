#ifndef RECURSE_HPP
#define RECURSE_HPP

inline unsigned int Fibonacci(const unsigned int x)
{
    if (x == 0)
        return 0;
    if (x == 1)
        return 1;
    return Fibonacci(x - 1) + Fibonacci(x - 2);
}

inline unsigned int factorial(const unsigned int x)
{
    if (x <= 1)
        return 1;
    return x * factorial(x - 1);
}

template <typename T>
T sum(T x[], const int n)
{
    if (n <= 0)
        return 0;
    return x[n - 1] + sum(x, n - 1);
}


#endif
