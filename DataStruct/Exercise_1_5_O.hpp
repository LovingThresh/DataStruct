#ifndef EXERCISE_1_5_O_HPP
#define EXERCISE_1_5_O_HPP
#include <ostream>

enum sign_type
{
    plus,
    minus
};

class currency
{
public:
    currency(sign_type sign = plus,
             unsigned long currency_value = 0,
             unsigned int currency_decimals = 0);
    ~currency() = default;
    currency(const currency&) = default;
    currency(currency&&) noexcept = default;
    currency& operator=(const currency&) = default;
    currency& operator=(currency&&) noexcept = default;

    void setValue(sign_type, unsigned long, unsigned int);
    void setValue(double);
    [[nodiscard]] sign_type getSign() const;
    [[nodiscard]] unsigned long getDollars() const;
    [[nodiscard]] unsigned int getCents() const;
    [[nodiscard]] currency operator+(const currency&) const;
    currency& operator+=(const currency&);
    void output(std::ostream&) const;
    friend std::ostream& operator<<(std::ostream&, const currency&);

private:
    long m_amount;
};

#endif
