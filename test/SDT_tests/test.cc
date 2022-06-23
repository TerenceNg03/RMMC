#include <gtest/gtest.h>
#include "rmm_utility.hh"
#include <iostream>
using namespace rmmc;
using namespace std;

TEST(utility, string_process){
	EXPECT_EQ(str_unquote("'as'"), "as");
	EXPECT_EQ(str_unquote("a"), "a");
	EXPECT_EQ(str_unquote("\"\""),"");

	EXPECT_EQ(str_unescape("\\a12yu\\t\\rmmm\\f\\q\\\\\\v"), "\a12yu\t\rmmm\fq\\\v");
	EXPECT_EQ(str_unescape(""), "");
	EXPECT_EQ(str_unescape("31\\01267"), "31\01267");
	EXPECT_EQ(str_unescape("31\\582\'67"), "31\582'67");
	EXPECT_EQ(str_unescape("\\5"), "\5");
	EXPECT_EQ(str_unescape("\\042"), "\042");
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
