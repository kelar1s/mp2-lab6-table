#include "ScanTable.h"
#include "Table.h"
#include "Record.h"
#include "SortTable.h"
#include "ArrayHashTable.h"
#include "ListHashTable.h"
#include "TreeTable.h"
#include "BalancedTreeTable.h"
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

	/*BalancedTreeTable<int, int> btt;
	
	btt.Insert(Record<int, int>(15, 15));
	for (int i = 0; i < 15; i++) {
		btt.Insert(Record<int, int>(i, i));
	}
	for (int i = 16; i < 30; i++) {
		btt.Insert(Record<int, int>(i, i));
	}
	for (btt.Reset(); !btt.IsEnd(); btt.GoNext()) {
		std::cout << btt.GetCurrKey() << ":" << btt.GetCurrVal() << std::endl;
	}

	std::cout << std::endl;
	std::cout << "Tree structure:" << std::endl;
	btt.PrintTree(std::cout);

	std::cout << std::endl << "After delete pRoot" << std::endl;

	btt.Delete(15);
	for (btt.Reset(); !btt.IsEnd(); btt.GoNext()) {
		std::cout << btt.GetCurrKey() << ":" << btt.GetCurrVal() << std::endl;
	}

	std::cout << "Tree structure after delete pRoot:" << std::endl;
	btt.PrintTree(std::cout);*/

	BalancedTreeTable<int, int> btt;
	Record<int, int> rt(20, 20);
	btt.Insert(rt);
	for (int i = 0; i < 20; i++) {
		btt.Insert(Record<int, int>(i, i));
	}
	for (int i = 0; i <= 20; i++) {
		std::cout << "Found" << i << ": " << btt.Find(i) << std::endl;
	}
	return 0;
}