#ifndef EXERCISE_1_5_HPP
#define EXERCISE_1_5_HPP

namespace currency_space
{
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
        [[nodiscard]] static currency geMaxCurrency();
        [[nodiscard]] static currency geMixCurrency();
        [[nodiscard]] currency add(const currency&) const;
        [[nodiscard]] currency subtract(const currency&) const;
        [[nodiscard]] currency multiply(const double) const;
        [[nodiscard]] currency divide(const double) const;
        [[nodiscard]] currency percent(const double) const ;
        [[nodiscard]] currency& decrement(const currency&);
        [[nodiscard]] currency& increment(const currency&);
        [[nodiscard]] currency& input(std::istream&);
        [[nodiscard]] explicit operator double() const;
        [[nodiscard]] friend std::istream& operator>>(std::istream&, currency&);
        void output() const;

    private:
        sign_type m_sign;
        unsigned long m_dollars;
        unsigned int m_cents;
    };
}
#endif
