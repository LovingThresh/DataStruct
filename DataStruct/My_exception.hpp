#ifndef MY_EXCEPTION_HPP
#define MY_EXCEPTION_HPP

#include <exception>
#include <iostream>


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
#endif

