#include "Exercise_1_5_O.hpp"
#include "My_definition.hpp"

#include <format>
#include <ostream>

currency::currency(const int x)
{
    *this = x;
}

currency::currency(const double x)
{
    *this = x;
}

currency currency::operator+(const currency& x) const
{
    currency result;
    result.m_amount = m_amount + x.m_amount;
    return result;
}

sign_type currency::getSign() const
{
    if (m_amount < 0)
        return sign_type::minus;
    else
        return sign_type::plus;
}

unsigned long currency::getDollars() const
{
    return abs(m_amount / 100);
}

long currency::getMaxAmount()
{
    // constexpr unsigned long maxDollars = (LONG_MAX - 99) / 100;
    // const currency temp(static_cast<int>(maxDollars * 100 + 99));
    return LONG_MAX;
}

long currency::getMinAmount()
{
    // constexpr unsigned long minDollars = -(LONG_MIN + 99) / 100;
    // const currency temp(-static_cast<int>(minDollars * 100 + 99));
    return LONG_MIN;
}

unsigned int currency::getCents() const
{
    if (m_amount < 0)
        return -m_amount - getDollars() * 100;
    return m_amount - getDollars() * 100;
}

currency currency::percent(const double x) const
{
    currency result;
    result.m_amount = static_cast<long>(static_cast<double>(m_amount) * (x / 100));
    return result;
}

currency currency::operator-(const currency& x) const
{
    currency result;
    result.m_amount = m_amount - x.m_amount;
    return result;
}

currency currency::operator*(const double x) const
{
    currency result;
    result.m_amount = static_cast<long>(static_cast<double>(m_amount) * x);
    return result;
}

currency currency::operator/(const double x) const
{
    currency result;
    result.m_amount = static_cast<long>(static_cast<double>(m_amount) / x);
    return result;
}

currency& currency::operator=(const int x)
{
    this->m_amount = x;
    return *this;
}

currency& currency::operator=(const double x)
{
    if (x < 0)
        m_amount = static_cast<long>((x - 0.001) * 100);
    else
        m_amount = static_cast<long>((x + 0.001) * 100);
    return *this;
}


currency& currency::operator-=(const currency& x)
{
    m_amount -= x.m_amount;
    return *this;
}

bool currency::operator==(const currency& x) const
{
    return m_amount == x.m_amount;
}

bool currency::operator!=(const currency& x) const
{
    return m_amount != x.m_amount;
}

currency& currency::operator+=(const currency& x)
{
    m_amount += x.m_amount;
    return *this;
}

std::istream& operator>>(std::istream& in, currency& x)
{
    double the_mount;
    in >> the_mount;
    if (constexpr double epsilon = 1e-9; fabs(the_mount - static_cast<int>(the_mount)) < epsilon)
        throw std::runtime_error("Invalid input, double number!");
    x = the_mount;
    return in;
}

std::ostream& operator<<(std::ostream& out, const currency& x)
{
    std::string sign = (x.getSign() == minus) ? "-" : "";
    const std::string formatted = std::format("(${}{}.{})", sign, x.getDollars(), x.getCents());
    out << formatted;
    return out;
}
