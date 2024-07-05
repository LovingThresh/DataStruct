// STLDataStructures.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

#include "STLFunction.hpp"

int main()
{
    int list[] = { 1, 2, 3, 4, 5 };
    constexpr int n = std::size(list);
    const int sumValue = sum(list, n);
    std::cout << "sumValue = " << sumValue << '\n';

    const int mulValue = product(list, n);
    std::cout << "mulValue = " << mulValue << '\n';

    permutations(list, 0, n - 1);
    return 0;
}
