#ifndef EXERCISE_1_2_HPP
#define EXERCISE_1_2_HPP

#include <vector>
#include <string>

inline void swap(int& a, int& b) noexcept
{
    const int temp = a;
    a = b;
    b = temp;
}


template <typename T>
static size_t count(std::vector<T> a)
{
    if (a.empty())
        throw "n should not < 1"; // NOLINT(hicpp-exception-baseclass)
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
    for (size_t element = 0; element < a.size(); ++element)
    {
        if (static_cast<T>(std::numeric_limits<T>::max() - element) < value)
        {
            throw std::overflow_error("overflow");
        }
        a[element] = static_cast<T>(element) + value;
    }

    return a;
}

template <typename T>
bool is_sorted(const std::vector<T>& a)
{
    for (size_t i = 0; i < a.size() - 1; ++i)
    {
        if (a[i] > a[i + 1])
        {
            return false;
        }
    }
    return true;
}

template <typename T>
size_t mismatch(const std::vector<T>& a, const std::vector<T>& b)
{
    for (size_t i = 0; i < std::min(a.size(), b.size()); ++i)
    {
        if (a[i] != b[i])
        {
            return i;
        }
    }

    if (a.size() != b.size())
    {
        return std::min(a.size(), b.size());
    }

    return std::string::npos;
}
#endif
