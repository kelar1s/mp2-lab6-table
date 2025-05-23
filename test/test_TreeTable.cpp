#include "gtest.h"
#include "../Table/TreeTable.h"

TEST(TreeTable, can_insert_element_find_it_and_it_works_correct) {
	TreeTable<int, int> tt;
	Record<int, int> rt(20, 20);
	ASSERT_NO_THROW(tt.Insert(rt));
	for (int i = 1; i < 20; i++) {
		ASSERT_NO_THROW(tt.Insert(Record<int, int>(i, i)));
	}
	for (int i = 20; i < 32; i++) {
		ASSERT_NO_THROW(tt.Insert(Record<int, int>(i, i)));
	}
	for (int i = 1; i < 32; i++) {
		EXPECT_EQ(tt.Find(i), true);
	}
}