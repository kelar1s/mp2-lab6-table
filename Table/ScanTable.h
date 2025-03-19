#pragma once
#include "ArrayTable.h"
#include "Table.h"
#include "Record.h"

template<typename TKey, typename TVal>
class ScanTable : public ArrayTable<TKey, TVal> {
public:
	ScanTable(int _size) : ArrayTable<TKey, TVal>(_size) {}
	
	bool Find(TKey key) {
		for (int i = 0; i < this->dataCount; i++) {
			this->eff++;
			if (key == this->pRecord[i].key) {
				this->currentIndex = i;
				return true;
			}
		}
		this->currentIndex = this->dataCount;
		return false;
	}

	void Insert(Record<TKey, TVal> record) {
		if (Find(record.key)) {
			throw -1;
		}
		if (this->dataCount == this->size) {
			throw -1;
		}
		this->pRecord[this->currentIndex] = record;
		this->dataCount++;
		this->eff++;
	}

	void Delete(TKey key) {
		if (!Find(key)) {
			throw -1;
		}
		this->pRecord[this->currentIndex] = this->pRecord[this->dataCount - 1];
		this->dataCount--;
		this->eff++;
	}

	bool IsFull() const override {
		return this->dataCount == this->size;
	}

	Record<TKey, TVal> GetCurr() override {
		if (this->currentIndex < 0 || this->currentIndex >= this->dataCount) {
			throw -1;
		}
		return this->pRecord[this->currentIndex];
	}

	TKey GetCurrKey() override {
		if (this->currentIndex < 0 || this->currentIndex >= this->dataCount) {
			throw -1;
		}
		return this->pRecord[this->currentIndex].key;
	}

	TVal GetCurrVal() override {
		if (this->currentIndex < 0 || this->currentIndex >= this->dataCount) {
			throw -1;
		}
		return this->pRecord[this->currentIndex].val;
	}

	void SelectSort() { // i - начиная с какого ищем минимальный - j для поиска в оставшейся части
		int i = 0, j = 0;
		while (i < dataCount) {
			eff++;
			j = i;
			int k = i; // индекс минимального
			int minik = pRecord[i].key;
			while (j < dataCount) {
				if (pRecord[j].key < minik) {
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

	void QuickSort() {
		QSortRec(0, dataCount - 1);
	}

	void QSortRec(int start, int finish) {
		if (start >= finish) {
			return;
		}
		int left = start, right = finish;
		Record<TKey, TVal> pivot = pRecord[(start + finish) / 2];

		while (left <= right) {
			while (pRecord[left].key < pivot.key) {
				left++;
			}
			while (pRecord[right].key > pivot.key) {
				right--;
			}
			if (left <= right) {
				Record<TKey, TVal> temp = pRecord[left];
				pRecord[left] = pRecord[right];
				pRecord[right] = temp;
				left++;
				right--;
			}
		}
		if (start < right) {
			QSortRec(start, right);
		}
		if (left < finish) {
			QSortRec(left, finish);
		}
	}
};

