#include "gtest.h"
#include "../Table/ScanTable.h"

TEST(ScanTable, can_insert_element_and_it_works_correct) {
	ScanTable<int, int> st(10);
	Record<int, int> rec(0, 0);
	ASSERT_NO_THROW(st.Insert(rec));
	for (int i = 1; i < 5; i++) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	int i = 0;
	for (st.Reset(); !st.IsEnd() && i < 5; st.GoNext(), i++) {
		EXPECT_EQ(i, st.GetCurrKey());
		EXPECT_EQ(i, st.GetCurrVal());
	}
}

TEST(ScanTable, cant_insert_element_in_full_scantable) {
	ScanTable<int, int> st(10);
	for (int i = 0; i < 10; i++) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	Record<int, int> rec(10, 10);
	ASSERT_ANY_THROW(st.Insert(rec));
}

TEST(ScanTable, cant_insert_element_to_existing_position) {
	ScanTable<int, int> st(10);
	for (int i = 0; i < 5; i++) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	Record<int, int> rec(4, 4);
	ASSERT_ANY_THROW(st.Insert(rec));
}

TEST(ScanTable, can_delete_element_and_it_works_correct) {
	ScanTable<int, int> st(10);
	for (int i = 5; i > 0; i--) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	ASSERT_NO_THROW(st.Delete(5)); 
	ASSERT_NO_THROW(st.Delete(4));
	int i = 1;
	for (st.Reset(); !st.IsEnd() && i < 4; st.GoNext(), i++) {
		EXPECT_EQ(i, st.GetCurrKey());
		EXPECT_EQ(i, st.GetCurrVal());
	}
}

TEST(ScanTable, cant_delete_non_existent_element) {
	ScanTable<int, int> st(10);
	for (int i = 1; i < 5; i++) {
		Record<int, int> rec(i, i);
		st.Insert(rec);
	}
	ASSERT_ANY_THROW(st.Delete(6));
}