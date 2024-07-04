#include "Recurse.hpp"

#include <complex>

inline unsigned int fibonacci_rec(const unsigned int x)
{
    if (x == 0)
        return 0;
    if (x == 1)
        return 1;
    return fibonacci_rec(x - 1) + fibonacci_rec(x - 2);
}

inline unsigned int factorial_rec(const unsigned int x)
{
    if (x <= 1)
        return 1;
    return x * factorial_rec(x - 1);
}


inline unsigned int fibonacci(const unsigned int x)
{
    if (x == 0)
        return 0;
    if (x == 1)
        return 1;
    unsigned int a = 0, b = 1, c = 0;
    for (unsigned int i = 2; i <= x; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}

inline unsigned int factorial(const unsigned int x)
{
    if (x <= 1)
        return 1;
    unsigned int result = 1;
    for (unsigned int i = 2; i <= x; i++)
        result *= i;
    return result;
}

// ReSharper disable once CppInconsistentNaming
unsigned int euclidGCD_rec(const unsigned int x, const unsigned int y)
{
    if (y == 0)
        return x;
    return euclidGCD_rec(y, x % y);
}

unsigned int callatz_rec(const unsigned int x)
{
    if (x % 2 == 0)
        return x / 2;
    return callatz_rec(3 * x + 1);
}

unsigned int callatz(const unsigned int x)
{
    if (x % 2 == 0)
        return x / 2;
    return (3 * x + 1) / 2;
}


unsigned int ackermann_rec(const unsigned int i, const unsigned int j)
{
    if (i == 1 && j >= 1)
        return static_cast<unsigned int>(std::pow(2, j));
    if (i >= 2 && j == 1)
        return ackermann_rec(i - 1, 2);
    return ackermann_rec(i - 1, ackermann_rec(i, j - 1));
}
