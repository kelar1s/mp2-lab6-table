#pragma once

template<typename TKey, typename TVal>
struct Record
{
    TKey key;
    TVal val;
public:
    Record(TKey key, TVal val) : key(key), val(val) {}
    Record() : key(), val() {}
};