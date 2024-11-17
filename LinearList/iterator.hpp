#pragma once

#include <iterator>

template <typename T>
class iterator
{
public:
    // 用 C++ 的 typedef 语句实现双向迭代器
    typedef std::bidirectional_iterator_tag iterator_category;
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;

    // 构造函数
    explicit iterator(T* thePosition = nullptr) : m_pPosition(thePosition) {}

    // 解引用操作符
    T& operator*() const;
    T* operator->() const;

protected:
    T* m_pPosition;

};

template <typename T>
T& iterator<T>::operator*() const
{
    return *m_pPosition;
}

template <typename T>
T* iterator<T>::operator->() const
{
    return &*m_pPosition;
}
