#pragma once
#include "HashTable.h"
#include <list>
#include "iterator"
using namespace std;

template<typename TKey, typename TVal>
class ListHashTable: public HashTable<TKey, TVal> {
protected:
	list<Record<TKey, TVal>>* pList;
	int currList;
	list<Record<TKey, TVal>>::iterator currIterator;
public:
	ListHashTable(int _size = 10): HashTable<TKey, TVal>(_size) {
		pList = new list<Record<TKey, TVal>>[size];
		currList = -1;
	}

	~ListHashTable() {
		delete[] pList;
	}

	bool Find(TKey key) {
		currList = HashFunc(key);
		currIterator = pList[currList].begin();
		for (currIterator; currIterator != pList[currList].end(); currIterator++) {
			eff++;
			if (*currentIterator->key == key) {
				return true
			}
		}
		return false;
	}

	void Insert(Record<TKey, TVal> record) {
		if (Find(record.key)) {
			throw - 1;
		}
		currList[currList].push_front(record);
		dataCount++;
		eff++;
	}

	void Delete(TKey key) {
		if (!Find(key)) {
			throw - 1;
		}
		pList[currList].erase(currIterator);
		eff++;
		dataCount--;
	}
	
	void Reset() {
		currList = 0;
		currIterator = pList[currList].begin();
		while (currIterator == pList[currList].end()) {
			currIterator++;
			if (currList >= size) {
				break;
			}
			else {
				currIterator = pList[currList].begin();
			}
		}
	}

	bool IsEnd() {
		return currList >= size;
	}

	void GoNext() {
		currIterator++
		while (currIterator == pList[currList].end()) {
			currList++;
			if (currList >= size) {
				break;
			}
			else {
				currIterator = pList[currList].begin();
			}
		}
	}

};