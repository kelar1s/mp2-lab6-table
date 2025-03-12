#pragma once
#include "Table.h"
#include "Record.h"

template<typename TKey, typename TVal>
class ArrayTable : public Table<TKey, TVal> {
protected:
	int size, currentIndex;
	Record<TKey, TVal>* pRecord;
public:
	ArrayTable(int _size = 10) : size(_size), pRecord(new Record<TKey, TVal>[_size]), currentIndex(0) {
		this->dataCount = 0;
		this->eff = 0;
	}
	
	ArrayTable(const ArrayTable& oth) {
		size = oth.size;
		currentIndex = oth.currentIndex;
		this->dataCount = oth.dataCount;
		this->eff = oth.eff;
		pRecord = new Record<TKey, TVal>[size];
		for (int i = 0; i < size; i++) {
			pRecord[i] = oth.pRecord[i];
		}
	}
	
	~ArrayTable() { delete[] pRecord; }

	void Reset() {
		currentIndex = 0;
	}

	void GoNext() {
		currentIndex++;
	}

	bool IsEnd() {
		return currentIndex == this->dataCount;
	}
};