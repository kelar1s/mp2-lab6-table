#pragma once
#include "HashTable.h"

template<typename TKey, typename TVal>
class ArrayHashTable : public HashTable<TKey, TVal> {
protected:
	Record<TKey, TVal>* pRec;
	int step, currentIndex;
	Record<TKey, TVal> free, del;
public:
	ArrayHashTable(int _size = 100, int _step = 17): step(_step), currentIndex(0) {
		size = _size;
		eff = 0;
		dataCount = 0;
		free.key = -1;
		del.key = -2;
		pRec = new Record<TKey, TVal>[size];
		for (int i = 0; i < size; i++) {
			pRec[i] = free;
		}
	}

	ArrayHashTable(const ArrayHashTable& oth) {
		size = oth.size;
		pRec = new Record<TKey, TVal>[size];
		eff = oth.eff;
		dataCount = oth.dataCount;
		step = oth.step;
		currentIndex = oth.currentIndex;
		free = oth.free;
		del = oth.del;
		for (int i = 0; i < size; i++) {
			pRec[i] = oth.pRec[i];
		}
	}

	~ArrayHashTable() {
		delete[] pRec;
	}

	bool IsFull() const {
		return dataCount == size;
	}

	bool Find(TKey key) {
		int temp = -1;
		currentIndex = HashFunc(key);
		for (int i = 0; i < size; i++) {
			eff++;
			if (pRec[currentIndex] == free) {
				break;
			}
			else if (pRec[currentIndex] == del && temp == -1) {
				temp = currentIndex;
			}
			else if (pRec[currentIndex].key == key) {
				return true;
			}
			currentIndex = (currentIndex + step) % size;
		}
		if (temp != -1) {
			eff++;
			currentIndex = temp;
		}
		return false;
	}

	void Insert(Record<TKey, TVal> rec) {
		if (Find(rec.key) || IsFull()) {
			throw -1;
		}
		eff++;
		pRec[currentIndex] = rec;
		dataCount++;
	}

	void Delete(TKey key) {
		if (!Find(key)) {
			throw -1;
		}
		eff++;
		pRec[currentIndex] = del;
		dataCount--;
	}

	Record<TKey, TVal> GetCurr() {
		return pRec[currentIndex];
	}

	TKey GetCurrKey() {
		return pRec[currentIndex].key;
	}

	TVal GetCurrVal() {
		return pRec[currentIndex].val;
	}

	void Reset() {
		currentIndex = 0;
		while (currentIndex < size &&
			(pRec[currentIndex] == free || pRec[currentIndex] == del)) {
			currentIndex++;
		}
	}

	void GoNext() {
		currentIndex++;
		while (pRec[currentIndex] == free || pRec[currentIndex] == del) {
			currentIndex++;
		}
	}

	bool IsEnd() {
		return currentIndex == size;
	}
	
	void Clear() {
		currentIndex = 0;
		dataCount = 0;
		ClearEff();
		for (int i = 0; i < size; i++) {
			pRec[i] = free;
		}
	}
};