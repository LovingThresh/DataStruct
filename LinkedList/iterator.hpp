#pragma once
#include <cstddef>

#include "LinkedList.hpp"


template<typename T>
class iterator
{
public:
    typedef T value_type;
    typedef ptrdiff_t difference_type;
    typedef T* pointer;
    typedef T& reference;

    explicit iterator(chainNode<T>* pTheNode = nullptr)
    {
        m_pNode = pTheNode;
    }

    // 解引用操作符
    T& operator*() const
    {
        return m_pNode->m_oElement;
    }

    T* operator->() const
    {
        return &(m_pNode->m_oElement);
    }

    // 迭代器加法
    iterator& operator++() // 前置++
    {
        m_pNode = m_pNode->m_oNextNode;
        return m_pNode;
    }

    iterator operator++(int) // 后置++
    {
        iterator old = *this;  // 保存当前状态
        m_pNode = m_pNode->next;     // 自增，移动到下一个节点
        return old;            // 返回未自增前的旧状态
    }

    bool operator==(const iterator& lhs, const iterator& rhs)
    {
        return lhs.m_pNode == rhs.m_pNode;
    }

    bool operator!=(const iterator& lhs, const iterator& rhs)
    {
        return !(lhs == rhs);
    }

protected:
    chainNode<T>* m_pNode;
};
