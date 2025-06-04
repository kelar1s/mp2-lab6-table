#include "gtest.h"
#include "../Table/BalancedTreeTable.h"

TEST(BalancedTreeTable, can_insert_element_and_it_works_correct) {
	BalancedTreeTable<int, int> btt;
	Record<int, int> rt(20, 20);
	ASSERT_NO_THROW(btt.Insert(rt));
	for (int i = 0; i < 20; i++) {
		btt.Insert(Record<int, int>(i, i));
	}
	for (int i = 0; i <= 20; i++) {
		EXPECT_TRUE(btt.Find(i));
	}
}

TEST(BalancedTreeTable, cant_insert_element_to_existing_position) {
	BalancedTreeTable<int, int> btt;
	Record<int, int> rt(20, 20);
	btt.Insert(rt);
	int i;
	for (i = 15; i < 20; i++) {
		btt.Insert(Record<int, int>(i, i));
	}
	for (int i = 15; i < 21; i++) {
		ASSERT_ANY_THROW(btt.Insert(Record<int, int>(i, i)));
	}
}

TEST(BalancedTreeTable, can_find_element_and_it_works_correct) {
	BalancedTreeTable<int, int> btt;
	Record<int, int> rt(20, 20);
	btt.Insert(rt);
	int i;
	for (i = 1; i < 20; i++) {
		btt.Insert(Record<int, int>(i, i));
	}
	for (i = 21; i < 32; i++) {
		btt.Insert(Record<int, int>(i, i));
	}
	for (i = 1; i < 32; i++) {
		EXPECT_TRUE(btt.Find(i));
	}
}

TEST(BalancedTreeTable, cant_find_non_existent_element) {
	BalancedTreeTable<int, int> btt;
	Record<int, int> rt(20, 20);
	btt.Insert(rt);
	int i;
	for (i = 1; i < 20; i++) {
		btt.Insert(Record<int, int>(i, i));
	}
	for (i = 21; i < 25; i++) {
		EXPECT_FALSE(btt.Find(i));
	}
}

TEST(BalancedTreeTable, can_delete_element_and_it_works_correct) {
	BalancedTreeTable<int, int> btt;
	Record<int, int> rt(5, 5);
	btt.Insert(rt);
	for (int i = 0; i < 5; i++) {
		btt.Insert(Record<int, int>(i, i));
	}
	for (int i = 6; i < 10; i++) {
		btt.Insert(Record<int, int>(i, i));
	}

	for (int i = 0; i < 10; i += 2) {
		ASSERT_NO_THROW(btt.Delete(i));
	}

	for (int i = 0; i < 10; i += 2) {
		EXPECT_FALSE(btt.Find(i));
	}
	for (int i = 1; i < 10; i += 2) {
		EXPECT_TRUE(btt.Find(i));
	}
}

TEST(BalancedTreeTable, cant_delete_non_existent_element) {
	BalancedTreeTable<int, int> btt;
	Record<int, int> rt(5, 5);
	btt.Insert(rt);
	for (int i = 0; i < 5; i++) {
		btt.Insert(Record<int, int>(i, i));
	}
	for (int i = 6; i < 10; i++) {
		btt.Insert(Record<int, int>(i, i));
	}

	for (int i = 10; i < 15; i++) {
		ASSERT_ANY_THROW(btt.Delete(i));
	}
}

TEST(BalancedTreeTable, efficiency_when_inserting) {
	BalancedTreeTable<int, int> btt;
	for (int i = 0; i < 999; i++) {
		btt.Insert(Record<int, int>(i, i));
	}
	btt.ClearEff();
	btt.Insert(Record<int, int>(1000, 1000));
	EXPECT_EQ(btt.GetEff(), 11);
}

TEST(BalancedTreeTable, efficiency_when_deleting) {
	BalancedTreeTable<int, int> btt;

	for (int i = 0; i < 1000; i++) {
		btt.Insert(Record<int, int>(i, i));
	}
	btt.ClearEff();
	btt.Delete(500);
	EXPECT_EQ(btt.GetEff(), 10);
}
