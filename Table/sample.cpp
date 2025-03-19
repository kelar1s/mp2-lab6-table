#include "ScanTable.h"
#include "Table.h"
#include "Record.h"
#include "SortTable.h"


int main() {
	SortTable<int, std::string> table(10);
	table.Insert(Record<int, std::string>(1, "Lesha Tsydenov"));
	table.Insert(Record<int, std::string>(2, "Namsarai Baltahinov"));
	table.Insert(Record<int, std::string>(3, "Dorzhi Zandakov"));
	table.Insert(Record<int, std::string>(4, "Bato Batuevich"));
	table.Insert(Record<int, std::string>(5, "Zhargal Shushkevich"));
	table.Insert(Record<int, std::string>(8, "Ayuna Ledyasheva"));
	table.Delete(1);
	return 0;
}