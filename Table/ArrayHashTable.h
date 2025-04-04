#pragma once
#include "HashTable.h"

template<typename TKey, typename TVal>
class ArrayHashTable : public HashTable<TKey, TVal> {
protected:
	Record<TKey, TVal>* pRec;
	int step, currentIndex;
	Record<TKey, TVal> free, del;
public:
	ArrayHashTable(int _size = 100, int _step = 17) {
		eff = 0;
		dataCount = 0;
		size = _size;
		pRec = new Record<TKey, TVal>[size];
		free.key = -1;
		del.key = -2;
		step = _step;
		currentIndex = 0;
		for (int i = 0; i < size; i++) {
			pRec[i].key = free;
		}
	}

	ArrayHashTable(const ArrayHashTable& oth) {
		size = oth.size;
		pRec = new Record<TKey, TVal>[size];
		eff = oth.eff;
		dataCount = oth.dataCount;
		free = oth.free;
		del = oth.del;
		step = oth.step;
		currentIndex = oth.currentIndex;
		for (int i = 0; i < size; i++) {
			pRec[i] = oth.pRec[i];
		}
	}

	~ArrayHashTable() {
		delte[] pRec;
	}

	bool Find(TKey key) {
		int temp = -1;
		currentIndex = HashFunc(key);
		for (int i = 0; i < size; i++) {
			eff++;
			if (pRec[currentIndex].key == free) {
				break;
			}
			else if (pRec[currentIndex].key == del && tmp == -1) {
				temp = currentIndex;
			}
			else if (pRec[currentIndex].key == key) {
				return true;
			}
			currentIndex = (currentIndex + step) % size;
		}
		if (temp != -1) {
			currentIndex = tmp;
		}
		return false;
	}

	bool IsFull() {
		return dataCount == size;
	}

	void Insert(Record<TKey, TVal> rec) {
		if (Find(rec.key)) {
			throw -1;
		}
		eff++;
		pRec[currentIndex] = rec;
		dataCount++;
	}

	void Delete(TKey key) {
		if (!Find(rec.key)) {
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
		for (int i = 0; i < size; i++) {
			if (pRec[i] != free || pRec[i] != del) {
				currentIndex = i;
				break;
			}
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
	
};