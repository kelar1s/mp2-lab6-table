#pragma once
#include "TreeTable.h"

const int H_OK = 0; const int H_INC = 1; const int H_DEC = -1;
const bool InsTN = 1; const bool DelTN = 0;

template <typename TKey, typename TVal>
class BalancedTreeTable : public TreeTable<TKey, TVal> {
protected:
    int InsertBalancedTreeNode(TreeNode<TKey, TVal>*& pNode, Record<TKey, TVal> rec) {
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
                res = BalanceTreeLeft(pNode, InsTN);
            }
        }
        else if (pNode->rec.key < rec.key) {
            eff++;
            int tmp = InsertBalancedTreeNode(pNode->pRight, rec);
            if (tmp == H_INC) {
                res = BalanceTreeRight(pNode, InsTN);
            }
        }
        return res;
    }

    int BalanceTreeLeft(TreeNode<TKey, TVal>*& pNode, bool flag = InsTN) {
        if (pNode == nullptr) return H_OK;
        int res = H_OK;
        if (pNode->bal == BAL_RIGHT) {
            pNode->bal = BAL_OK;
            res = (flag == InsTN) ? H_OK : H_DEC;
        }
        else if (pNode->bal == BAL_OK) {
            pNode->bal = BAL_LEFT;
            res = (flag == InsTN) ? H_INC : H_OK;
        }
        else { 
            TreeNode<TKey, TVal>* p1 = pNode->pLeft;
            if (p1->bal == BAL_LEFT) {
                pNode->pLeft = p1->pRight;
                p1->pRight = pNode;
                pNode->bal = BAL_OK;
                pNode = p1;
            }
            else {
                TreeNode<TKey, TVal>* p2 = p1->pRight;
                p1->pRight = p2->pLeft;
                p2->pLeft = p1;
                pNode->pLeft = p2->pRight;
                p2->pRight = pNode;

                if (p2->bal == BAL_LEFT) {
                    pNode->bal = BAL_RIGHT;
                    p1->bal = BAL_OK;
                }
                else if (p2->bal == BAL_RIGHT) {
                    pNode->bal = BAL_OK;
                    p1->bal = BAL_LEFT;
                }
                else {
                    pNode->bal = BAL_OK;
                    p1->bal = BAL_OK;
                }
                pNode = p2;
            }
            pNode->bal = BAL_OK;
            res = (flag == InsTN) ? H_OK : H_DEC;
        }
        return res;
    }

    int BalanceTreeRight(TreeNode<TKey, TVal>*& pNode, bool flag = InsTN) {
        if (pNode == nullptr) return H_OK;
        int res = H_OK;
        if (pNode->bal == BAL_LEFT) {
            pNode->bal = BAL_OK;
            res = (flag == InsTN) ? H_OK : H_DEC;
        }
        else if (pNode->bal == BAL_OK) {
            pNode->bal = BAL_RIGHT;
            res = (flag == InsTN) ? H_INC : H_OK;
        }
        else { 
            TreeNode<TKey, TVal>* p1 = pNode->pRight;
            if (p1->bal == BAL_RIGHT || (flag == DelTN && p1->bal == BAL_OK)) {
                pNode->pRight = p1->pLeft;
                p1->pLeft = pNode;
                if (p1->bal == BAL_RIGHT) {
                    pNode->bal = BAL_OK;
                    p1->bal = BAL_OK;
                }
                else {
                    pNode->bal = BAL_RIGHT;
                    p1->bal = BAL_LEFT;
                }

                pNode = p1;
                res = (flag == InsTN) ? H_OK : H_DEC;
            }
            else {
                TreeNode<TKey, TVal>* p2 = p1->pLeft;
                p1->pLeft = p2->pRight;
                p2->pRight = p1;
                pNode->pRight = p2->pLeft;
                p2->pLeft = pNode;
                if (p2->bal == BAL_RIGHT) {
                    pNode->bal = BAL_LEFT;
                    p1->bal = BAL_OK;
                }
                else if (p2->bal == BAL_LEFT) {
                    pNode->bal = BAL_OK;
                    p1->bal = BAL_RIGHT;
                }
                else { 
                    pNode->bal = BAL_OK;
                    p1->bal = BAL_OK;
                }

                pNode = p2;
                pNode->bal = BAL_OK;
                res = (flag == InsTN) ? H_OK : H_DEC;
            }
        }
        return res;
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
                TreeNode<TKey, TVal>* temp = pNode->pRight;
                delete pNode;
                pNode = temp;
                res = H_DEC;
            }
            else if (pNode->pRight == nullptr && pNode->pLeft != nullptr) {
                TreeNode<TKey, TVal>* temp = pNode->pLeft;
                delete pNode;
                pNode = temp;
                res = H_DEC;
            }
            else {
                TreeNode<TKey, TVal>* minNode = FindMin(pNode->pRight);
                pNode->rec = minNode->rec;
                int tmp = RemoveMin(pNode->pRight);
                if (tmp == H_DEC) {
                    res = BalanceTreeLeft(pNode, DelTN);
                }
            }
        }
        return res;
    }

    TreeNode<TKey, TVal>* FindMin(TreeNode<TKey, TVal>* pNode) {
        if (pNode == nullptr) return nullptr;
        while (pNode->pLeft != nullptr) {
            pNode = pNode->pLeft;
        }
        return pNode;
    }

    int RemoveMin(TreeNode<TKey, TVal>*& pNode) {
        int res = H_OK;
        if (pNode->pLeft == nullptr) {
            TreeNode<TKey, TVal>* temp = pNode->pRight;
            delete pNode;
            pNode = temp;
            res = H_DEC;
        }
        else {
            res = RemoveMin(pNode->pLeft);
            if (res == H_DEC) {
                res = BalanceTreeRight(pNode, DelTN);
            }
        }
        return res;
    }

public:
    bool IsEmpty() const {
        return pRoot == nullptr;
    }

    bool Find(TKey key) {
        pCurr = pRoot;
        pPrev = nullptr;
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
            else {
                return true;
            }
        }
        eff++;
        pCurr = pPrev;
        return false;
    }

    void Insert(Record<TKey, TVal> rec) {
        if (Find(rec.key)) {
            throw -1;
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