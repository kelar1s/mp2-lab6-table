#pragma once
#include "ScanTable.h"
#include "ArrayTable.h"
#include "Table.h"
#include "Record.h"

template<typename TKey, typename TVal>
class SortTable : public ScanTable<TKey, TVal> {
	Record<TKey, TVal>* tmpArr;
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

	void SelectSort() { // i - ������� � ������ ���� ����������� - j ��� ������ � ���������� �����
		int i = 0, j = 0;
		while (i < dataCount) {
			eff++;
			j = i;
			int k = i; // ������ ������������
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
			if (pRec[i].key < pRec[j].key) {
				tmpArr[k] = pRec[i];
				i++; k++;
			}
			else if (pRec[i].key > pRec[j].key) {
				tmpArr[k] = pRec[j];
				j++; k++;
			}
			else {
				tmpArr[k] = tmpArr[k + 1] = pRec[i];
				i++; j++; k += 2;
			}
		}
		for (; i <= mid; i++, k++) {
			tmpArr[k] = pRec[i];
		}
		for (; j <= right; j++, k++) {
			tmpArr[k] = pRec[j];
		}
		for (int i = left; i <= right; i++) {
			pRec[i] = tmpArr[i];
		}
	}
};