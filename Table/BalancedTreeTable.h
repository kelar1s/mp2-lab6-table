#pragma once
#include "TreeTable.h"
#include "TreeNode.h"


const int H_OK = 0; const int H_INC = 1; const int H_DEC = -1;

enum Operation {
    INS,
    DEL
};

template <typename TKey, typename TVal>
class BalancedTreeTable : public TreeTable<TKey, TVal>
{
protected:
    int InsertBalancedTreeTable(TreeNode<TKey, TVal>*& pNode, Record<TKey, TVal> rec) {
        int result = H_OK;
        if (pNode == nullptr) {
            pNode = new TreeNode<TKey, TVal>(rec.key, rec.val);
            result = H_INC;
            dataCount++;
        }
        else {
            if (rec.key < pNode->rec.key) {
                int temp = InsertBalancedTreeTable(pNode->pLeft, rec);
                if (temp == H_INC) {
                    result = BalanceLeft(pNode, INS);
                }
            }
            else if (rec.key > pNode->rec.key) {
                int temp = InsertBalancedTreeTable(pNode->pRight, rec);
                if (temp == H_INC) {
                    result = BalanceRight(pNode, INS);
                }
            }
            else {
                throw - 1;
            }
        }
        return result;
    }

    int BalanceLeft(TreeNode<TKey, TVal>*& pNode, Operation mode) {
        int result = H_OK;
        if (mode == INS) {
            if (pNode->bal == BAL_RIGHT) {
                pNode->bal = BAL_OK;
                result = H_OK;
            }
            else if (pNode->bal == BAL_OK) {
                pNode->bal = BAL_LEFT;
                result = H_INC;
            }
            else {
                if (pNode->pLeft == nullptr) {
                    pNode->bal = BAL_OK;
                    return H_DEC;
                }

                TreeNode<TKey, TVal>* leftChild = pNode->pLeft;
                if (leftChild->bal == BAL_LEFT) {
                    pNode->pLeft = leftChild->pRight;
                    leftChild->pRight = pNode;
                    pNode = leftChild;
                    pNode->bal = BAL_OK;
                    pNode->pRight->bal = BAL_OK;
                    result = H_OK;
                }
                else {
                    if (leftChild->pRight == nullptr) {
                        pNode->bal = BAL_OK;
                        return H_DEC;
                    }

                    TreeNode<TKey, TVal>* rightChild = leftChild->pRight;
                    leftChild->pRight = rightChild->pLeft;
                    rightChild->pLeft = leftChild;
                    pNode->pLeft = rightChild->pRight;
                    rightChild->pRight = pNode;

                    if (rightChild->bal == BAL_LEFT) {
                        pNode->bal = BAL_RIGHT;
                        leftChild->bal = BAL_OK;
                    }
                    else if (rightChild->bal == BAL_RIGHT) {
                        pNode->bal = BAL_OK;
                        leftChild->bal = BAL_LEFT;
                    }
                    else {
                        pNode->bal = BAL_OK;
                        leftChild->bal = BAL_OK;
                    }
                    pNode = rightChild;
                    pNode->bal = BAL_OK;
                    result = H_OK;
                }
            }
        }
        else {
            if (pNode->bal == BAL_RIGHT) {
                pNode->bal = BAL_OK;
                result = H_DEC;
            }
            else if (pNode->bal == BAL_OK) {
                pNode->bal = BAL_LEFT;
                result = H_OK;
            }
            else {
                if (pNode->pLeft == nullptr) {
                    pNode->bal = BAL_OK;
                    return H_DEC;
                }

                TreeNode<TKey, TVal>* leftChild = pNode->pLeft;
                if (leftChild->bal != BAL_RIGHT) {
                    pNode->pLeft = leftChild->pRight;
                    leftChild->pRight = pNode;
                    if (leftChild->bal == BAL_OK) {
                        pNode->bal = BAL_LEFT;
                        leftChild->bal = BAL_RIGHT;
                        result = H_OK;
                    }
                    else {
                        pNode->bal = BAL_OK;
                        leftChild->bal = BAL_OK;
                        result = H_DEC;
                    }
                    pNode = leftChild;
                }
                else {
                    if (leftChild->pRight == nullptr) {
                        pNode->bal = BAL_OK;
                        return H_DEC;
                    }

                    TreeNode<TKey, TVal>* rightChild = leftChild->pRight;
                    leftChild->pRight = rightChild->pLeft;
                    rightChild->pLeft = leftChild;
                    pNode->pLeft = rightChild->pRight;
                    rightChild->pRight = pNode;

                    if (rightChild->bal == BAL_LEFT) {
                        pNode->bal = BAL_RIGHT;
                        leftChild->bal = BAL_OK;
                    }
                    else if (rightChild->bal == BAL_RIGHT) {
                        pNode->bal = BAL_OK;
                        leftChild->bal = BAL_LEFT;
                    }
                    else {
                        pNode->bal = BAL_OK;
                        leftChild->bal = BAL_OK;
                    }
                    pNode = rightChild;
                    pNode->bal = BAL_OK;
                    result = H_DEC;
                }
            }
        }
        return result;
    }

