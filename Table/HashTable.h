#pragma once
#include "Table.h"
#include "Record.h"

template <typename TKey, typename TVal>
class HashTable: public Table<TKey, TVal> {
protected:
	int size;
public:
	virtual int HashFunc(TKey key) {
		return key % size;
	}
};