#pragma once
#include "ScanTable.h"
#include "ArrayTable.h"
#include "Table.h"
#include "Record.h"

template<typename TKey, typename TVal>
class SortTable : public ScanTable<TKey, TVal> {
public:
	SortTable(int _size = 10) : ScanTable<TKey, TVal>(_size) {}
	
	bool Find(TKey key) {
		int start = 0, finish = dataCount - 1;
		while (start <= finish) {
			eff++;
			int ind = (start + finish) / 2;
			if (pRecord[ind].key > key) {
				finish = ind - 1;
			}
			else if (pRecord[ind].key < key) {
				start = ind + 1;
			}
			else {
				currentIndex = ind;
				return true;
			}
		}
		currentIndex = start;
		return false;
	}

	void Insert(Record<TKey, TVal> record) {
		if (Find(record.key)) {
			throw -1;
		}
		if (this->dataCount == size) {
			throw -1;
		}
		for (int i = dataCount; i > currentIndex; i--) {
			pRecord[i] = pRecord[i - 1];
			eff++;
		}
		dataCount++;
		pRecord[currentIndex] = record;
	}

	void Delete(TKey key) {
		if (!Find(key)) {
			throw -1;
		}
		for (int i = currentIndex; i < dataCount - 1; i++) {
			pRecord[i] = pRecord[i + 1];
			eff++;
		}
		dataCount--;
	}

};