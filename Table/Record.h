#pragma once
#include <iostream>

template<typename TKey, typename TVal>
struct Record
{
    TKey key;
    TVal val;
public:
    Record(TKey key, TVal val) : key(key), val(val) {}
    Record() : key(), val() {}
    friend std::ostream& operator<<(std::ostream& out, const Record<TKey, TVal>& rec)
    {
        out << rec.key << " : " << rec.val;
        return out;
    }

    bool operator==(const Record<TKey, TVal>& oth) {
        return this->key == oth.key;
    }

    
};