    int BalanceRight(TreeNode<TKey, TVal>*& pNode, Operation mode) {
        int result = H_OK;
        if (mode == INS) {
            if (pNode->bal == BAL_LEFT) {
                pNode->bal = BAL_OK;
                result = H_OK;
            }
            else if (pNode->bal == BAL_OK) {
                pNode->bal = BAL_RIGHT;
                result = H_INC;
            }
            else {
                if (pNode->pRight == nullptr) {
                    pNode->bal = BAL_OK;
                    return H_DEC;
                }

                TreeNode<TKey, TVal>* rightChild = pNode->pRight;
                if (rightChild->bal == BAL_RIGHT) {
                    pNode->pRight = rightChild->pLeft;
                    rightChild->pLeft = pNode;
                    pNode = rightChild;
                    pNode->bal = BAL_OK;
                    pNode->pLeft->bal = BAL_OK;
                    result = H_OK;
                }
                else {
                    if (rightChild->pLeft == nullptr) {
                        pNode->bal = BAL_OK;
                        return H_DEC;
                    }

                    TreeNode<TKey, TVal>* leftChild = rightChild->pLeft;
                    rightChild->pLeft = leftChild->pRight;
                    leftChild->pRight = rightChild;
                    pNode->pRight = leftChild->pLeft;
                    leftChild->pLeft = pNode;

                    if (leftChild->bal == BAL_RIGHT) {
                        pNode->bal = BAL_LEFT;
                        rightChild->bal = BAL_OK;
                    }
                    else if (leftChild->bal == BAL_LEFT) {
                        pNode->bal = BAL_OK;
                        rightChild->bal = BAL_RIGHT;
                    }
                    else {
                        pNode->bal = BAL_OK;
                        rightChild->bal = BAL_OK;
                    }
                    pNode = leftChild;
                    pNode->bal = BAL_OK;
                    result = H_OK;
                }
            }
        }
        else {
            if (pNode->bal == BAL_LEFT) {
                pNode->bal = BAL_OK;
                result = H_DEC;
            }
            else if (pNode->bal == BAL_OK) {
                pNode->bal = BAL_RIGHT;
                result = H_OK;
            }
            else {
                if (pNode->pRight == nullptr) {
                    pNode->bal = BAL_OK;
                    return H_DEC;
                }

                TreeNode<TKey, TVal>* rightChild = pNode->pRight;
                if (rightChild->bal != BAL_LEFT) {
                    pNode->pRight = rightChild->pLeft;
                    rightChild->pLeft = pNode;
                    if (rightChild->bal == BAL_OK) {
                        pNode->bal = BAL_RIGHT;
                        rightChild->bal = BAL_LEFT;
                        result = H_OK;
                    }
                    else {
                        pNode->bal = BAL_OK;
                        rightChild->bal = BAL_OK;
                        result = H_DEC;
                    }
                    pNode = rightChild;
                }
                else {
                    if (rightChild->pLeft == nullptr) {
                        pNode->bal = BAL_OK;
                        return H_DEC;
                    }

                    TreeNode<TKey, TVal>* leftChild = rightChild->pLeft;
                    rightChild->pLeft = leftChild->pRight;
                    leftChild->pRight = rightChild;
                    pNode->pRight = leftChild->pLeft;
                    leftChild->pLeft = pNode;

                    if (leftChild->bal == BAL_RIGHT) {
                        pNode->bal = BAL_LEFT;
                        rightChild->bal = BAL_OK;
                    }
                    else if (leftChild->bal == BAL_LEFT) {
                        pNode->bal = BAL_OK;
                        rightChild->bal = BAL_RIGHT;
                    }
                    else {
                        pNode->bal = BAL_OK;
                        rightChild->bal = BAL_OK;
                    }
                    pNode = leftChild;
                    pNode->bal = BAL_OK;
                    result = H_DEC;
                }
            }
        }
        return result;
    }

