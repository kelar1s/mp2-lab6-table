#pragma once
#include "Record.h"
#include <iostream>

template<typename TKey, typename TVal>
class Table
{
protected:
    int dataCount;
    int eff;
public:
    Table() : dataCount(0), eff(0) {};
    virtual ~Table() {};

    int GetDataCount() {
        return dataCount;
    }

    int GetEff() {
        return eff;
    }

    void ClearEff() {
        eff = 0;
    }

    bool IsEmpty() const {
        if (dataCount == 0)
            return true;
        return false;
    }

    virtual bool IsFull() const = 0;

    virtual bool Find(TKey key) = 0;
    virtual void Insert(Record<TKey, TVal> rec) = 0;
    virtual void Delete(TKey key) = 0;

    virtual void Reset() = 0;
    virtual void GoNext() = 0;
    virtual bool IsEnd() = 0;

    virtual Record<TKey, TVal> GetCurr() = 0;
    virtual TKey GetCurrKey() = 0;
    virtual TVal GetCurrVal() = 0;

    friend std::ostream& operator<<(std::ostream& out, Table<TKey, TVal>& table)
    {
        for (table.Reset(); !table.IsEnd(); table.GoNext())
        {
            out << table.GetCurr() << std::endl;
        }
        return out;
    }

};

