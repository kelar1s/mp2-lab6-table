#pragma once
#include "ScanTable.h"
#include "ArrayTable.h"
#include "Table.h"
#include "Record.h"

enum SortType {
	MergeSortType,
	QuickSortType,
	SelectSortType
};

template<typename TKey, typename TVal>
class SortTable : public ScanTable<TKey, TVal> {
	Record<TKey, TVal>* tmpArr;
public:
	SortTable(int _size = 10) : ScanTable<TKey, TVal>(_size), tmpArr(nullptr) {}

	SortTable(const ScanTable<TKey, TVal>& t, SortType st = QuickSortType ) : ScanTable<TKey, TVal>(t), tmpArr(nullptr) {
		if (st == QuickSortType) {
			QuickSort();
		}
		else if (st == MergeSortType) {
			tmpArr = new Record<TKey, TVal>[size];
			MergeSort(0, dataCount - 1);
		}
		else if (st == SelectSortType) {
			SelectSort();
		}
	}

	~SortTable() {
		delete[] tmpArr;
	}

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
		eff++;
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
		eff++;
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

private:

	void SelectSort() { 
		int i = 0, j = 0; // i - начиная с какого ищем минимальный - j для поиска в оставшейся части
		while (i < dataCount) {
			eff++;
			j = i;
			int minikIndex = i;
			int minik = pRecord[i].key;
			while (j < dataCount) {
				if (pRecord[j].key < minik) {
					minik = pRecord[j].key;
					minikIndex = j;
				}
				j++;
			}
			Record<TKey, TVal> tmp = pRecord[i];
			pRecord[i] = pRecord[minikIndex];
			pRecord[minikIndex] = tmp;
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

	void MergeSort(int left, int right) {
		if (left == right) {
			return;
		}
		int mid = (left + right) / 2;
		MergeSort(left, mid);
		MergeSort(mid + 1, right);
		Merge(left, mid, right);
	}

	void Merge(int left, int mid, int right) {
		int i = left, j = mid + 1, k = left;
		while (i <= mid && j <= right) {
			if (pRecord[i].key < pRecord[j].key) {
				tmpArr[k] = pRecord[i];
				i++; k++;
			}
			else if (pRecord[i].key > pRecord[j].key) {
				tmpArr[k] = pRecord[j];
				j++; k++;
			}
		}
		for (; i <= mid; i++, k++) {
			tmpArr[k] = pRecord[i];
		}
		for (; j <= right; j++, k++) {
			tmpArr[k] = pRecord[j];
		}
		for (int i = left; i <= right; i++) {
			pRecord[i] = tmpArr[i];
		}
	}
};