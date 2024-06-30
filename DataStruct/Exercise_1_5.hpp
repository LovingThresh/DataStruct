#pragma once
#include <iostream>
#include <__msvc_filebuf.hpp>

enum sign_type
{
    plus,
    minus
};

class currency
{
public:
    explicit currency(sign_type sign = plus, int currency_value = 0, int currency_decimals = 0);
    ~currency() = default;
    currency(const currency&) = default;
    currency(currency&&) noexcept = default;
    currency& operator=(const currency&) = default;
    currency& operator=(currency&&) noexcept = default;

    void setValue(sign_type, unsigned long, unsigned int);
    void setValue(double);
    [[nodiscard]] sign_type getSign() const { return m_sign; }
    [[nodiscard]] unsigned long getDollars() const { return m_dollars; }
    [[nodiscard]] unsigned int getCents() const { return m_cents; }
    [[nodiscard]] currency add(const currency&) const;
    currency& increment(const currency&);
    void output() const;

private:
    sign_type m_sign;
    unsigned long m_dollars;
    unsigned int m_cents;
};

class illegalParameterValue final : public std::exception
{
public:
    illegalParameterValue():
        m_message("Illegal parameter value")
    {
    }

    explicit illegalParameterValue(const char* message):
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
