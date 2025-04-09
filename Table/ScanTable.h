#pragma once
#include "ArrayTable.h"
#include "Table.h"
#include "Record.h"

template<typename TKey, typename TVal>
class ScanTable : public ArrayTable<TKey, TVal> {
public:

	 // Временный для хранения

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

	
};