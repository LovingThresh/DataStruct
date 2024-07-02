#include "My_definition.hpp"
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

    currency currency::geMaxCurrency()
    {
        currency result;
        result.m_sign = plus;
        result.m_dollars = ULONG_MAX;
        // result.m_dollars = INT32_MAX
        result.m_cents = 99;
        return result;
    }

    currency currency::geMixCurrency()
    {
        currency result;
        result.m_sign = minus;
        result.m_dollars = ULONG_MAX;
        // result.m_dollars = INT32_MIN;
        result.m_cents = 99;
        return result;
    }


    currency currency::add(const currency& x) const
    {
        currency result;
        long long a1 = m_dollars * 100 + m_cents;
        if (m_sign == minus)
            a1 = -a1;

        long long a2 = x.m_dollars * 100 + x.m_cents;
        if (x.m_sign == minus)
            a2 = -a2;
        long long a3 = a1 + a2;
        if (std::abs(a3 / 100) >= ULONG_MAX)
            throw illegalParameterValue("The amount is too large");

        if (a3 < 0)
        {
            result.m_sign = minus;
            a3 = -a3;
        }
        else
            result.m_sign = plus;

        result.m_dollars = static_cast<unsigned long>(a3 / 100);
        result.m_cents = static_cast<unsigned long>(a3 % 100);
        return result;
    }

    currency currency::subtract(const currency& x) const
    {
        currency result;
        long long a1 = m_dollars * 100 + m_cents;
        if (m_sign == minus)
            a1 = -a1;

        long long a2 = x.m_dollars * 100 + x.m_cents;
        if (x.m_sign == minus)
            a2 = -a2;
        long long a3 = a1 - a2;
        if (std::abs(a3 / 100) >= ULONG_MAX)
            throw illegalParameterValue("The amount is too large");

        if (a3 < 0)
        {
            result.m_sign = minus;
            a3 = -a3;
        }
        else
            result.m_sign = plus;

        result.m_dollars = static_cast<unsigned long>(a3 / 100);
        result.m_cents = static_cast<unsigned long>(a3 % 100);
        return result;
    }

    currency currency::multiply(const double x) const
    {
        currency result;
        const double value = static_cast<double>(*this);
        result.setValue(value * x);
        return result;

    }

    currency currency::divide(const double x) const
    {
        currency result;
        const double value = static_cast<double>(*this);
        result.setValue(value / x);
        return result;
    }

    currency currency::percent(const double x) const
    {
        currency result;
        const double value = static_cast<double>(*this);
        result.setValue(value * (x / 100));
        return result;
    }

    currency& currency::decrement(const currency& x)
    {
        *this = subtract(x);
        return *this;
    }

    currency& currency::increment(const currency& x)
    {
        *this = add(x);
        return *this;
    }

    currency& currency::input(std::istream& in)
    {
        char ch1, ch2;
        unsigned long the_dollars = 0;
        unsigned int the_cents = 0;
        sign_type the_sign = plus;

        in >> ch1;
        if (ch1 == '-')
        {
            the_sign = minus;
            in >> the_dollars;
        }
        else if (ch1 == '+')
        {
            in >> the_dollars;
        }
        else if (isdigit(ch1))
        {
            in.putback(ch1);
            in >> the_dollars;
        }
        else
        {
            throw illegalParameterValue("currency::input: illegal character for currency sign");
        }

        in >> ch2;
        if (ch2 != '.')
        {
            throw illegalParameterValue("currency::input: illegal form for currency value");
        }

        in >> the_cents;
        if (the_cents > 99)
        {
            throw illegalParameterValue("currency::input: cents value out of range");
        }

        this->m_sign = the_sign;
        this->m_dollars = the_dollars;
        this->m_cents = the_cents;

        return *this;
    }

    currency::operator double() const
    {
        const double value = static_cast<double>(this->m_dollars * 100 + this->m_cents) / 100;
        return (this->m_sign == minus) ? -value : value;
    }


    void currency::output() const
    {
        std::string sign = (m_sign == minus) ? "-" : "+";
        const std::string formatted = std::format("({}${}.{})", sign, m_dollars, m_cents);
        std::cout << formatted;
    }

    std::istream& operator>>(std::istream& in, currency& x)
    {
        char ch1, ch2;
        unsigned long the_dollars;
        unsigned int the_cents;
        sign_type the_sign{plus};
        in >> ch1;
        if (ch1 == '-')
            the_sign = minus;
        else if (ch1 == '+')
            the_sign = plus;
        else
        {
            in.putback(ch1);
            in >> the_dollars;
            x.setValue(the_sign, the_dollars, 0);
            return in;
        }
        in >> the_dollars >> ch2 >> the_cents;
        if (ch2 != '.')
        {
            const auto message = "currency::setValue: illegal form for currency value\n";
            throw illegalParameterValue(message);
        }
        x.setValue(the_sign, the_dollars, the_cents);
        return in;
    }
}
