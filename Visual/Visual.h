#pragma once
#include "../Table/ArrayHashTable.h"
#include "../Table/ListHashTable.h"
#include "../Table/ScanTable.h"
#include "../Table/SortTable.h"
#include "../Table/TreeTable.h"
#include "../Table/BalancedTreeTable.h"
#include <vector>
#include <string>
using namespace std;

class Visual {
    vector<ScanTable<int, int>> scanTables;
    vector<SortTable<int, int>> sortTables;
    vector<ArrayHashTable<int, int>> arrayHashTables;
    vector<ListHashTable<int, int>> listHashTables;
    TreeTable<int, int> treeTable;

public:
    Visual();
    void Run();
    void Update(string message = "");

    void Clear() {
        for (ScanTable<int, int>& table : scanTables) {
            table.Clear();
        }
        for (SortTable<int, int>& table : sortTables) {
            table.Clear();
        }
        for (ArrayHashTable<int, int>& table : arrayHashTables) {
            table.Clear();
        }
        for (ListHashTable<int, int>& table : listHashTables) {
            table.Clear();
        }
        treeTable.Clear();
    }
    void ClearAllEff() {
        for (ScanTable<int, int>& table : scanTables) {
            table.ClearEff();
        }
        for (SortTable<int, int>& table : sortTables) {
            table.ClearEff();
        }
        for (ArrayHashTable<int, int>& table : arrayHashTables) {
            table.ClearEff();
        }
        for (ListHashTable<int, int>& table : listHashTables) {
            table.ClearEff();
        }
        treeTable.ClearEff();
    }
};