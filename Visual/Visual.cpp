#include "Visual.h"
#include <chrono>
#include <thread>
#include <conio.h> // Для _kbhit()

Visual::Visual() {
    // Инициализация тестовых таблиц
    ScanTable<int, int> st(105); // Увеличиваем размер для 100 элементов
    st.Insert(Record<int, int>(1, 100));
    st.Insert(Record<int, int>(2, 200));
    scanTables.push_back(st);

    SortTable<int, int> sortt(105);
    sortt.Insert(Record<int, int>(3, 300));
    sortTables.push_back(sortt);

    ArrayHashTable<int, int> aht(105);
    aht.Insert(Record<int, int>(4, 400));
    arrayHashTables.push_back(aht);
}

void Visual::Run() {
    Update();
    char operation = 'b';
    while (operation != 'q') {
        if (_kbhit()) {
            operation = tolower(_getch());
        }
        else {
            this_thread::sleep_for(chrono::milliseconds(100));
            continue;
        }

        int tableType, tableNum, key, value;

        try {
            switch (operation) {
            case '1': // Вставка элемента
                cout << "\033[33m" << "Select table type (1-Scan, 2-Sort, 3-ArrayHash): " << "\033[0m";
                cin >> tableType;
                cout << "\033[33m" << "Enter table number: " << "\033[0m";
                cin >> tableNum;
                cout << "\033[33m" << "Enter key and value: " << "\033[0m";
                cin >> key >> value;

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
                default:
                    throw invalid_argument("Invalid table type");
                }
                operations_count++;
                Update("Insert successful!");
                break;

            case '2': // Удаление элемента
                cout << "\033[33m" << "Select table type: " << "\033[0m";
                cin >> tableType;
                cout << "\033[33m" << "Enter table number: " << "\033[0m";
                cin >> tableNum;
                cout << "\033[33m" << "Enter key to delete: " << "\033[0m";
                cin >> key;

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
                default:
                    throw invalid_argument("Invalid table type");
                }
                operations_count++;
                Update("Delete successful!");
                break;

            case '3': // Поиск элемента
                cout << "\033[33m" << "Select table type: " << "\033[0m";
                cin >> tableType;
                cout << "\033[33m" << "Enter table number: " << "\033[0m";
                cin >> tableNum;
                cout << "\033[33m" << "Enter key to find: " << "\033[0m";
                cin >> key;

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
                default:
                    throw invalid_argument("Invalid table type");
                }
                Update(found ? "Key found!" : "Key not found!");
                break;

            case '4': // Создать новую таблицу
                cout << "\033[33m" << "Select table type: " << "\033[0m";
                cin >> tableType;
                cout << "\033[33m" << "Enter table size: " << "\033[0m";
                cin >> value;

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
                default:
                    throw invalid_argument("Invalid table type");
                }
                Update("Table created!");
                break;

            case 'a': { // Автоматическое добавление элементов
                Clear();
                Update("Auto-adding elements 0-100 to all tables... (Press any key to stop)");

                for (int key = 0; key <= 100; key++) {
                    if (_kbhit()) {
                        _getch();
                        Update("Auto-adding stopped at key " + to_string(key));
                        break;
                    }

                    Record<int, int> rec(key, key * 10);

                    // Добавление во все таблицы
                    for (auto& table : scanTables) {
                        try { table.Insert(rec); operations_count++; }
                        catch (...) {}
                    }
                    for (auto& table : sortTables) {
                        try { table.Insert(rec); operations_count++; }
                        catch (...) {}
                    }
                    for (auto& table : arrayHashTables) {
                        try { table.Insert(rec); operations_count++; }
                        catch (...) {}
                    }

                    Update("Auto-adding... " + to_string(key) + "/100");
                    this_thread::sleep_for(chrono::seconds(1));
                }
                Update("Auto-adding completed!");
                break;
            }

            case 'd': { // Автоматическое удаление элементов
            Update("Auto-deleting elements from all tables... (Press any key to stop)");
            
            bool elementsExist = true;
            while (elementsExist) {
                if (_kbhit()) {
                    _getch();
                    Update("Auto-deleting stopped");
                    break;
                }

                elementsExist = false;
                
                // Удаляем из всех таблиц
                for (auto& table : scanTables) {
                    if (!table.IsEmpty()) {
                        table.Reset();
                        table.Delete(table.GetCurrKey());
                        operations_count++;
                        elementsExist = true;
                    }
                }
                for (auto& table : sortTables) {
                    if (!table.IsEmpty()) {
                        table.Reset();
                        table.Delete(table.GetCurrKey());
                        operations_count++;
                        elementsExist = true;
                    }
                }
                for (auto& table : arrayHashTables) {
                    if (!table.IsEmpty()) {
                        table.Reset();
                        table.Delete(table.GetCurrKey());
                        operations_count++;
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
            default:
                if (operation != 'q') {
                    Update("Invalid operation.");
                }
                break;
            }
        }
        catch (const exception& e) {
            Update("Error: " + string(e.what()));
        }
        catch (...) {
            Update("Unknown error occurred!");
        }
    }
    Update("Exiting...");
    this_thread::sleep_for(chrono::seconds(1));
    exit(0);
}

void Visual::Update(string message) {
    system("cls");
    cout << "\033[33m" << "=== Tables Manager (" << operations_count << " operations) ===" << "\033[0m" << endl << endl;

    // Вывод ScanTables
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

    // Вывод SortTables
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

    // Вывод ArrayHashTables
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

    // Меню операций
    cout << endl << "Operations:" << endl
        << "  1: Insert element" << endl
        << "  2: Delete element" << endl
        << "  3: Find element" << endl
        << "  4: Create new table" << endl
        << "  a: Auto-add 0-100 to all tables" << endl
        << "  d: Auto-delete all elements" << endl
        << "  l: Clear all tables" << endl
        << "  q: Quit" << endl << endl;

    if (!message.empty()) {
        cout << "\033[31m" << message << "\033[0m" << endl;
    }
}