#pragma once
#include "Record.h"

const int BAL_OK = 0; const int BAL_LEFT = -1; const int BAL_RIGHT = 1;

template <typename TKey, typename TVal>
struct TreeNode {
	Record<TKey, TVal> rec;
	TreeNode* pLeft = nullptr;
	TreeNode* pRight = nullptr;
	int bal = BAL_OK; // ѕоказатель отвечающий за балансировку
public:
	TreeNode(): rec() {}
	TreeNode(TKey key, TVal val) : rec(key, val) {};

	bool operator==(const TreeNode<TKey, TVal>& oth) {
		return rec.key == oth.rec->key;
	}
};