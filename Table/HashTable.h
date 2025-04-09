#pragma once
#include "Table.h"
#include "Record.h"

template <typename TKey, typename TVal>
class HashTable: public Table<TKey, TVal> {
protected:
	int size;
public:
	HashTable(int _size = 10) : size(_size) {}

	virtual int HashFunc(TKey key) {
		eff++;
		return key % size;
	}
};