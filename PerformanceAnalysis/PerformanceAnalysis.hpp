#ifndef PERFORMANCEANALYSIS_HPP
#define PERFORMANCEANALYSIS_HPP
#include <algorithm>
#include <future>

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

template <typename T>
T ployEval(T coeff[], const int n, const T& x)
{
    T y = 1, value = coeff[0];
    for (int i =1; i < n + 1; i++)
    {
        y *= x;
        value += coeff[i] * y;
    }
    return value;
}

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

template <typename T >
void rank(T a[], const int n, int r[])
{
    for (int i =0; i < n; i++)
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

template <typename T>
void selectionSort(T a[], const int n)
{
    for (int size = n; size > 1; size--)
    {
        int j = indexOfMax(a, size);
        std::swap(a[j], a[size - 1]);
    }
}

template <typename T>
void bubble(T a[], const int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] > a[i + 1])
            std::swap(a[i], a[i + 1]);
    }
}

template <typename T >
void bubbleSort(T a[], const int n)
{
    for (int i = n; i > 1; i--)
    {
        bubble(a, i);
    }
}

template <typename T>
void insert(T a[], const int n, const T& x)
{
    for (int i = n - 1; i >= 0 && x < a[i]; i--)
    {
        a[i + 1] = a[i];
    }
}
#endif
