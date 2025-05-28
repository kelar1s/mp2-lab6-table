#include "gtest.h"
#include "../Table/ArrayHashTable.h"

TEST(ArrayHashTable, can_insert_element_and_it_works_correct) {
	ArrayHashTable<int, int> aht(10);
	for (int i = 1; i < 32; i += 10) {
		Record<int, int> rec(i, i);
		ASSERT_NO_THROW(aht.Insert(rec));
	}
	for (int i = 1; i < 32; i += 10) {
		EXPECT_EQ(aht.Find(i), true);
	}
}

TEST(ArrayHashTable, cant_insert_element_in_full_ArrayHashTable) {
	ArrayHashTable<int, int> aht(10);
	for (int i = 0; i < 10; i ++) {
		Record<int, int> rec(i, i);
		aht.Insert(rec);
	}
	Record<int, int> rec(10, 10);
	ASSERT_ANY_THROW(aht.Insert(rec));
}

TEST(ArrayHashTable, cant_insert_element_to_existing_position) {
	ArrayHashTable<int, int> aht(10);
	for (int i = 0; i < 10; i++) {
		Record<int, int> rec(i, i);
		aht.Insert(rec);
	}
	Record<int, int> rec(5, 5);
	ASSERT_ANY_THROW(aht.Insert(rec));
}

TEST(ArrayHashTable, find_existent_element_works_correct) {
	ArrayHashTable<int, int> st(10);
	for (int i = 0; i < 5; i++) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	for (int i = 0; i < 5; i++) {
		EXPECT_EQ(st.Find(i), true);
	}
}

TEST(ArrayHashTable, cant_find_non_existent_element) {
	ArrayHashTable<int, int> st(10);
	for (int i = 0; i < 5; i++) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	for (int i = 5; i < 10; i++) {
		EXPECT_EQ(st.Find(i), false);
	}
}

TEST(ArrayHashTable, can_delete_element_and_it_works_correct) {
	ArrayHashTable<int, int> aht(10);
	for (int i = 0; i < 10; i++) {
		Record<int, int> rec(i, i);
		aht.Insert(rec);
	}
	for (int i = 0; i < 10; i += 2) {
		ASSERT_NO_THROW(aht.Delete(i));
	}
	for (int i = 1; i < 10; i += 2) {
		EXPECT_TRUE(aht.Find(i));
	}
	for (int i = 0; i < 10; i += 2) {
		EXPECT_FALSE(aht.Find(i));
	}
}

TEST(ArrayHashTable, cant_delete_non_existent_element) {
	ArrayHashTable<int, int> aht(10);
	for (int i = 1; i < 5; i++) {
		Record<int, int> rec(i, i);
		aht.Insert(rec);
	}
	ASSERT_ANY_THROW(aht.Delete(6));
}