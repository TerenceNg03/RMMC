#include <gtest/gtest.h>
#include <string>
#include "driver.hh"


TEST(parser, import_test) {
	rmmc::Driver driver;
	std::string filename = "cases/import.rmm";
	int result = driver.parse_file(filename);
	EXPECT_EQ(result, 0);
}

TEST(parser, let) {
	rmmc::Driver driver;
	std::string filename = "cases/let.rmm";
	int result = driver.parse_file(filename);
	EXPECT_EQ(result, 0);
}

TEST(parser, expression) {
	rmmc::Driver driver;
	std::string filename = "cases/expression.rmm";
	int result = driver.parse_file(filename);
	EXPECT_EQ(result, 0);
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
