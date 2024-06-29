#pragma once
#include <vector>
static void swap(int& a, int& b) noexcept;

inline void swap(int& a, int& b) noexcept
{
    const int temp = a;
    a = b;
    b = temp;
}


template <typename T>
static size_t count(std::vector<T> a)
{
    return a.size();
}

template <typename T>
std::vector<T>& fill(std::vector<T>& a, const T& value)
{
    for (auto& element : a) // 使用范围for循环
    {
        element = value;
    }

    return a;
}

template <typename Ta, typename Tb, typename Tr>
Tr inner_product(const std::vector<Ta>& a, const std::vector<Tb>& b, Tr& result = 0)
{
    assert(a.size() == b.size());
    for (size_t i = 0; i < a.size(); ++i)
    {
        result += a[i] * b[i];
    }

    return result;
}

template <typename T>
std::vector<T> iota(std::vector<T>& a, const T value)
{
    for (size_t element = 0; element < a.size(); element++)
    {
        if (static_cast<T>(std::numeric_limits<T>::max() - element) < value)
        {
            throw std::overflow_error("overflow");
        }
        a[element] = static_cast<T>(element) + value;
    }

    return a;
}

