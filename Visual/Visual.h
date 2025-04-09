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
    int operations_count = 0;

public:
    Visual();
    void Run();
    void Update(string message = "");

    void Clear() {
        for (auto& table : scanTables) {
            while (!table.IsEmpty()) {
                table.Reset();
                table.Delete(table.GetCurrKey());
            }
            table.ClearEff(); 
        }

        for (auto& table : sortTables) {
            while (!table.IsEmpty()) {
                table.Reset();
                table.Delete(table.GetCurrKey());
            }
            table.ClearEff();
        }

        for (auto& table : arrayHashTables) {
            while (!table.IsEmpty()) {
                table.Reset();
                table.Delete(table.GetCurrKey());
            }
            table.ClearEff();
        }
        operations_count = 0;
    }
};