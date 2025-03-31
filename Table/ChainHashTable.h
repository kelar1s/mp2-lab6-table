#pragma once
#include "HashTable.h"

template<typename TKey, typename TVal>
class ChainHashTable: public HashTable<TKey, TVal> {
	Record<TKey, TVal>** pRec;
	int chainSize;
	int currentChain, currentPositionInChain;
public:
	ChainHashTable(int _size = 10, int _chainSize = 5)
	{
		eff = 0;
		dataCount = 0;
		size = _size;
		chainSize = _chainSize;
		pRec = new Record<TKey, TVal>*[size];
		for (int i = 0; i < size; i++) {
			pRec[i] = new Record<TKey, TVal>[chainSize];
			for (int j = 0; j < chainSize; j++) {
				pRec[i][j] = -1;
			}
		}
	}

	bool Find(TKey key) {
		currentChain = HashFunc(key);
		for (currentPositionInChain = 0; currentPositionInChain < chainSize; currentPositionInChain++) {
			eff++;
			if (pRec[currentChain][currentPositionInChain].key == key) {

			}
		}
	}

};