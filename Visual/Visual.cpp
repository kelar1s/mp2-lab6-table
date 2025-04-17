#include "Visual.h"
#include <chrono>
#include <thread>
#include <conio.h>

Visual::Visual() {
    ScanTable<int, int> st(101);
    st.Insert(Record<int, int>(1, 10));
    st.Insert(Record<int, int>(2, 20));
    scanTables.push_back(st);

    SortTable<int, int> sortt(101);
    sortt.Insert(Record<int, int>(3, 30));
    sortTables.push_back(sortt);

    ArrayHashTable<int, int> aht(101);
    aht.Insert(Record<int, int>(4, 40));
    arrayHashTables.push_back(aht);

    ListHashTable<int, int> lht(101);
    lht.Insert(Record<int, int>(5, 50));
    listHashTables.push_back(lht);
}

void Visual::Run() {
    Update();
    char operation = 'b';
    while (operation != 'q') {
        if (_kbhit()) {
            operation = tolower(_getch());
        }
        else {
            this_thread::sleep_for(chrono::milliseconds(500));
            continue;
        }

        int tableType, tableNum, key, value;
        bool tableExists;

        try {
            switch (operation) {
            case '1': // Вставка элемента
                cout << "\033[33m" << "Select table type (1-Scan, 2-Sort, 3-ArrayHash, 4-ListHash): " << "\033[0m";
                cin >> tableType;
                if (tableType < 1 || tableType > 4) {
                    Update("The table type must be 1-Scan or 2-Sort or 3-ArrayHash or 4-ListHash!");
                    break;
                }
                cout << "\033[33m" << "Enter table number: " << "\033[0m";
                cin >> tableNum;
                tableExists = tableNum < 0;
                switch (tableType) {
                case 1:
                    tableExists = tableNum < scanTables.size();
                    if (!tableExists) Update("There is no ScanTable with this number!");
                    break;
                case 2:
                    tableExists = tableNum < sortTables.size();
                    if (!tableExists) Update("There is no SortTable with this number!");
                    break;
                case 3:
                    tableExists = tableNum < arrayHashTables.size();
                    if (!tableExists) Update("There is no ArrayHashTable with this number!");
                    break;
                case 4:
                    tableExists = tableNum < listHashTables.size();
                    if (!tableExists) Update("There is no ListHashTable with this number!");
                    break;
                }
                if (!tableExists) {
                    break;
                }
                cout << "\033[33m" << "Enter key and value: " << "\033[0m";
                cin >> key >> value;
                if (key < 0) {
                    Update("The key must be a positive number!");
                    break;
                }
                switch (tableType) {
                case 1:
                    scanTables[tableNum].Insert(Record<int, int>(key, value));
                    break;
                case 2:
                    sortTables[tableNum].Insert(Record<int, int>(key, value));
                    break;
                case 3:
                    arrayHashTables[tableNum].Insert(Record<int, int>(key, value));
                    break;
                case 4:
                    listHashTables[tableNum].Insert(Record<int, int>(key, value));
                    break;
                default:
                    throw -1;
                }
                Update("Insert successful!");
                break;

            case '2': // Удаление элемента
                cout << "\033[33m" << "Select table type (1-Scan, 2-Sort, 3-ArrayHash, 4-ListHash): " << "\033[0m";
                cin >> tableType;
                if (tableType < 1 || tableType > 4) {
                    Update("The table type must be 1-Scan or 2-Sort or 3-ArrayHash or 4-ListHash!");
                    break;
                }
                cout << "\033[33m" << "Enter table number: " << "\033[0m";
                cin >> tableNum;
                tableExists = tableNum < 0;
                switch (tableType) {
                case 1:
                    tableExists = tableNum < scanTables.size();
                    if (!tableExists) Update("There is no ScanTable with this number!");
                    break;
                case 2:
                    tableExists = tableNum < sortTables.size();
                    if (!tableExists) Update("There is no SortTable with this number!");
                    break;
                case 3:
                    tableExists = tableNum < arrayHashTables.size();
                    if (!tableExists) Update("There is no ArrayHashTable with this number!");
                    break;
                case 4:
                    tableExists = tableNum < listHashTables.size();
                    if (!tableExists) Update("There is no ListHashTable with this number!");
                    break;
                }
                if (!tableExists) {
                    break;
                }
                cout << "\033[33m" << "Enter key: " << "\033[0m";
                cin >> key;
                if (key < 0) {
                    Update("The key must be a positive number!");
                    break;
                }
                switch (tableType) {
                case 1:
                    scanTables[tableNum].Delete(key);
                    break;
                case 2:
                    sortTables[tableNum].Delete(key);
                    break;
                case 3:
                    arrayHashTables[tableNum].Delete(key);
                    break;
                case 4:
                    listHashTables[tableNum].Delete(key);
                    break;
                default:
                    throw -1;
                }
                Update("Delete successful!");
                break;

            case '3': // Поиск элемента
                cout << "\033[33m" << "Select table type (1-Scan, 2-Sort, 3-ArrayHash, 4-ListHash): " << "\033[0m";
                cin >> tableType;
                if (tableType < 1 || tableType > 4) {
                    Update("The table type must be 1-Scan or 2-Sort or 3-ArrayHash or 4-ListHash!");
                    break;
                }
                cout << "\033[33m" << "Enter table number: " << "\033[0m";
                cin >> tableNum;
                tableExists = tableNum < 0;
                switch (tableType) {
                case 1:
                    tableExists = tableNum < scanTables.size();
                    if (!tableExists) Update("There is no ScanTable with this number!");
                    break;
                case 2:
                    tableExists = tableNum < sortTables.size();
                    if (!tableExists) Update("There is no SortTable with this number!");
                    break;
                case 3:
                    tableExists = tableNum < arrayHashTables.size();
                    if (!tableExists) Update("There is no ArrayHashTable with this number!");
                    break;
                case 4:
                    tableExists = tableNum < listHashTables.size();
                    if (!tableExists) Update("There is no ListHashTable with this number!");
                    break;
                }
                if (!tableExists) {
                    break;
                }
                cout << "\033[33m" << "Enter key to find: " << "\033[0m";
                cin >> key;
                if (key < 0) {
                    Update("The key must be a positive number!");
                    break;
                }
                bool found;
                switch (tableType) {
                case 1:
                    found = scanTables[tableNum].Find(key);
                    break;
                case 2:
                    found = sortTables[tableNum].Find(key);
                    break;
                case 3:
                    found = arrayHashTables[tableNum].Find(key);
                    break;
                case 4:
                    found = listHashTables[tableNum].Find(key);
                    break;
                default:
                    throw -1;
                }
                Update(found ? "Key found!" : "Key not found!");
                break;

            case '4': // Создать новую таблицу
                cout << "\033[33m" << "Select table type (1-Scan, 2-Sort, 3-ArrayHash, 4-ListHash): " << "\033[0m";
                cin >> tableType;
                if (tableType < 1 || tableType > 4) {
                    Update("Table type has to be 1-Scan or 2-Sort or 3-ArrayHash or 4-ListHash");
                    break;
                }
                cout << "\033[33m" << "Enter table size: " << "\033[0m";
                cin >> value;
                if (value < 0) {
                    Update("The size must be a positive number!");
                    break;
                }
                switch (tableType) {
                case 1:
                    scanTables.push_back(ScanTable<int, int>(value));
                    break;
                case 2:
                    sortTables.push_back(SortTable<int, int>(value));
                    break;
                case 3:
                    arrayHashTables.push_back(ArrayHashTable<int, int>(value));
                    break;
                case 4:
                    listHashTables.push_back(ListHashTable<int, int>(value));
                    break;
                default:
                    throw -1;
                }
                Update("Table created!");
                break;
            case 'f':
                int cnt;
                Update("Enter number of elements to add: ");
                cin >> cnt;
                if (cnt < 0) {
                    Update("The count must be a positive number!");
                    break;
                }
                Update("Adding " + to_string(cnt) + " elements to all tables... (Press any key to stop)");
                for (int i = 0; i < cnt; i++) {
                    if (_kbhit()) {
                        _getch();
                        break;
                    }
                    int key = i;
                    int value = key + 1;
                    Record<int, int> rec(key, value);
                    for (ScanTable<int, int>& table : scanTables) {
                        try { table.Insert(rec); }
                        catch (...) {}
                    }
                    for (SortTable<int, int>& table : sortTables) {
                        try { table.Insert(rec); }
                        catch (...) {}
                    }
                    for (ArrayHashTable<int, int>& table : arrayHashTables) {
                        try { table.Insert(rec); }
                        catch (...) {}
                    }
                    for (ListHashTable<int, int>& table : listHashTables) {
                        try { table.Insert(rec); }
                        catch (...) {}
                    }
                    Update("Adding... " + to_string(i) + "/" + to_string(cnt));
                    this_thread::sleep_for(chrono::milliseconds(500));
                }

                Update("Adding completed!");
                break;

            case 'a': { // Добавление случайных элементов
                int count;
                Update("Enter number of random elements to add: ");
                cin >> count;
                if (count < 0) {
                    Update("The count must be a positive number!");
                    break;
                }
                Update("Adding " + to_string(count) + " random elements to all tables... (Press any key to stop)");
                srand(static_cast<unsigned int>(time(nullptr)));
                for (int i = 0; i < count; i++) {
                    if (_kbhit()) {
                        _getch();
                        break;
                    }
                    int key = rand() % (2 * count); 
                    int value = key + 1; 
                    Record<int, int> rec(key, value);
                    for (ScanTable<int, int>& table : scanTables) {
                        try { table.Insert(rec); }
                        catch (...) {}
                    }
                    for (SortTable<int, int>& table : sortTables) {
                        try { table.Insert(rec); }
                        catch (...) {}
                    }
                    for (ArrayHashTable<int, int>& table : arrayHashTables) {
                        try { table.Insert(rec); }
                        catch (...) {}
                    }
                    for (ListHashTable<int, int>& table : listHashTables) {
                        try { table.Insert(rec); }
                        catch (...) {}
                    }
                    Update("Adding... " + to_string(i) + "/" + to_string(count));
                    this_thread::sleep_for(chrono::seconds(1));
                }

                Update("Adding completed!");
                break;
            }

            case 'd': { // Удаление элементов
            Update("Auto-deleting elements from all tables! (Press any key to stop)");
            
            bool elementsExist = true;
            while (elementsExist) {
                if (_kbhit()) {
                    _getch();
                    Update("Auto-deleting stopped!");
                    break;
                }

                elementsExist = false;
                
                // Удаляем из всех таблиц
                for (ScanTable<int, int>& table : scanTables) {
                    if (!table.IsEmpty()) {
                        table.Reset();
                        table.Delete(table.GetCurrKey());
                        elementsExist = true;
                    }
                }
                for (SortTable<int, int>& table : sortTables) {
                    if (!table.IsEmpty()) {
                        table.Reset();
                        table.Delete(table.GetCurrKey());
                        elementsExist = true;
                    }
                }
                for (ArrayHashTable<int, int>& table : arrayHashTables) {
                    if (!table.IsEmpty()) {
                        table.Reset();
                        table.Delete(table.GetCurrKey());
                        elementsExist = true;
                    }
                }
                for (ListHashTable<int, int>& table : listHashTables) {
                    if (!table.IsEmpty()) {
                        table.Reset();
                        table.Delete(table.GetCurrKey());
                        elementsExist = true;
                    }
                }
                Update("Auto-deleting...");
                this_thread::sleep_for(chrono::seconds(1));
            }
            Update("Auto-deleting completed!");
            break;
            }

            case 'l':
                Clear();
                Update("All tables cleared!");
                break;
            case 'e':
                ClearAllEff();
                Update("Eff in all tables cleared!");
                break;
            default:
                if (operation != 'q') {
                    Update("Invalid operation.");
                }
                break;
            }
        }
        catch (...) {
            Update("Unknown error!");
        }
    }
    Update("Exiting...");
    this_thread::sleep_for(chrono::milliseconds(1000));
    exit(0);
}

