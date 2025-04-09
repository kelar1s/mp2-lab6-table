#pragma once
#include "ListIterator.h"

template <typename T>
struct TNode {
	T val;
	TNode* next = nullptr;
	TNode(T v) : val(v) {};
	TNode(): val(T()) {};
};

template <class T>
class TList {
protected:
    TNode<T>* pFirst;
    TNode<T>* pLast;
    TNode<T>* pCurr = nullptr;
    TNode<T>* pPrev = nullptr;
    int sz;
public:
    TList(): pFirst(nullptr), pLast(nullptr), sz(0) {}
    TList(const TList& oth);
    ~TList();

    TList<T>& operator=(const TList& oth);
    bool operator==(const TList& oth) const;
    bool operator!=(const TList& oth) const;

    void InsFirst(T val);
    void DelFirst();
    void InsLast(T val);
    void DelLast();
    
    bool isEmpty();
    bool isFull();
    void Clear();

    void Reset();
    bool IsEnd();
    void GoNext();
    T& GetCurr();
    void InsCurr(T v);
    void DelCurr();

    typedef ListIterator<T> iterator;

    iterator Begin() { return iterator(pFirst); };
    iterator End() { return iterator(pLast->next); };
};

template<class T>
inline TList<T>::TList(const TList& oth)
{
    if (oth.pFirst == nullptr) {
        pFirst = nullptr;
        pLast = nullptr;
        return;
    }
    pFirst = new TNode<T>(oth.pFirst->val);
    TNode<T>* tmp = oth.pFirst->next;
    TNode<T>* prev = pFirst;
    while (tmp != nullptr) {
        TNode<T>* node = new TNode<T>(tmp->val);
        prev->next = node;
        tmp = tmp->next;
        prev = prev->next;
    }
    pLast = prev;
    sz = oth.sz;
}

template<class T>
inline TList<T>::~TList()
{
    Clear();
}

template<class T>
TList<T>& TList<T>::operator=(const TList& oth)
{
    if (this == &oth) {
        return *this;
    }
    Clear();
    sz = oth.sz;
    if (oth.pFirst == nullptr) {
        pFirst = nullptr;
        pLast = nullptr;
        return *this;
    }
    pFirst = new TNode<T>(oth.pFirst->val);
    TNode<T>* tmp = oth.pFirst->next;
    TNode<T>* prev = pFirst;
    while (tmp != nullptr) {
        TNode<T>* node = new TNode<T>(tmp->val);
        prev->next = node;
        tmp = tmp->next;
        prev = prev->next;
    }
    pLast = prev;
    return *this;
}

template<class T>
bool TList<T>::operator==(const TList& oth) const
{
    if (this == &oth) {
        return true;
    }
    TNode<T>* tmp1 = pFirst;
    TNode<T>* tmp2 = oth.pFirst;
    while (tmp1 != nullptr && tmp2 != nullptr) {
        if (tmp1->val != tmp2->val) {
            return false;
        }
        tmp1 = tmp1->next;
        tmp2 = tmp2->next;
    }
    return tmp1 == nullptr && tmp2 == nullptr;
}

template<class T>
bool TList<T>::operator!=(const TList& oth) const
{
    return !(*this == oth);
}

template<class T>
void TList<T>::InsFirst(T val)
{
    TNode<T>* new_node = new TNode<T>(val);
    if (pFirst == nullptr) {
        pFirst = new_node;
        pLast = new_node;
    }
    else {
        new_node->next = pFirst;
        pFirst = new_node;
    }
    sz++;
}

template<class T>
void TList<T>::DelFirst()
{
    if (isEmpty()) {
        return;
    }
    if (sz == 0) return;
    TNode<T>* tmp = pFirst;
    pFirst = pFirst->next;
    delete tmp;
    sz--;
    if (sz == 0) pLast = pFirst;
}

template<class T>
inline void TList<T>::InsLast(T val)
{
    TNode<T>* last = new TNode<T>(val);
    if (pFirst == nullptr) {
        pFirst = last;
        pLast = last;
    }
    else {
        pLast->next = last;
        pLast = last;
    }
    sz++;
}

template<class T>
void TList<T>::DelLast()
{
    if (isEmpty()) {
        return; 
    }
    if (sz == 1) {
        delete pFirst; 
        pFirst = nullptr;
        pLast = nullptr; 
        sz = 0; 
        return;
    }
    TNode<T>* curr = pFirst;
    TNode<T>* prev = nullptr;
    while (curr->next != nullptr) {
        prev = curr;
        curr = curr->next;
    }
    prev->next = nullptr; 
    delete curr; 
    pLast = prev; 
    sz--;
}

template<class T>
bool TList<T>::isEmpty()
{
    return pFirst == nullptr;
}

template<class T>
bool TList<T>::isFull()
{
    try {
        TNode<T>* tmp = new TNode<T>();
        delete tmp;
        return false;
    }
    catch (...) {
        return true;
    }
}

template<class T>
void TList<T>::Clear()
{
    while (pFirst != nullptr) {
        TNode<T>* p = pFirst;
        pFirst = pFirst->next;
        delete p;
    }
    pLast = nullptr;
    sz = 0;
}

template<class T>
void TList<T>::Reset()
{
    pCurr = pFirst;
    pPrev = nullptr;
}

template<class T>
bool TList<T>::IsEnd()
{
    return pCurr == nullptr;
}

template<class T>
inline void TList<T>::GoNext()
{
    if (pCurr == nullptr) {
        throw - 1;
    }
    pPrev = pCurr;
    pCurr = pCurr->next;
}

template<class T>
T& TList<T>::GetCurr()
{
    return pCurr->val;
}

template<class T>
void TList<T>::InsCurr(T v)
{
    if (pCurr == pFirst) {
        InsFirst(v);
        pPrev = pFirst;
        return;
    }
    else if (pPrev == pLast) {
        InsLast(v);
        pPrev = pPrev->next;
        return;
    }
    else {
        TNode<T>* tmp = new TNode<T>(v);
        tmp->next = pCurr;
        pPrev->next = tmp;
        pPrev = pPrev->next;
        sz++;
    }
}

template<class T>
void TList<T>::DelCurr()
{
    if (pCurr == nullptr) {
        throw - 1;
    }
    else if (pCurr == pFirst) {
        DelFirst();
        pCurr = pFirst;
    }
    else {
        TNode<T>* tmp = pCurr;
        pCurr = pCurr->next;
        pPrev->next = pCurr;
        if (pCurr == nullptr) {
            pLast = pPrev;
        }
        delete tmp;
        sz--;
    }
}
