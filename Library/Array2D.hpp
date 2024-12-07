#pragma once
#include <iostream>
#include <algorithm> // 引入 std::max
#include <functional>

inline int recursiveMultiply(const int* array, const size_t size, const size_t index = 0)
{
    if (index == size)
    {
        // 递归基：所有维度处理完成，返回 1（乘法单位）
        return 1;
    }

    // 递归：当前值乘以剩余部分的乘积
    return array[index] * recursiveMultiply(array, size, index + 1);
}

// 递归模板实现行主映射
template <size_t S>
int rowMajorMapping(const int nRowsArray[S], const int nQueryArray[S], const size_t dimension)
{
    if (dimension == S - 1)
    {
        // 基本情况：最后一维直接返回索引值
        return nQueryArray[dimension];
    }

    // 递归：当前维度索引值 * 该维度的列数 + 下一维的递归值
    return nQueryArray[dimension] * recursiveMultiply(nRowsArray, S, dimension + 1) +
        rowMajorMapping<S>(nRowsArray, nQueryArray, dimension + 1);
}

template <size_t S>
int rowMajorMapping(const int nRowsArray[S], const int nQueryArray[S])
{
    return rowMajorMapping<S>(nRowsArray, nQueryArray, 0);
}

template <typename T, size_t S>
class Array2D
{
public:
    Array2D() = default;
    Array2D(int nRows, int nCols);
    Array2D(int nRow, const int nColsArray[S]);
    ~Array2D();

    void printArray2D() const;
    T* operator[](int row);
    const T* operator[](int row) const;

private:
    int m_nRow = 0;
    int m_nCol = 0; // 对于规则数组
    int* m_nColsPerRow = nullptr; // 对于不规则数组
    T** m_pArray = nullptr;
    bool isJagged = false; // 标记是否为不规则数组
};

// 规则数组构造函数
template <typename T, size_t S>
Array2D<T, S>::Array2D(const int nRows, const int nCols)
    : m_nRow(nRows), m_nCol(nCols), isJagged(false)
{
    m_pArray = new T * [m_nRow];
    for (int i = 0; i < m_nRow; i++)
    {
        m_pArray[i] = new T[m_nCol]();
    }
}

// 不规则数组构造函数
template <typename T, size_t S>
Array2D<T, S>::Array2D(const int nRow, const int nColsArray[S])
    : m_nRow(nRow), isJagged(true)
{
    if (m_nRow != static_cast<int>(S))
    {
        std::cout << "Array size does not match nRow." << '\n';
        // 可以考虑抛出异常或处理错误
    }

    // 分配存储每行列数的数组
    m_nColsPerRow = new int[m_nRow];
    m_nCol = 0; // 重置 m_nCol，因为每行可能不同

    // 复制每行的列数，并找到最大列数（如果需要）
    for (int i = 0; i < m_nRow; i++)
    {
        m_nColsPerRow[i] = nColsArray[i];
        if (nColsArray[i] > m_nCol)
            m_nCol = nColsArray[i];
    }

    // 分配二维数组
    m_pArray = new T * [m_nRow];
    for (int i = 0; i < m_nRow; i++)
    {
        m_pArray[i] = new T[m_nColsPerRow[i]]();
    }
}

// 析构函数
template <typename T, size_t S>
Array2D<T, S>::~Array2D()
{
    // 释放内存
    for (int i = 0; i < m_nRow; i++)
    {
        delete[] m_pArray[i];
    }
    delete[] m_pArray;

    if (isJagged)
    {
        delete[] m_nColsPerRow;
    }
}

// 打印二维数组
template <typename T, size_t S>
void Array2D<T, S>::printArray2D() const
{
    for (int i = 0; i < m_nRow; ++i)
    {
        const int currentCols = isJagged ? m_nColsPerRow[i] : m_nCol;
        for (int j = 0; j < currentCols; ++j)
        {
            std::cout << m_pArray[i][j] << " ";
        }
        std::cout << '\n';
    }
}

template <typename T, size_t S>
T* Array2D<T, S>::operator[](int row)
{
    if (row < 0 || row >= m_nRow)
    {
        throw std::out_of_range("Row index out of bounds");
    }
    return m_pArray[row];
}

template <typename T, size_t S>
const T* Array2D<T, S>::operator[](int row) const
{
    if (row < 0 || row >= m_nRow)
    {
        throw std::out_of_range("Row index out of bounds");
    }
    return m_pArray[row];
}
