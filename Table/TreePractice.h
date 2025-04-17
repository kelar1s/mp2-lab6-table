#pragma once
#include "Record.h"
#include "Table.h"
#include <stack>

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
	//	Легкие случаи: Удалить лист, Один потомок(Поменять местами и удалить)
	// Иначе находим звено идем налево ищем максимум в левом поддереве(идем 1 раз налево потом все направо) -> меняем местами

};