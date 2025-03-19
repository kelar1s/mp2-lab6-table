#pragma once
#include "ScanTable.h"
#include "ArrayTable.h"
#include "Table.h"
#include "Record.h"

template<typename TKey, typename TVal>
class SortTable : ScanTable<TKey, TVal> {
public:
	SortTable(int _size = 10) : ScanTable<TKey, TVal>(_size) {}
	
	bool Find(TKey key) {
		int start = 0;
		int finish = dataCount - 1;
		while (finish > start) {
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

	void SelectSort() {
		int i = 0, j = 0;
		while (i < dataCount) {
			eff++;
			j = i;
			int k = i;
			int minik = pRecord[i].key;
			while (j < dataCount) {
				if (pRecord[j] < minik) {
					minik = pRecord[j].key;
					k = j;
				}
				j++;
			}
			Record<TKey, TVal> tmp = pRecord[i];
			pRecord[i] = pRecord[k];
			pRecord[k] = tmp;
			i++;
		}
	}

	void QSort() {
		QSortRec(0, DataCount - 1);
	}
	
	void QSortRec(int start, int finish) {
		int left = start, right = finish;
		Record<TKey, TVal> pivot = pRecord[(start + finish) / 2];
		while (left < right) {
			while (pRecord[left].key < pivot.key) { // .key
				left++;
			}
			while (pRecord[right].key > pivot.key) { // .key
				right--;
			}
			if (left <= right) {
				Record<TKey, TVal> rec = pRecord[left];
				pRecord[left] = pRecord[right];
				pRecotd[right] = rec;
				left++;
				right--;
			}
		}
		if (start < left) {
			QSortRec(start, left);
		}
		if (right < finish) {
			QSort(right, finish);
		}
		
	}
};