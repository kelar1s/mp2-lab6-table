#include "ScanTable.h"
#include "Table.h"
#include "Record.h"
#include "SortTable.h"
#include "ArrayHashTable.h"
#include "ListHashTable.h"
#include "TreeTable.h"
#include <iostream>



int main() {
	/*ListHashTable<int, std::string> table(10);
	table.Insert(Record<int, std::string>(1, "Lesha Tsydenov"));
	table.Insert(Record<int, std::string>(11, "Namzhal-Dorzho Tsybikov"));
	table.Insert(Record<int, std::string>(2, "Namsarai Baltahinov"));
	table.Insert(Record<int, std::string>(3, "Dorzhi Zandakov"));
	table.Insert(Record<int, std::string>(6, "Bato Batuevich"));
	table.Insert(Record<int, std::string>(5, "Zhargal Shushkevich"));
	std::cout << "Table:" << std::endl;
	std::cout << table << std::endl;
	table.Delete(11);
	table.Delete(1);
	std::cout << "Table 2:" << std::endl;
	std::cout << table << std::endl;
	table.Clear();
	std::cout << "Table 3:" << std::endl;
	std::cout << table << std::endl;*/

	TreeTable<int, int> treetable;
	for (int i = 10; i < 15; i++) {
		treetable.Insert(Record<int, int>(i, i));
	}
	for (int i = 1; i < 5; i++) {
		treetable.Insert(Record<int, int>(i, i));
	}
	for (int i = 7; i < 10; i++) {
		treetable.Insert(Record<int, int>(i, i));
	}
	for (int i = 20; i < 26; i++) {
		treetable.Insert(Record<int, int>(i, i));
	}
	for (int i = 20; i < 22; i++) {
		treetable.Delete(i);
	}
	for (int i = 3; i < 5; i++) {
		treetable.Delete(i);
	}
	treetable.Insert(Record<int, int>(15, 15));
	for (int i = 0; i < 40; i++) {
		std::cout << i << "Exist: " << treetable.Find(i) << std::endl;
	}
	std::cout << "Tree structure:" << std::endl;
	treetable.PrintTree(std::cout);
	return 0;
}