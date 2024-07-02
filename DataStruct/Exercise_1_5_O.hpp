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
    // currency() = default;
    // ReSharper disable once CppNonExplicitConvertingConstructor
    currency() : m_amount(0)
    {
    }

    explicit currency(int x);
    explicit currency(double);
    ~currency() = default;
    currency(const currency&) = default;
    currency(currency&&) noexcept = default;
    currency& operator=(const currency&) = default;
    currency& operator=(currency&&) noexcept = default;

    [[nodiscard]] sign_type getSign() const;
    [[nodiscard]] unsigned long getDollars() const;
    [[nodiscard]] static long getMaxAmount();
    [[nodiscard]] static long getMinAmount();
    [[nodiscard]] unsigned int getCents() const;
    [[nodiscard]] currency percent(double) const;
    [[nodiscard]] currency operator+(const currency&) const;
    [[nodiscard]] currency operator-(const currency&) const;
    [[nodiscard]] currency operator*(double) const;
    [[nodiscard]] currency operator/(double) const;
    currency& operator=(int);
    currency& operator=(double);
    currency& operator+=(const currency&);
    currency& operator-=(const currency&);
    [[nodiscard]] bool operator==(const currency&) const;
    [[nodiscard]] bool operator!=(const currency&) const;
    friend std::ostream& operator<<(std::ostream&, const currency&);
    friend std::istream& operator>>(std::istream&, currency&);

private:
    long m_amount;
};

#endif
