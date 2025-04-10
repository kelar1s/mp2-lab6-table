#include "gtest.h"
#include "../Table/SortTable.h"
#include "../Table/ScanTable.h"

TEST(SortTable, can_insert_element_and_it_works_correct) {
	SortTable<int, int> st(10);
	Record<int, int> rec(0, 0);
	ASSERT_NO_THROW(st.Insert(rec));
	for (int i = 1; i < 4; i++) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	for (int i = 7; i > 3; i--) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	int i = 0;
	for (st.Reset(); !st.IsEnd() && i < 8; st.GoNext(), i++) {
		EXPECT_EQ(i, st.GetCurrKey());
		EXPECT_EQ(i, st.GetCurrVal());
	}
}

TEST(SortTable, cant_insert_element_in_full_sorttable) {
	SortTable<int, int> st(10);
	for (int i = 0; i < 10; i++) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	Record<int, int> rec(10, 10);
	ASSERT_ANY_THROW(st.Insert(rec));
}

TEST(SortTable, cant_insert_element_to_existing_position) {
	SortTable<int, int> st(10);
	for (int i = 0; i < 5; i++) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	Record<int, int> rec(4, 4);
	ASSERT_ANY_THROW(st.Insert(rec));
}

TEST(SortTable, find_existent_element_works_correct) {
	SortTable<int, int> st(10);
	for (int i = 0; i < 5; i++) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	for (int i = 0; i < 5; i++) {
		EXPECT_EQ(st.Find(i), true);
	}
}

TEST(SortTable, cant_find_non_existent_element) {
	SortTable<int, int> st(10);
	for (int i = 0; i < 5; i++) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	for (int i = 5; i < 10; i++) {
		EXPECT_EQ(st.Find(i), false);
	}
}


TEST(SortTable, can_delete_element_and_it_works_correct) {
	ScanTable<int, int> st(10);
	for (int i = 1; i < 10; i++) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	for (int i = 1; i % 2 == 0; i++) {
		ASSERT_NO_THROW(st.Delete(i));
	}
	int i = 1;
	for (st.Reset(); !st.IsEnd() && i % 2 == 1; st.GoNext(), i++) {
		EXPECT_EQ(i, st.GetCurrKey());
		EXPECT_EQ(i, st.GetCurrVal());
	}
}

TEST(SortTable, cant_delete_non_existent_element) {
	SortTable<int, int> st(10);
	for (int i = 1; i < 5; i++) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	ASSERT_ANY_THROW(st.Delete(6));
}

TEST(SortTable, can_create_copied_sorttable_using_quicksort_and_it_works_correct) {
	ScanTable<int, int> st(10);
	for (int i = 10; i > 0; i--) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	SortTable<int, int> stQuick(st, QuickSortType);
	int i = 1;
	for (stQuick.Reset(); !stQuick.IsEnd() && i <= 10; stQuick.GoNext(), i++) {
		EXPECT_EQ(i, stQuick.GetCurrKey());
		EXPECT_EQ(i, stQuick.GetCurrVal());
	}
}

TEST(SortTable, can_create_copied_sorttable_using_selectsort_and_it_works_correct) {
	ScanTable<int, int> st(10);
	for (int i = 10; i > 0; i--) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	SortTable<int, int> stQuick(st, SelectSortType);
	int i = 1;
	for (stQuick.Reset(); !stQuick.IsEnd() && i <= 10; stQuick.GoNext(), i++) {
		EXPECT_EQ(i, stQuick.GetCurrKey());
		EXPECT_EQ(i, stQuick.GetCurrVal());
	}
}

TEST(SortTable, can_create_copied_sorttable_using_mergesort_and_it_works_correct) {
	ScanTable<int, int> st(10);
	for (int i = 10; i > 0; i--) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	SortTable<int, int> stQuick(st, MergeSortType);
	int i = 1;
	for (stQuick.Reset(); !stQuick.IsEnd() && i <= 10; stQuick.GoNext(), i++) {
		EXPECT_EQ(i, stQuick.GetCurrKey());
		EXPECT_EQ(i, stQuick.GetCurrVal());
	}
}