void Visual::Update(string message) {
    system("cls");
    cout << "\033[33m" << "=== Tables Manager ===" << "\033[0m" << endl << endl;
    
    if (!scanTables.empty()) {
        cout << "Scan Tables:" << endl;
        for (size_t i = 0; i < scanTables.size(); i++) {
            cout << "  [" << i << "] (Eff: " << scanTables[i].GetEff() << "): ";
            for (scanTables[i].Reset(); !scanTables[i].IsEnd(); scanTables[i].GoNext()) {
                cout << scanTables[i].GetCurrKey() << ":" << scanTables[i].GetCurrVal() << " ";
            }
            cout << endl;
        }
    }
    if (!sortTables.empty()) {
        cout << endl << "Sort Tables:" << endl;
        for (size_t i = 0; i < sortTables.size(); i++) {
            cout << "  [" << i << "] (Eff: " << sortTables[i].GetEff() << "): ";
            for (sortTables[i].Reset(); !sortTables[i].IsEnd(); sortTables[i].GoNext()) {
                cout << sortTables[i].GetCurrKey() << ":" << sortTables[i].GetCurrVal() << " ";
            }
            cout << endl;
        }
    }
    if (!arrayHashTables.empty()) {
        cout << endl << "Array Hash Tables:" << endl;
        for (size_t i = 0; i < arrayHashTables.size(); i++) {
            cout << "  [" << i << "] (Eff: " << arrayHashTables[i].GetEff() << "): ";
            for (arrayHashTables[i].Reset(); !arrayHashTables[i].IsEnd(); arrayHashTables[i].GoNext()) {
                cout << arrayHashTables[i].GetCurrKey() << ":" << arrayHashTables[i].GetCurrVal() << " ";
            }
            cout << endl;
        }
    }
    if (!listHashTables.empty()) {
        cout << endl << "List Hash Tables:" << endl;
        for (size_t i = 0; i < listHashTables.size(); i++) {
            cout << "  [" << i << "] (Eff: " << listHashTables[i].GetEff() << "): ";
            for (listHashTables[i].Reset(); !listHashTables[i].IsEnd(); listHashTables[i].GoNext()) {
                cout << listHashTables[i].GetCurrKey() << ":" << listHashTables[i].GetCurrVal() << " ";
            }
            cout << endl;
        }
    }

    cout << endl << "Operations:" << endl
        << "  1: Insert element" << endl
        << "  2: Delete element" << endl
        << "  3: Find element" << endl
        << "  4: Create new table" << endl
        << "  a: Auto-add random elements to all tables" << endl
        << "  f: Auto-add elements from 0 to N to all tables" << endl
        << "  d: Auto-delete all elements" << endl
        << "  l: Clear all tables" << endl
        << "  q: Quit" << endl << endl;
    if (!message.empty()) {
        cout << "\033[31m" << message << "\033[0m" << endl;
    }
}