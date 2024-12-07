#include <iostream>
#include "../Library/Array2D.hpp"

int main()
{
    int x[3][5];
    std::cout << sizeof(x) << '\n';

    constexpr int rows = 3;
    constexpr int cols = 5;

    int** px = new int*[rows];
    for (int i = 0; i < rows; i++)
    {
        px[i] = new int[cols];
        if (!px[i])
        {
            std::cerr << "Memory allocation failed!" << '\n';
            return -1;
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            px[i][j] = i * cols + j; // 设置值
        }
    }

    // 计算内存大小
    constexpr int pointerArraySize = sizeof(px); // 指针数组的大小
    constexpr int allocatedMemorySize = cols * rows * sizeof(int); // 动态分配的数据大小
    std::cout << "Total memory size: " << pointerArraySize + allocatedMemorySize << " bytes" << '\n';

    // 释放内存
    for (int i = 0; i < rows; i++)
    {
        delete[] px[i];
    }
    delete[] px;

    // 创建规则数组 3x4
    const Array2D<int, 3> regularArray(3, 4);
    // 初始化一些值
    regularArray.printArray2D();

    // 创建不规则数组，3 行，列数分别为 2, 4, 3
    int colsPerRow[5] = {6, 3, 4, 2, 7};
    Array2D<int, 5> jaggedArray(5, colsPerRow);
    // 初始化一些值
    jaggedArray.printArray2D();

    jaggedArray[2][3] = 5;
    jaggedArray[4][6] = jaggedArray[2][3] + 2;
    jaggedArray[1][1] = 3;

    std::cout << jaggedArray[2][3] << '\n';
    std::cout << jaggedArray[4][6] << '\n';
    std::cout << jaggedArray[1][1] << '\n';

    constexpr size_t S = 4; // 维度数
    constexpr int dimensions[S] = {2, 3, 2, 2}; // 每维的大小
    constexpr int query[S] = {1, 1, 1, 1}; // 查询索引
    constexpr int result = 1 * 3 * 2 * 2 + 1 * 2 * 2 + 1 * 2 + 1;
    std::cout << "result: " << result << '\n';
    std::cout << rowMajorMapping<S>(dimensions, query) << '\n';
}
