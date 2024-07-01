#include "My_exception.hpp"
#include "Exercise_1_5.hpp"

namespace currency_space
{
    inline currency::currency(const sign_type sign, const int currency_value, const int currency_decimals)
        : m_sign(plus), m_dollars(0), m_cents(0)
    {
        setValue(sign, currency_value, currency_decimals);
    }

    void currency::setValue(const sign_type the_sign, const unsigned long the_dollars, const unsigned int the_cents)
    {
        if (the_cents > 99)
        {
            const auto message = "currency::setValue: cents must be less than 100\n";
            throw illegalParameterValue(message);
        }
        m_sign = the_sign;
        m_dollars = the_dollars;
        m_cents = the_cents;
    }

    void currency::setValue(double the_amount)
    {
        if (the_amount < 0.0)
        {
            m_sign = minus;
            the_amount = -the_amount;
        }
        else
        {
            m_sign = plus;
        }
        m_dollars = static_cast<unsigned long>(the_amount);
        m_cents = static_cast<unsigned int>((the_amount + 0.001 - m_dollars) * 100.0);
    }

    currency currency::add(const currency& x) const
    {
        currency result;
        long long a1 = m_dollars * 100 + m_cents;
        if (m_sign == minus)
        {
            a1 = -a1;
        }

        long long a2 = x.m_dollars * 100 + x.m_cents;
        if (x.m_sign == minus)
        {
            a2 = -a2;
        }
        long long a3 = a1 + a2;
        if (a3 < 0)
        {
            result.m_sign = minus;
            a3 = -a3;
        }
        else
        {
            result.m_sign = plus;
        }
        result.m_dollars = static_cast<unsigned long>(a3 / 100);
        result.m_cents = static_cast<unsigned long>
            (a3 - static_cast<long long>(result.m_dollars * 100));
        return result;
    }

    currency& currency::increment(const currency& x)
    {
        *this = add(x);
        return *this;
    }

    void currency::output() const
    {
        std::string sign = (m_sign == minus) ? "-" : "+";
        const std::string formatted = std::format("({}${}.{})", sign, m_dollars, m_cents);
        std::cout << formatted;
    }
}
