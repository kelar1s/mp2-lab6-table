#pragma once
#include "TreeTable.h"

const int H_OK = 0; const int H_INC = 1; const int H_DEC = -1;
const bool InsTN = 1; const bool DelTN = 0;

template <typename TKey, typename TVal>
class BalancedTreeTable : public TreeTable<TKey, TVal> {
protected:
	int InsertBalancedTreeNode(TreeNode<TKey, TVal>*& pNode, Record<TKey, TVal> rec) { //по ссылке корень тк он может измениться
		int res = H_OK;
		if (pNode == nullptr) {
			eff++;
			pNode = new TreeNode<TKey, TVal>(rec.key, rec.val);
			res = H_INC;
			dataCount++;
		}
		else if (pNode->rec.key > rec.key) {
			eff++;
			int tmp = InsertBalancedTreeNode(pNode->pLeft, rec);
			if (tmp == H_INC) {
				res = BalanceTreeLeft(pNode);
			}
		}
		else if (pNode->rec.key < rec.key) {
			eff++;
			int tmp = InsertBalancedTreeNode(pNode->pRight, rec);
			if (tmp == H_INC) {
				res = BalanceTreeRight(pNode);
			}
		}
		return res;
	}

	int BalanceTreeLeft(TreeNode<TKey, TVal>*& pNode, bool flag = InsTN) {
		int res = H_OK;
		if (pNode->bal == BAL_RIGHT) {
			pNode->bal = BAL_OK;
			res = H_OK;
		}
		else if (pNode->bal == BAL_OK) {
			pNode->bal = BAL_LEFT;
			res = H_INC;
		}
		else if (pNode->bal == BAL_LEFT) {
			TreeNode<TKey, TVal>* p1 = pNode->pLeft;
			if (p1->Bal == BAL_LEFT) {
				pNode->pLeft = p1->pRight;
				p1->pRight = pNode;
				pNode->bal = BAL_OK;
				pNode = p1;
				pNode->bal = BAL_OK;
			}
			else {
				TreeNode<TKey, TVal>* p2 = p1->pRight;
				p1->pRight = p2->pLeft;
				p2->pLeft = p1;
				pNode->pLeft = p2->pRight;
				if (p2->bal == BAL_LEFT) {
					pNode->bal = BAL_RIGHT;
				}
				else {
					pNode->bal = BAL_OK;
				}
				if (p2->bal == BAL_RIGHT) {
					pNode->bal = BAL_LEFT;
				}
				else {
					p1->bal = BAL_OK;
				}
				pNode = p2;
				pNode->bal = BAL_OK;
				res = H_OK;
			}
		}
		return res;
	}

	int BalanceTreeRight(TreeNode<TKey, TVal>*& pNode, bool flag = InsTN) {
		
	}

	int DeleteBalancedTreeNode(TreeNode<TKey, TVal>*& pNode, TKey key) {
		int res = H_OK;
		eff++;
		if (pNode == nullptr) {
			return res;
		}
		else if (key > pNode->rec.key) {
			int tmp = DeleteBalancedTreeNode(pNode->pRight, key);
			if (tmp == H_DEC) {
				res = BalanceTreeLeft(pNode, DelTN);
			}
		}
		else if (key < pNode->rec.key) {
			int tmp = DeleteBalancedTreeNode(pNode->pLeft, key);
			if (tmp == H_DEC) {
				res = BalanceTreeRight(pNode, DelTN);
			}
		}
		else {
			dataCount--;
			if (pNode->pLeft == nullptr && pNode->pRight == nullptr) {
				delete pNode;
				pNode = nullptr;
				res = H_DEC;
			}
			else if (pNode->pLeft == nullptr && pNode->pRight != nullptr) {
				pNode->rec = pNode->pRight->rec;
				delete pNode->pRight;
				pNode->pRight = nullptr;
				pNode->bal = BAL_OK;
				res = H_DEC;
			}
			else if (pNode->pRight == nullptr && pNode->pLeft != nullptr) {
				pNode->rec = pNode->pLeft->rec;
				delete pNode->pLeft;
				pNode->pLeft = nullptr;
				pNode->bal = BAL_OK;
				res = H_DEC;
			}
			else {
				TreeNode<TKey, TVal> left = pNode->pLeft;
				TreeNode<TKey, TVal> right = pNode->pRight;
				TreeNode<TKey, TVal> minik = FindMin(right);
				res = RemoveMin(right);
				pNode->rec = minik->rec;
				delete minik;
				pNode->pLeft = left;
				pNode->pRight = right;
				if (res != H_OK) {
					res = BalanceTreeLeft(pNode, DelTN);
				}
			}
		}
		return res;
	}

	TreeNode<TKey, TVal>* FindMin(TreeNode<TKey, TVal>* pNode) {
		TreeNode<TKey, TVal>* current = pNode;
		while (current->left != nullptr) {
			current = current->left;
		}
		return current;
	}

	int RemoveMin(TreeNode<TKey, TVal>*& pNode) {
		int res = H_OK;
		if (pNode->pLeft == nullptr) {
			pNode = pNode->pRight;
			res = H_DEC;
		}
		else {
			res = RemoveMin(pNode->pLeft);
			if (res != H_OK) {
				res = BalanceTreeRight(pNode, DelTN);
			}
		}
		return res;
	}

	void DeleteTreeNodeWithDesc(TreeNode<TKey, TVal>* pNode) {
		DeleteTreeNodeWithDesc(pNode->pLeft);
		DeleteTreeNodeWithDesc(pNode->pRight);
		delete pNode;
	}
public:
	~BalancedTreeTable() {
		DeleteTreeNodeWithDesc(pRoot);
	}

	bool IsEmpty() {
		return pRoot == nullptr;
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
		if (Find(rec.key) || IsEmpty()) {
			throw - 1;
		}
		InsertBalancedTreeNode(pRoot, rec);
	}

	void Delete(TKey key) {
		if (!Find(key)) {
			throw - 1;
		}
		DeleteBalancedTreeNode(pRoot, key);
	}
};