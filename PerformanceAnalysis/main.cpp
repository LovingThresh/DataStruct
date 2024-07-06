#include <iostream>
#include "PerformanceAnalysis.hpp"
int main() {
    constexpr int n = 4;
    double coefficients[] = { 2, 3, 5, 7, 11 };
    constexpr double x = 2.0;

    const double result = horner(coefficients, n, x);

    std::cout << "The value of the polynomial at x=" << x << " is: " << result << '\n';

    return 0;
}
