#pragma once
#include "TreePractice.h"

const int H_OK, H_INC, H_DEC;

template <typename TKey, typename TVal>
class TBalTreeTable : public TreeTable<TKey, TVal> {
protected:
	int InsBalTree(TreeNode<TKey, TVal>*& pNode, Record<TKey, TVal> rec) { //по ссылке корень тк он может измениться
		int res = H_OK;
		if (pNode == nullptr) {
			eff++;
			pNode = new TreeNode<TKey, TVal>(rec.key, rec.val);
			res = H_INC;
			dataCount++;
		}
		else if (pNode->rec.key > rec.key) {
			eff++;
			int tmp = InsBalTree(pNode->pLeft, rec);
			if (tmp == H_INC) {
				res = BalTreeLeft(pNode);
			}
		}
		else if (pNode->rec.key < rec.key) {
			eff++;
			int tmp = InsBalTree(pNode->pRight, rec);
			if (tmp == H_INC) {
				res = BalTreeRight(pNode);
			}
		}
		return res;
	}

	int BalTreeLeft(TreeNode<TKey, TVal>*& pNode) {
		int res = H_OK;
		if (pNode->bal == BAL_RIGHT) {
			pNode->bal = BAL_OK;
			res = H_OK;
		}
		else if (pNode->bal == BAL_OK) {
			pNode->bal = BAL_LEFT;
			res = H_INC;
		}
		else (pNode->bal == BAL_LEFT) {
			TreeNode<TKey, TVal>* p1 = pNode->pLeft;
			if (pl->Bal == BAL_LEFT) {
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

	int BalTreeRight(TreeNode<TKey, TVal>*& pNode) {

	}
public:
	void Insert(Record<TKey, TVal> rec) {
		if (Find(rec.key)) {
			throw - 1;
		}
		InsBalTree(pRoot, rec);
	}
};