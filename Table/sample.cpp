#include "ScanTable.h"
#include "Table.h"
#include "Record.h"


int main() {
	ScanTable<int, std::string> table(10);
	table.Insert(Record<int, std::string>(1, "Tsydenov"));
	table.Insert(Record<int, std::string>(2, "Namsarai"));
	table.Insert(Record<int, std::string>(3, "Dorzhi Zandakov"));
	table.Insert(Record<int, std::string>(4, "Bato"));
	table.Insert(Record<int, std::string>(5, "Zhargal"));
	table.Insert(Record<int, std::string>(8, "Ayuna"));
	for (int i = 0; i < 10; i += 2) {
		if (table.Find(i)) {
			std::cout << i << " exists in the table" << std::endl;
		}
		else {
			std::cout << i << " does not exist in the table" << std::endl;
		}
	}
	return 0;
}