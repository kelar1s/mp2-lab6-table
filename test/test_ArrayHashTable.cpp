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

TEST(ArrayHashTable, can_delete_element_and_it_works_correct) {
	ArrayHashTable<int, int> aht(10);
	for (int i = 1; i < 10; i++) {
		Record<int, int> rec(i, i);
		aht.Insert(rec);
	}
	for (int i = 1; i % 2 == 0; i++) {
		ASSERT_NO_THROW(aht.Delete(i));
	}
	int i = 1;
	for (aht.Reset(); !aht.IsEnd() && i % 2 == 1; aht.GoNext(), i++) {
		EXPECT_EQ(aht.Find(i), true);
		EXPECT_EQ(aht.Find(i), true);
	}
	i = 1;
	for (aht.Reset(); !aht.IsEnd() && i % 2 == 0; aht.GoNext(), i++) {
		EXPECT_EQ(aht.Find(i), false);
		EXPECT_EQ(aht.Find(i), false);
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