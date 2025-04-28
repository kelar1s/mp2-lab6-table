#pragma once
#include "Record.h"
#include "Table.h"
#include <stack>
#include <iostream>
using namespace std;

template <typename TKey, typename TVal>
struct TreeNode {
	Record<TKey, TVal> rec;
	TreeNode *pLeft = nullptr;
	TreeNode *pRight = nullptr;
	int bal; // Показатель отвечающий за балансировку
public:
	TreeNode(TKey key, TVal val) : rec(key, val) {};
};

template <typename TKey, typename TVal>
class TreeTable : Table<TKey, TVal> {
protected:
	TreeNode *pRoot, *pCurr, *pPrev;
	std::stack<TreeNode*> st;
	int pos, level;
public: 
	TreeTable() : pRoot(nullptr), pCurr(nullptr), pPrev(nullptr) {};

	bool Find(TKey key) {
		pCurr = pRoot;
		while (pCurr != nullptr) {
			eff++;
			if (key > pCurr->rec.key) {
				pPrev = pCurr;
				pCurr = pCurr->pRight;
			}
			else if (key < pCurr->rec.key) {
				pPrev = pCurr;
				pCurr = pCurr->pLeft;
			}
			else if (key == pCurr->rec.key) {
				return true;
			}
		}
		eff++;
		pCurr = pPrev;
		return false;
	}

	void Insert(Record<TKey, TVal> record) {
		if (Find(record.key)) {
			throw -1;
		}
		TreeNode<Tkey, Tval>* new_node = new TreeNode<TKey, TVal>(record.key, record.val);
		if (pCurr == nullptr) {
			pRoot = new_node;
		}
		else if (record.key > pCurr->rec.key) {
			pCurr->pRight = new_node;
		}
		else if (record.key < pCurr->rec.key){
			pCurr->pLeft = new_node;
		}
		eff++;
		dataCount++;
	}

	void Delete(TKey key) {
		if (!Find(key)) {
			throw -1;
		}
		TreeNode<TKey, TVal>* nodeToDelete = pCurr;
		//Один потомок слева
		if (pCurr->pRight == nullptr && pCurr->pLeft != nullptr) { //На практике без !=
			eff++;
			TreeNode<TKey, TVal>* child = pCurr->pLeft;
			if (nodeToDelete == pRoot) {
				pRoot = child;
			}
			else {
				if (pPrev->pLeft == nodeToDelete) {
					pPrev->pLeft = child;
				}
				else {
					pPrev->pRight = child;
				}
			}
		}
		//Один потомок справа
		else if (pCurr->pLeft == nullptr && pCurr->pRight != nullptr) { //На практике без !=
			eff++;
			TreeNode<TKey, TVal>* child = pCurr->pRight;
			if (nodeToDelete == pRoot) {
				pRoot = child;
			}
			else {
				if (pPrev->pLeft == nodeToDelete) {
					pPrev->pLeft = child;
				}
				else {
					pPrev->pRight = child;
				}
			}
		}
		//Нет потомков - Лист
		else if (pCurr->pLeft == nullptr && pCurr->pRight == nullptr) { // На практике не реализовывали
			eff++;
			if (nodeToDelete == pRoot) {
				pRoot = nullptr;
			}
			else {
				if (pPrev->pLeft == nodeToDelete) {
					pPrev->pLeft = nullptr;
				}
				else {
					pPrev->pRight = nullptr;
				}
			}
		}
		//Оба потомка
		else {
			TreeNode<TKey, TVal>* beforeMaxLeft = nodeToDelete;
			TreeNode<TKey, TVal>* maxLeft = nodeToDelete->pLeft;
			while (maxLeft->pRight != nullptr) {
				eff++;
				beforeMaxLeft = maxLeft;
				maxLeft = maxLeft->pRight;
			}
			nodeToDelete->rec = maxLeft->rec;
			if (nodeToDelete->pLeft == maxLeft) {
				nodeToDelete->pLeft = maxLeft->pLeft;
			}
			else {
				beforeMaxLeft->pRight = maxLeft->pLeft;
			}
			eff++;
			nodeToDelete = maxLeft;
		}
		delete nodeToDelete;
		dataCount--;
	}
	
	void Reset() {
		pCurr = pRoot;
		while (!st.empty()) {
			st.pop();
		}
		while (pCurr->pLeft != nullptr) {
			st.push(pCurr);
			pCurr = pCurr->pLeft;
		}
		st.push(pCurr);
		pos = 0;
	}

	void GoNext() {
		pCurr = pCurr->pRight;
		st.pop();
		if (pCurr == nullptr && !st.empty()) {
			pCurr = st.top();
		}
		else {
			while (pCurr->pLeft != nullptr) {
				st.push(pCurr);
				pCurr = pCurr->pLeft;
			}
			st.push(pCurr);
		}
		pos++;
	}

	bool IsEnd() {
		return pos == dataCount;
	}

	void  PrintRec(ostream& os, TreeNode<TKey, TVal>* p) {
		if (p == nullptr) {
			return;
		}
		for (int i = 0; i < level; i++) {
			os << " ";
		}
		os << p->rec.key; << endl;
		level++;
		PrintRec(os, p->pRight);
		PrintRec(os, p->pLeft);
		level--;
	}

	void PrintTree(ostream& os) {
		level = 0;
		PrintRec(os, pRoot);
	}
};