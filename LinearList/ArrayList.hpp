#pragma once

#include "LinearList.hpp"
#include <sstream>

template<typename T>
class arrayList : public linearList<T>
{
public:
    explicit arrayList(int initialCapacity = 10);
    arrayList(const arrayList<T>&);
    ~arrayList() override;

    // ADT
    bool empty() const override;
    int size() const override;
    T& get(int theIndex) const override;
    int indexOf(T& theElement) const override;
    void erase(int theIndex) override;
    void insert(int theIndex, const T& theElement) override;
    void output(std::ostream& out) const override;

    // 其他方法
    int capacity() const;

protected:
    void checkIndex(int theIndex) const;

    T* element; // 存储线性表元素的一维数组
    int arrayLength; // 一维数组的容量
    int listSize; // 线性表的元素个数
};

template <typename T>
arrayList<T>::arrayList(const int initialCapacity)
{
    if (initialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << initialCapacity << "Must be > 0";
        throw illegalParameterValue(s.str().c_str());
    }
    arrayLength = initialCapacity;
    element = new T[arrayLength];
    listSize = 0;
}

template <typename T>
arrayList<T>::arrayList(const arrayList<T>& theList)
{
    arrayLength = theList.arrayLength; // protected 成员对类的所有成员函数和派生类的成员函数可见。
    listSize = theList.listSize;
    element = new T[arrayLength];
    std::copy(theList.element, theList.element + listSize, element);
}

template <typename T>
arrayList<T>::~arrayList()
{
    delete[] element;
}

template <typename T>
bool arrayList<T>::empty() const
{
    return listSize == 0;
}

template <typename T>
int arrayList<T>::size() const
{
    return listSize;
}

template <typename T>
T& arrayList<T>::get(const int theIndex) const
{
    // 返回索引为 theIndex 的元素
    checkIndex(theIndex);
    return element[theIndex];
}

template <typename T>
int arrayList<T>::indexOf(T& theElement) const
{
    const int theIndex = static_cast<int>(std::find(element, element + listSize, theElement) - element);

    // 确定元素 theElement 是否找到
    if (theIndex == listSize)
    {
        return -1;
    }
    return theIndex;
}

template <typename T>
void arrayList<T>::erase(const int theIndex)
{
    checkIndex(theIndex);

    // 有效索引，移动其索引大于 theIndex 的元素
    std::copy(element + theIndex + 1, element + listSize, element + theIndex);
    element[--listSize].~T();
}

template <typename T>
void arrayList<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > listSize)
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
    }

    // 有效索引，确定数组是否已满
    if (listSize == arrayLength)
    {
        changeLength1D(element, arrayLength, 2 * arrayLength);
        arrayLength *= 2;
    }

    // 把元素向右移动一个位置
    std::copy_backward(element + theIndex, element + listSize, element + listSize + 1);

    element[theIndex] = theElement;
    listSize++;
}

template <typename T>
void arrayList<T>::output(std::ostream& out) const
{
    std::copy(element, element + listSize, std::ostream_iterator<T>(std::cout, " "));
}

template <typename T>
int arrayList<T>::capacity() const
{
    return arrayLength;
}

template <typename T>
void arrayList<T>::checkIndex(const int theIndex) const
{
    // 确定索引 theIndex 在 0 和 listSize - 1 之间
    if (theIndex < 0 || theIndex >= listSize)
    {
        std::ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalParameterValue(s.str().c_str());
    }
}

template<typename T>
std::ostream& operator<<(std::ostream& out, const arrayList<T>& x)
{
    x.output(out);
    return out;
}
