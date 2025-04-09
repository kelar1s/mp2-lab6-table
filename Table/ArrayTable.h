#pragma once
#include "Table.h"
#include "Record.h"

template<typename TKey, typename TVal>
class ArrayTable : public Table<TKey, TVal> {
protected:
	int size, currentIndex;
	Record<TKey, TVal>* pRecord;
public:
	ArrayTable(int _size = 10) : Table<TKey, TVal>(), size(_size), pRecord(new Record<TKey, TVal>[_size]), currentIndex(0) { }
	
	ArrayTable(const ArrayTable& oth) {
		size = oth.size;
		currentIndex = oth.currentIndex;
		dataCount = oth.dataCount;
		eff = oth.eff;
		pRecord = new Record<TKey, TVal>[size];
		for (int i = 0; i < size; i++) {
			pRecord[i] = oth.pRecord[i];
		}
	}
	
	~ArrayTable() { delete[] pRecord; }

	bool IsFull() const {
		return dataCount == size;
	}

	Record<TKey, TVal> GetCurr() {
		if (currentIndex < 0 || currentIndex >= dataCount) {
			throw -1;
		}
		return pRecord[this->currentIndex];
	}

	TKey GetCurrKey() {
		if (currentIndex < 0 || currentIndex >= dataCount) {
			throw -1;
		}
		return pRecord[currentIndex].key;
	}

	TVal GetCurrVal() {
		if (currentIndex < 0 || currentIndex >= dataCount) {
			throw -1;
		}
		return pRecord[currentIndex].val;
	}

	void Reset() {
		currentIndex = 0;
	}

	void GoNext() {
		currentIndex++;
	}

	bool IsEnd() {
		return currentIndex == dataCount;
	}
};