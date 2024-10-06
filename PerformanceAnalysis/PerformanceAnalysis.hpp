#ifndef PERFORMANCEANALYSIS_HPP
#define PERFORMANCEANALYSIS_HPP
#include <algorithm>
#include <future>

#include "../DataStruct/Recurse.hpp"

template <typename T>
int indexOfMax(T a[], const int n)
{
    int indexOfMax = 0;
    for (int i = 1; i < n; i++)
    {
        if (a[i] > a[indexOfMax])
            indexOfMax = i;
    }
    return indexOfMax;
}

// program 2-3
template <typename T>
T ployEval(T coeff[], const int n, const T& x)
{
    T y = 1, value = coeff[0];
    for (int i = 1; i < n + 1; i++)
    {
        y *= x;
        value += coeff[i] * y;
    }
    return value;
}

// program 2-4
template <typename T>
T horner(T coeff[], const int n, const T& x)
{
    T value = coeff[n];
    for (int i = n - 1; i >= 0; i--)
    {
        value = value * x + coeff[i];
    }
    return value;
}

// program 2-5
template <typename T >
void rank(T a[], const int n, int r[])
{
    for (int i = 0; i < n; i++)
    {
        r[i] = 0;
    }

    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (a[j] <= a[i])
                r[i]++;
            else
                r[j]++;
        }
    }
}

// program 2-6
template <typename T>
void rearrange(T a[], const int n, int r[])
{
    T* u = new T[n]; // temp array u
    for (int i = 0; i < n; i++)
        u[r[i]] = a[i];
    for (int i = 0; i < n; i++)
        a[i] = u[i];
    delete[] u;
}

template <typename T>
void rankSort(T a[], const int n, int r[])
{
    rank(a, n, r);
    rearrange(a, n, r);
}

// program 2-7
template <typename T>
void selectionSort(T a[], const int n)
{
    for (int size = n; size > 1; size--)
    {
        int j = indexOfMax(a, size);
        std::swap(a[j], a[size - 1]);
    }
}

// program 2-8
template <typename T>
void bubble(T a[], const int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] > a[i + 1])
            std::swap(a[i], a[i + 1]);
    }
}

// program 2-9
template <typename T >
void bubbleSort(T a[], const int n)
{
    for (int i = n; i > 1; i--)
    {
        bubble(a, i);
    }
}

// program 2-10
template <typename T>
void insert(T a[], const int n, const T& x)
{
    int i;
    for (i = n - 1; i >= 0 && x < a[i]; i--) {
        a[i + 1] = a[i];  // 向后移动元素
    }
    a[i + 1] = x;  // 插入元素 x
}

// program 2-11
template <typename T>
void rearrangeR(T a[], int n, int r[])
{
    for (int i = 0; i < n; i++)
    {
        while (r[i] != i)
        {
            int t = r[i];
            std::swap(a[i], a[t]);
            std::swap(r[i], r[t]);
        }
    }
}

// program 2-12
template <typename T>
void selectionSortR(T a[], const int n)
{
    bool sorted = false;
    for (int size = n; !sorted && (size > 1); size--)
    {
        int indexOfMax = 0;
        sorted = true;
        for (int i = 1; i < size; i++)
        {
            if (a[i] > a[indexOfMax])
                indexOfMax = i;
            else
                sorted = false;
        }
        std::swap(a[indexOfMax], a[size - 1]);
    }
}

// program 2-13
template <typename T>
bool bubbleR(T a[], const int n)
{
    bool swapped = false;
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] > a[i + 1]) {
            std::swap(a[i], a[i + 1]);
            swapped = true;
        }
    }
    return swapped;
}

template <typename T >
void bubbleSortR(T a[], const int n)
{
    for (int i = n; i > 1 && bubbleR(a, i); i--);
}

// program 2-14
template<typename T>
void insertR(T a[], const int n, const T& x)
{
    int i;
    for (i = n - 1; i >= 0 && x < a[i]; i--)
        a[i + 1] = a[i];
    a[i + 1] = x;
}

template <typename T>
void insertionSort(T a[], const int n)
{
    for (int i = 1; i < n; i++) {
        T t = a[i];
        insert(a, i, t);  // 插入元素 a[i]
    }
}

// program 2-15
template <typename T>
void insertionSortR(T a[], const int n)
{
    for (int i = 1; i < n; i++)
    {
        T t = a[i];
        int j;
        for (j = i - 1; j >= 0 && t < a[j]; j--)
            a[j + 1] = a[j];
        a[j + 1] = t;
    }
}

template <typename T>
void transpose(T **a, const int rows)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = i + 1; j < rows; j++)
        {
            std::swap(a[i][j], a[j][i]);
        }
    }
}

template <typename T>
void inef(T a[], T b[], int n)
{
    for (int j = 0; j < n; j++)
    {
        b[j] = sum(a, j + 1);
    }
}
#endif
