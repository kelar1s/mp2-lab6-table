#pragma once
#include "HashTable.h"
#include <list>
#include <iterator>

template<typename TKey, typename TVal>
class ListHashTable : public HashTable<TKey, TVal> {
protected:
    std::list<Record<TKey, TVal>>* pList;
    int currList;
    typename std::list<Record<TKey, TVal>>::iterator currIterator;
public:
    ListHashTable(int _size = 10) : HashTable<TKey, TVal>(_size) {
        pList = new std::list<Record<TKey, TVal>>[size];
        eff = 0;
        dataCount = 0;
        currList = -1;
    }

    ListHashTable(const ListHashTable& oth){
        size = oth.size;
        currList = oth.currList;
        eff = oth.eff;
        dataCount = oth.dataCount;
        pList = new std::list<Record<TKey, TVal>>[size];
        for (int i = 0; i < size; ++i) {
            pList[i] = oth.pList[i];
        }
        if (currList >= 0 && currList < size && !pList[currList].empty()) {
            currIterator = pList[currList].begin();
        }
    }

    ~ListHashTable() {
        delete[] pList;
    }

    bool IsFull() const {
        try {
            Record<TKey, TVal>* tmp = new Record<TKey, TVal>;
            delete tmp;
            return false;
        }
        catch (...) {
            return true;
        }
    }

    bool Find(TKey key) {
        currList = HashFunc(key);
        currIterator = pList[currList].begin();
        for (currIterator; currIterator != pList[currList].end(); currIterator++) {
            eff++;
            if (currIterator->key == key) {
                return true;
            }
        }
        return false;
    }

    void Insert(Record<TKey, TVal> record) {
        if (Find(record.key)) {
            throw - 1;
        }
        pList[currList].push_front(record);
        dataCount++;
        eff++;
    }

    void Delete(TKey key) {
        if (!Find(key) || dataCount == 0) {
            throw - 1;
        }
        pList[currList].erase(currIterator);
        eff++;
        dataCount--;
    }

    void Reset() {
        currList = 0;
        while (currList < size && pList[currList].empty()) {
            currList++;
        }
        if (currList < size) {
            currIterator = pList[currList].begin();
        }
    }

    bool IsEnd() {
        return currList >= size;
    }

    void GoNext() {
        if (IsEnd()) return;
        ++currIterator;
        while (currIterator == pList[currList].end()) {
            currList++;
            if (currList >= size) break;
            currIterator = pList[currList].begin();
        }
    }

    Record<TKey, TVal> GetCurr() {
        if (IsEnd() || pList[currList].empty()) {
            throw -1;
        }
        return *currIterator;
    }

    TKey GetCurrKey() {
        return GetCurr().key;
    }

    TVal GetCurrVal() {
        return GetCurr().val;
    }

    void Clear() {
        for (int i = 0; i < size; i++) {
            pList[i].clear();
        }
        dataCount = 0;
        currList = -1;
        ClearEff();
    }
};