#include "ScanTable.h"
#include "Table.h"
#include "Record.h"
#include "SortTable.h"
#include "ArrayHashTable.h"
#include "ListHashTable.h"
#include <iostream>



int main() {
	SortTable<int, std::string> table(10);
	table.Insert(Record<int, std::string>(1, "Lesha Tsydenov"));
	table.Insert(Record<int, std::string>(11, "Namzhal-Dorzho Tsybikov"));
	//table.Insert(Record<int, std::string>(2, "Namsarai Baltahinov"));
	//table.Insert(Record<int, std::string>(3, "Dorzhi Zandakov"));
	//table.Insert(Record<int, std::string>(6, "Bato Batuevich"));
	//table.Insert(Record<int, std::string>(5, "Zhargal Shushkevich"));
	std::cout << "Table:" << std::endl;
	std::cout << table << std::endl;
	return 0;
}