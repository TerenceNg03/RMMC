#include <gtest/gtest.h>
#include <regex>
#include <string>
#include "driver.hh"


TEST(parser, import_test) {
	std::string filename = "cases/import.rmm";
	rmmc::Driver driver(filename);
	EXPECT_EQ(driver.get_error_count(), 0);
}

TEST(parser, let_test) {
	std::string filename = "cases/let.rmm";
	rmmc::Driver driver(filename);
	EXPECT_EQ(driver.get_error_count(), 0);
}

TEST(parser, type_test) {
	std::string filename = "cases/type.rmm";
	rmmc::Driver driver(filename);
	EXPECT_EQ(driver.get_error_count(), 0);
}

TEST(parser, expression_test) {
	std::string filename = "cases/expression.rmm";
	rmmc::Driver driver(filename);
	EXPECT_EQ(driver.get_error_count(), 0);
}

TEST(parser, function_test) {
	std::string filename = "cases/function.rmm";
	rmmc::Driver driver(filename);
	EXPECT_EQ(driver.get_error_count(), 0);
}

TEST(parser, mod_test) {
	std::string filename = "cases/mod.rmm";
	rmmc::Driver driver(filename);
	EXPECT_EQ(driver.get_error_count(), 0);
}

TEST(parser, syntax_error_test) {
	/* Mute stdout if no error occurs */
	std::stringstream buffer;

	// Save cout's buffer here
	std::streambuf *sbuf = std::cout.rdbuf();

	// Redirect cout to our stringstream buffer or any other ostream
	std::cout.rdbuf(buffer.rdbuf());

	std::string filename = "cases/error.rmm";
	rmmc::Driver driver(filename);

	const int error_count = 17;
	if(error_count != driver.get_error_count()){
		std::cout << buffer.str();
	}else{
		/* print to log file */
		std::ofstream f("test.log");
		std::string s = buffer.str();
		std::stringstream result;
		/* remove escape sequence */
		std::regex re("\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])");
		std::regex_replace(std::ostream_iterator<char>(result), s.begin(), s.end(), re, "");
		f<<result.str();
	}

	std::cout.rdbuf(sbuf);
	EXPECT_EQ(driver.get_error_count(), error_count);
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
