#pragma once
#include "ArrayTable.h"
#include "Table.h"
#include "Record.h"

template<typename TKey, typename TVal>
class ScanTable : public ArrayTable<TKey, TVal> {
public:
	ScanTable(int _size = 10) : ArrayTable<TKey, TVal>(_size) {}
	
	bool Find(TKey key) {
		for (Reset(); !IsEnd(); GoNext()) {
			eff++;
			if (GetCurrKey() == key) {
				return true;
			}
		}
		eff++;
		currentIndex = dataCount;
		return false;
	}

	void Insert(Record<TKey, TVal> record) {
		if (Find(record.key) || IsFull() ) {
			throw -1;
		}
		pRecord[currentIndex] = record;
		dataCount++;
		eff++;
	}

	void Delete(TKey key) {
		if (!Find(key)) {
			throw -1;
		}
		pRecord[currentIndex] = pRecord[dataCount - 1];
		dataCount--;
		eff++;
	}
};