#include "Exercise_1_5_O.hpp"
#include "My_exception.hpp"

#include <format>
#include <ostream>

currency::currency(const sign_type sign, const unsigned long currency_value, const unsigned int currency_decimals)
{
    setValue(sign, currency_value, currency_decimals);
}

void currency::setValue(const sign_type theSign,
                        const unsigned long theDollars,
                        const unsigned int theCents)
{
    if (theCents > 99)
        throw illegalParameterValue("Cents should be < 100\n");
    m_amount = static_cast<long>(theDollars * 100 + theCents);
    if (theSign == sign_type::minus)
        m_amount = -m_amount;
}

void currency::setValue(const double theAmount)
{
    if (theAmount < 0)
        m_amount = static_cast<long>((theAmount - 0.001) * 100);
    else
        m_amount = static_cast<long>((theAmount + 0.001) * 100);
}

currency currency::operator+(const currency& aCurrency) const
{
    currency result;
    result.m_amount = m_amount + aCurrency.m_amount;
    return result;
}

void currency::output(std::ostream& out) const
{
    std::string sign = (getSign() == minus) ? "-" : "+";
    const std::string formatted = std::format("({}${}.{})", sign, getDollars(), getCents());
    out << formatted;
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
    if (m_amount < 0)
        return (-m_amount) / 100;
    else
        return m_amount / 100;
}

unsigned int currency::getCents() const
{
    if (m_amount < 0)
        return -m_amount - getDollars() * 100;
    else
        return m_amount - getDollars() * 100;
}

currency& currency::operator+=(const currency& x)
{
    m_amount += x.m_amount;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const currency& x)
{
    x.output(out);
    return out;
}
