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

    /*Record<TKey, TVal>& operator=(const Record<TKey, TVal>& oth) {
        if (this == &oth) {
            return *this;
        }
        key = oth.key;
        val = oth.key;
        return *this;
    }*/

    bool operator==(const Record<TKey, TVal>& oth) {
        return this->key == oth.key;
    }

    bool operator!=(const Record<TKey, TVal>& oth) {
        return !(*this == oth);
    }
};