    TreeNode<TKey, TVal>* FindMinimum(TreeNode<TKey, TVal>* pNode) {
        while (pNode && pNode->pLeft) {
            pNode = pNode->pLeft;
        }
        return pNode;
    }

    int RemoveMinimum(TreeNode<TKey, TVal>*& pNode) {
        int result = H_OK;
        if (pNode == nullptr) return H_OK;

        if (pNode->pLeft == nullptr) {
            TreeNode<TKey, TVal>* temp = pNode->pRight;
            delete pNode;
            pNode = temp;
            result = H_DEC;
        }
        else {
            result = RemoveMinimum(pNode->pLeft);
            if (result != H_OK) {
                result = BalanceLeft(pNode, DEL);
            }
        }
        return result;
    }

    int DeleteBalancedTree(TreeNode<TKey, TVal>*& pNode, TKey key) {
        int result = H_OK;
        if (pNode == nullptr) {
            return result;
        }

        if (key < pNode->rec.key) {
            int temp = DeleteBalancedTree(pNode->pLeft, key);
            if (temp != H_OK) {
                result = BalanceRight(pNode, DEL);
            }
        }
        else if (key > pNode->rec.key) {
            int temp = DeleteBalancedTree(pNode->pRight, key);
            if (temp != H_OK) {
                result = BalanceLeft(pNode, DEL);
            }
        }
        else {
            dataCount--;
            if (pNode->pLeft == nullptr || pNode->pRight == nullptr) {
                TreeNode<TKey, TVal>* temp = pNode->pLeft ? pNode->pLeft : pNode->pRight;
                if (temp == nullptr) {
                    delete pNode;
                    pNode = nullptr;
                    result = H_DEC;
                }
                else {
                    *pNode = *temp;
                    delete temp;
                    result = H_DEC;
                }
            }
            else {
                TreeNode<TKey, TVal>* minNode = FindMinimum(pNode->pRight);
                pNode->rec = minNode->rec;
                int temp = RemoveMinimum(pNode->pRight);
                if (temp != H_OK) {
                    result = BalanceLeft(pNode, DEL);
                }
            }
        }
        return result;
    }

public:
    BalancedTreeTable() : TreeTable<TKey, TVal>() {}

    void Insert(Record<TKey, TVal> rec) override {
        if (this->Find(rec.key)) {
            throw - 1;
        }
        InsertBalancedTreeTable(this->pRoot, rec);
    }

    void Delete(TKey key) override {
        if (this->pRoot == nullptr) {
            throw - 1;
        }
        if (!this->Find(key)) {
            throw - 1;
        }
        DeleteBalancedTree(this->pRoot, key);
    }
};