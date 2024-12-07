#pragma once
#include <sstream>

#include "iterator.hpp"
#include "../LinearList/LinearList.hpp"

template<typename T>
struct chainNode
{
    T m_oElement { };
    chainNode<T>* m_oNextNode = nullptr;

    chainNode() {}

    explicit chainNode(const T& oElement)
    {
        this->m_oElement = oElement;
    }

    chainNode(const T& oElement, chainNode<T>* pNextNode)
    {
        this->m_oElement = oElement;
        this->m_oNextNode = pNextNode;
    }
};

template<typename T>
class chain : public linearList<T>
{
public:
    explicit chain(int nInitialCapacity = 10);
    chain(const chain<T>& other);
    ~chain() override;

    bool empty() const override;
    int size() const override;
    T& get(int nTheIndex) const override;
    int indexOf(const T& oTheElement) const override;
    void erase(int theIndex) override;
    void insert(int theIndex, const T& theElement) override;
    void output(std::ostream& out) const override;

    iterator<T> begin() const
    {
        return iterator<T>(m_pFirstNode);
    }

    iterator<T> end() const
    {
        return iterator<T>(nullptr);
    }

protected:
    void checkIndex(int nTheIndex) const;
    chainNode<T>* m_pFirstNode = nullptr;
    int m_nListSize = 0;
};

template <typename T>
chain<T>::chain(const int nInitialCapacity)
{
    if (nInitialCapacity < 1)
    {
        std::ostringstream s;
        s << "Initial capacity = " << nInitialCapacity << "Must be > 0";
        throw illegalParameterValue(s.str().c_str());
    }

    m_pFirstNode = nullptr;
    m_nListSize = 0;
}

template <typename T>
chain<T>::chain(const chain<T>& other)
{
    m_nListSize = other.m_nListSize;

    if (m_nListSize == 0)
    {
        m_pFirstNode = nullptr;
        return;
    }

    chainNode<T>* pSourceNode = other.m_pFirstNode;
    m_pFirstNode = new chainNode<T>(pSourceNode->m_oElement);

    pSourceNode = pSourceNode->m_oNextNode;
    chainNode<T>* pTargetNode = m_pFirstNode;

    while (pSourceNode != nullptr)
    {
        pTargetNode->m_oNextNode = new chainNode<T>(pSourceNode->m_oElement);
        pTargetNode = pTargetNode->m_oNextNode;
        pSourceNode = pSourceNode->m_oNextNode;
    }

    pTargetNode= nullptr;
}

template <typename T>
chain<T>::~chain()
{
    while (m_pFirstNode != nullptr)
    {
        chainNode<T>* pNextNode = m_pFirstNode->m_oNextNode;
        delete m_pFirstNode;
        m_pFirstNode = pNextNode;
    }
}

template <typename T>
bool chain<T>::empty() const
{
    return m_nListSize == 0;
}

template <typename T>
int chain<T>::size() const
{
    return m_nListSize;
}

template <typename T>
T& chain<T>::get(const int nTheIndex) const
{
    chainNode<T>* pCurrentNode = m_pFirstNode;
    for (int i = 0; i < nTheIndex; ++i) {
        pCurrentNode = pCurrentNode->m_oNextNode;
    }
    return pCurrentNode->m_oElement;
}

template <typename T>
int chain<T>::indexOf(const T& oTheElement) const
{
    chainNode<T>* pCurrentNode = m_pFirstNode;
    int nIndex = 0;
    while (pCurrentNode != nullptr && pCurrentNode->m_oElement != oTheElement)
    {
        pCurrentNode = pCurrentNode->m_oNextNode;
        nIndex++;
    }
    if (pCurrentNode == nullptr)
    {
        return -1;
    }
    return nIndex;
}

template <typename T>
void chain<T>::erase(const int theIndex)
{
    checkIndex(theIndex);
    chainNode<T>* pDeletedNode = nullptr;
    if (theIndex == 0)
    {
        pDeletedNode = m_pFirstNode;
        m_pFirstNode = m_pFirstNode->m_oNextNode;
    }
    else
    {
        chainNode<T>* p = m_pFirstNode;
        for (auto i = 0; i < theIndex - 1; i++)
        {
            p = p->m_oNextNode;
        }
        pDeletedNode = p->m_oNextNode;
        p->m_oNextNode = p->m_oNextNode->m_oNextNode;
    }

    m_nListSize--;
    delete pDeletedNode;
}

template <typename T>
void chain<T>::insert(const int theIndex, const T& theElement)
{
    checkIndex(theIndex);
    if (theIndex == 0)
    {
        m_pFirstNode = new chainNode<T>(theElement, m_pFirstNode);
    }
    else
    {
        chainNode<T>* p = m_pFirstNode;
        for (auto i = 0; i < theIndex - 1; i++)
        {
            p = p->m_oNextNode;
        }
        p->m_oNextNode = new chainNode<T>(theElement, p->m_oNextNode);
    }
    m_nListSize++;
} 

template <typename T>
void chain<T>::output(std::ostream& out) const
{
    for (chainNode<T>* currentNode = m_pFirstNode; currentNode != nullptr; currentNode->m_oNextNode)
    {
        out << currentNode->m_oElement << " ";
    }
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const chain<T>& x)
{
    x.output(out);
    return out;
}

template <typename T>
void chain<T>::checkIndex(const int nTheIndex) const
{
    // 确定索引 theIndex 在 0 和 listSize - 1 之间
    if (nTheIndex < 0 || nTheIndex >= m_nListSize)
    {
        std::ostringstream s;
        s << "index = " << nTheIndex << " size = " << m_nListSize;
        throw illegalParameterValue(s.str().c_str());
    }
}
