#include "gtest/gtest.h"
#include "header.hpp"

// Тестирование конструкторов
TEST(NumberConstructor, Constructor) {
	Lab3::Number l1, l2("-a4b"), l3("523abf4"), l4(9153109301);
	ASSERT_EQ(0, l1.getLength());
	ASSERT_EQ(3, l2.getLength());
	ASSERT_EQ(7, l3.getLength());
	ASSERT_EQ(9, l4.getLength());
	ASSERT_STREQ("0", l1.getArray());
	ASSERT_STREQ("1a4b", l2.getArray());
	ASSERT_STREQ("0523abf4", l3.getArray());
	ASSERT_STREQ("0221915d35", l4.getArray());
}

TEST(NumberSum, Parameters) {
	Lab3::Number l1, l2("-1af45"), l3("-588e"), l4, l5, l6, l7, l8, l9, l10;
	l4 = l2 + l3, l5 = l2 - l3, l6 = l3 - l2, l7 = 2 + l2, l8 = l2 + 2, l9 = 2 - l2, l10 = l2 - 2;
	ASSERT_STREQ("1207d3", l4.getArray());
	ASSERT_STREQ("1156b7", l5.getArray());
	ASSERT_STREQ("0156b7", l6.getArray());
	ASSERT_STREQ("11af43", l7.getArray());
	ASSERT_STREQ("11af43", l8.getArray());
	ASSERT_STREQ("01af47", l9.getArray());
	ASSERT_STREQ("11af47", l10.getArray());
}

TEST(NumberMethods, Parameters) {
	Lab3::Number l1, l2("-1af45"), l3("-588e"), l4("-588e");
	ASSERT_FALSE(l2 > l3);
	ASSERT_TRUE(l1 > l2);
	ASSERT_TRUE(l3 == l4);
	ASSERT_FALSE(l2.isEven());
	ASSERT_TRUE(l3.isEven());
}


int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}