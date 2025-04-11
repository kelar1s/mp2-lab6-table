#include "gtest.h"
#include "../Table/ListHashTable.h"

TEST(ListHashTable, can_insert_element_and_it_works_correct) {
	ListHashTable<int, int> lht(10);
	for (int i = 1; i < 122; i += 10) {
		Record<int, int> rec(i, i);
		ASSERT_NO_THROW(lht.Insert(rec));
	}
	for (int i = 1; i < 122; i += 10) {
		EXPECT_EQ(lht.Find(i), true);
	}
	for (int i = 125; i < 140; i++) {
		Record<int, int> rec(i, i);
		ASSERT_NO_THROW(lht.Insert(rec));
	}
	for (int i = 125; i < 140; i++) {
		EXPECT_EQ(lht.Find(i), true);
	}
}

TEST(ListHashTable, cant_insert_element_to_existing_position) {
	ListHashTable<int, int> lht(10);
	for (int i = 0; i < 10; i++) {
		Record<int, int> rec(i, i);
		lht.Insert(rec);
	}
	Record<int, int> rec(5, 5);
	ASSERT_ANY_THROW(lht.Insert(rec));
}

TEST(ListHashTable, find_existent_element_works_correct) {
	ListHashTable<int, int> lht(10);
	for (int i = 1; i < 122; i += 10) {
		Record<int, int> rec(i, i);
		lht.Insert(rec);
	}
	for (int i = 1; i < 121; i += 10) {
		EXPECT_EQ(lht.Find(i), true);
	}
	for (int i = 200; i < 220; i++) {
		Record<int, int> rec(i, i);
		lht.Insert(rec);
	}
	for (int i = 200; i < 220; i++) {
		EXPECT_EQ(lht.Find(i), true);
	}
}

TEST(ListHashTable, cant_find_non_existent_element) {
	ListHashTable<int, int> lht(10);
	for (int i = 0; i < 5; i++) {
		Record<int, int> rec(i, i);
		lht.Insert(rec);
	}
	for (int i = 5; i < 10; i++) {
		EXPECT_EQ(lht.Find(i), false);
	}
}

TEST(ListHashTable, can_delete_element_and_it_works_correct) {
	ListHashTable<int, int> lht(10);
	for (int i = 1; i < 10; i++) {
		Record<int, int> rec(i, i);
		lht.Insert(rec);
	}
	for (int i = 1; i % 2 == 0; i++) {
		ASSERT_NO_THROW(lht.Delete(i));
	}
	int i = 1;
	for (lht.Reset(); !lht.IsEnd() && i % 2 == 1; lht.GoNext(), i++) {
		EXPECT_EQ(lht.Find(i), true);
		EXPECT_EQ(lht.Find(i), true);
	}
	i = 1;
	for (lht.Reset(); !lht.IsEnd() && i % 2 == 0; lht.GoNext(), i++) {
		EXPECT_EQ(lht.Find(i), false);
		EXPECT_EQ(lht.Find(i), false);
	}
}

TEST(ListHashTable, cant_delete_non_existent_element) {
	ListHashTable<int, int> lht(10);
	for (int i = 1; i < 5; i++) {
		Record<int, int> rec(i, i);
		lht.Insert(rec);
	}
	ASSERT_ANY_THROW(lht.Delete(6));
}