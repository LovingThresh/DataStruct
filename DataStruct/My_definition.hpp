#ifndef MY_EXCEPTION_HPP
#define MY_EXCEPTION_HPP

#include <exception>
#include <iostream>
#include <type_traits>
#include <utility>

class illegalParameterValue final : public std::exception
{
public:
    illegalParameterValue() :
        m_message("Illegal parameter value")
    {
    }

    explicit illegalParameterValue(const char* message) :
        m_message(message)
    {
    }

    void output() const
    {
        std::cout << m_message;
    }

private:
    std::string m_message;
};

// 用于处理非移动语义的swap实现
template <typename T>
void swap_impl(T& a, T& b, std::false_type)
{
    T temp(a);
    a = b;
    b = temp;
}

// 用于处理移动语义的swap实现
template <typename T>
void swap_impl(T& a, T& b, std::true_type)
{
    T temp(std::move(a));
    a = std::move(b);
    b = std::move(temp);
}

// 主swap函数
template <typename T>
void swap(T& a, T& b) noexcept(
    noexcept(swap_impl(a, b,  // NOLINT(cppcoreguidelines-noexcept-swap, performance-noexcept-swap)
        std::integral_constant<bool, noexcept(T(std::move(a))) &&
        noexcept(a = std::move(b))>()))
    )
{
    swap_impl(a, b, std::integral_constant<bool, noexcept(T(std::move(a))) &&
        noexcept(a = std::move(b))>());
}

#endif
