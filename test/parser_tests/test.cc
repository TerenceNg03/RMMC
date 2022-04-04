#include <gtest/gtest.h>
#include <string>
#include "driver.hh"


TEST(parser, import_test) {
	std::string filename = "cases/import.rmm";
	rmmc::Driver driver(filename);
	EXPECT_EQ(driver.failed(), false);
}

TEST(parser, let_test) {
	std::string filename = "cases/let.rmm";
	rmmc::Driver driver(filename);
	EXPECT_EQ(driver.failed(), false);
}

TEST(parser, expression_test) {
	std::string filename = "cases/expression.rmm";
	rmmc::Driver driver(filename);
	EXPECT_EQ(driver.failed(), false);
}

TEST(parser, syntax_error_test) {
	std::string filename = "cases/error.rmm";
	rmmc::Driver driver(filename);
	EXPECT_EQ(driver.failed(), true);
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
