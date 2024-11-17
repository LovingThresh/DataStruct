#pragma once
#include <ostream>

#include "../DataStruct/My_definition.hpp"

template<typename T>
class linearList
{
public:
    linearList() = default;
    virtual ~linearList() = default;
    virtual bool empty() const = 0;
    virtual int size() const = 0;
    virtual T& get(int theIndex) const = 0;
    virtual int indexOf(const T& theElement) const = 0;
    virtual void erase(int theIndex) = 0;
    virtual void insert(int theIndex, const T& theElement) = 0;
    virtual void output(std::ostream& out) const = 0;
};

template<typename T>
void changeLength1D(T*& a, const int oldLength, const int newLength)
{
    if (newLength < 0)
    {
        throw illegalParameterValue("new length must be >= 0");
    }

    T* temp = new T[newLength];
    int number = std::min(oldLength, newLength);
    std::copy(a, a + number, temp);
    delete[] a;
    a = temp;
}

template <typename T>
class extendedLinearList : public linearList<T>
{
public:
    ~extendedLinearList() override
    {
    }

    virtual void clear() = 0;
    virtual void push_back(const T& oTheElement) = 0;
};
