#pragma once
#include "../Table/ArrayHashTable.h"
#include "../Table/ListHashTable.h"
#include "../Table/ScanTable.h"
#include "../Table/SortTable.h"
#include <vector>
#include <string>
using namespace std;

class Visual {
    vector<ScanTable<int, int>> scanTables;
    vector<SortTable<int, int>> sortTables;
    vector<ArrayHashTable<int, int>> arrayHashTables;

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
    }
};