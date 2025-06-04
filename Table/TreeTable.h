#pragma once
#include <stack>
#include <iostream>
#include "Table.h"
#include "TreeNode.h"

template <typename TKey, typename TVal>
class TreeTable : public Table<TKey, TVal> {
protected:
	TreeNode<TKey, TVal>* pRoot, * pCurr, * pPrev;
	std::stack<TreeNode<TKey, TVal>*> st;
	int pos = 0, level = 0;
public:

	TreeTable() : pRoot(nullptr), pCurr(nullptr), pPrev(nullptr) {};

	TreeTable(const TreeTable<TKey, TVal>& t) : pRoot(nullptr), pCurr(nullptr), pPrev(nullptr), pos(0), dataCount(other.dataCount), level(0) { pRoot = CopyNode(t.pRoot); }

	~TreeTable() {
		DeleteTreeNodeWithDesc(pRoot);
	}

	void DeleteTreeNodeWithDesc(TreeNode<TKey, TVal>* pNode) {
		if (pNode == nullptr) {
			return;
		}
		DeleteTreeNodeWithDesc(pNode->pLeft);
		DeleteTreeNodeWithDesc(pNode->pRight);
		delete pNode;
	}

	void Clear() {
		DeleteTreeNodeWithDesc(pRoot);
		pRoot = nullptr;
		pCurr = nullptr;
		pPrev = nullptr;
		dataCount = 0;
		eff = 0;
	}

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

	void Insert(Record<TKey, TVal> rec) {
		if (Find(rec.key)) {
			throw - 1;
		}
		TreeNode<TKey, TVal>* new_node = new TreeNode<TKey, TVal>(rec.key, rec.val);
		if (pCurr == nullptr) {
			pRoot = new_node;
		}
		else if (rec.key > pCurr->rec.key) {
			pCurr->pRight = new_node;
		}
		else if (rec.key < pCurr->rec.key) {
			pCurr->pLeft = new_node;
		}
		eff++;
		dataCount++;
	}

	void Delete(TKey key) {
		if (!Find(key)) {
			throw - 1;
		}
		TreeNode<TKey, TVal>* nodeToDelete = pCurr;

		if (pCurr->pRight == nullptr && pCurr->pLeft != nullptr) {
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
		else if (pCurr->pLeft == nullptr && pCurr->pRight != nullptr) {
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
		else if (pCurr->pLeft == nullptr && pCurr->pRight == nullptr) {
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
		if (dataCount == 0) {
			pCurr = nullptr;
			pPrev = nullptr;
		}
	}

	void Reset() {
		pos = 0;
		if (IsEnd()) return;
		pCurr = pRoot;
		while (!st.empty()) {
			st.pop();
		}
		while (pCurr->pLeft != nullptr) {
			st.push(pCurr);
			pCurr = pCurr->pLeft;
		}
		pos = 0;
	}

	void GoNext() {
		pCurr = pCurr->pRight;
		pos++;
		if (IsEnd()) return;
		if (pCurr == nullptr && !st.empty()) {
			pCurr = st.top();
			st.pop();
		}
		else {
			while (pCurr->pLeft != nullptr) {
				st.push(pCurr);
				pCurr = pCurr->pLeft;
			}
		}
	}

	bool IsEnd() {
		return pos >= dataCount;
	}

	void PrintRec(std::ostream& os, TreeNode<TKey, TVal>* p) {
		if (p == nullptr) {
			return;
		}
		for (int i = 0; i < level; i++) {
			os << "  ";
		}
		os << "level " << level << ": " << p->rec.key << " (bal: " << p->bal << ")" << endl;
		level++;
		PrintRec(os, p->pRight);
		PrintRec(os, p->pLeft);
		level--;
	}

	void PrintTree(std::ostream& os) {
		level = 0;
		PrintRec(os, pRoot);
	}

	Record<TKey, TVal> GetCurr() {
		return pCurr->rec;
	}

	TKey GetCurrKey() {
		return pCurr->rec.key;
	}

	TVal GetCurrVal() {
		return pCurr->rec.val;
	}

	bool IsFull() const {
		try {
			TreeNode<TKey, TVal>* tmp = new TreeNode<TKey, TVal>;
			delete tmp;
			return false;
		}
		catch (...) {
			return true;
		}
	}
};