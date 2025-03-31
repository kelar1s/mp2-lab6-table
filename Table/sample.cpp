#include "ScanTable.h"
#include "Table.h"
#include "Record.h"
#include "SortTable.h"
#include <iostream>



int main() {
	ScanTable<int, std::string> table(10);
	table.Insert(Record<int, std::string>(9, "Lesha Tsydenov"));
	table.Insert(Record<int, std::string>(2, "Namsarai Baltahinov"));
	table.Insert(Record<int, std::string>(3, "Dorzhi Zandakov"));
	table.Insert(Record<int, std::string>(6, "Bato Batuevich"));
	table.Insert(Record<int, std::string>(5, "Zhargal Shushkevich"));

	std::cout << "ScanTable before sort: " << std::endl;
	std::cout << table << std::endl;
	table.QuickSort();
	std::cout << "ScanTable after sort: " << std::endl;
	std::cout << table << std::endl;

	SortTable<int, std::string> table1(10);
	table1.Insert(Record<int, std::string>(9, "Lesha Tsydenov"));
	table1.Insert(Record<int, std::string>(2, "Namsarai Baltahinov"));
	table1.Insert(Record<int, std::string>(3, "Dorzhi Zandakov"));
	table1.Insert(Record<int, std::string>(6, "Bato Batuevich"));
	table1.Insert(Record<int, std::string>(5, "Zhargal Shushkevich"));
	table1.Insert(Record<int, std::string>(1, "Ayuna Ledyasheva"));
	std::cout << "SortTable:" << std::endl;
	std::cout << table1 << std::endl;
	return 0;
}