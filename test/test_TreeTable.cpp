#include "gtest.h"
#include "../Table/TreeTable.h"

TEST(TreeTable, can_insert_element_and_it_works_correct) {
	TreeTable<int, int> tt;
	Record<int, int> rt(20, 20);
	ASSERT_NO_THROW(tt.Insert(rt));
	int i;
	for (i = 1; i < 20; i++) {
		ASSERT_NO_THROW(tt.Insert(Record<int, int>(i, i)));
	}
	for (i = 21; i < 32; i++) {
		ASSERT_NO_THROW(tt.Insert(Record<int, int>(i, i)));
	}
	for (i = 0, tt.Reset(); i < 32 && tt.IsEnd();tt.GoNext(), i++) {
		EXPECT_EQ(i, tt.GetCurr().key);
	}
}

TEST(TreeTable, cant_insert_element_to_existing_position) {
	TreeTable<int, int> tt;
	Record<int, int> rt(20, 20);
	tt.Insert(rt);
	int i;
	for (i = 15; i < 20; i++) {
		tt.Insert(Record<int, int>(i, i));
	}
	for (int i = 15; i < 21; i++) {
		ASSERT_ANY_THROW(tt.Insert(Record<int, int>(i, i)));
	}
}

TEST(TreeTable, can_find_element_and_it_works_correct) {
	TreeTable<int, int> tt;
	Record<int, int> rt(20, 20);
	tt.Insert(rt);
	int i;
	for (i = 1; i < 20; i++) {
		tt.Insert(Record<int, int>(i, i));
	}
	for (i = 21; i < 32; i++) {
		tt.Insert(Record<int, int>(i, i));
	}
	for (i = 1 ; i < 32; i++) {
		EXPECT_TRUE(tt.Find(i));
	}
}

TEST(TreeTable, cant_find_non_existent_element) {
	TreeTable<int, int> tt;
	Record<int, int> rt(20, 20);
	tt.Insert(rt);
	int i;
	for (i = 1; i < 20; i++) {
		tt.Insert(Record<int, int>(i, i));
	}
	for (i = 21; i < 25; i++) {
		EXPECT_FALSE(tt.Find(i));
	}
}

TEST(TreeTable, can_delete_element_and_it_works_correct) {
	TreeTable<int, int> tt;
	Record<int, int> rt(5, 5);
	tt.Insert(rt);
	for (int i = 0; i < 5; i++) {
		tt.Insert(Record<int, int>(i, i));
	}
	for (int i = 6; i < 10; i++) {
		tt.Insert(Record<int, int>(i, i));
	}
	for (int i = 0; i < 10; i += 2) {
		ASSERT_NO_THROW(tt.Delete(i));
	}
	for (int i = 0; i < 10; i += 2) {
		EXPECT_FALSE(tt.Find(i));
	}
	for (int i = 1; i < 10; i += 2) {
		EXPECT_TRUE(tt.Find(i));
	}
}

TEST(TreeTable, cant_delete_non_existent_element) {
	TreeTable<int, int> tt;
	Record<int, int> rt(5, 5);
	tt.Insert(rt);
	for (int i = 0; i < 5; i++) {
		tt.Insert(Record<int, int>(i, i));
	}
	for (int i = 6; i < 10; i++) {
		tt.Insert(Record<int, int>(i, i));
	}

	for (int i = 10; i < 15; i++) {
		ASSERT_ANY_THROW(tt.Delete(i));
	}
}
