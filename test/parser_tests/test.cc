#include <gtest/gtest.h>
#include <regex>
#include <string>
#include <vector>
#include "driver.hh"

const std::string case_file = "/tmp/tmp.rmm";

std::vector<std::string> split_files(std::string filename){
	using namespace std;
	ifstream infile(filename);
	vector<string> myVec;

	string line;
	string comboLine="";
	while(!infile.eof()){
		getline(infile,line);
		if (line == "" || line == "\0")  {
			//cout<<"->BLANK LINE DETECTED<-"<<endl;
			myVec.push_back(comboLine);
			comboLine="";
		}else {
			comboLine = comboLine + line +'\n';
			//cout<<"comb: "<<comboLine<<endl;
		}

		line = "";

	}

	if(comboLine!="")myVec.push_back(comboLine);

	infile.close();
	return myVec;
}

void create_case(const std::string s){
		std::fstream is(case_file, std::ios::out);
		is<<s;
		is.close();
}

TEST(parser, import_test) {
	std::string filename = "cases/import.rmm";
	auto cases = split_files(filename);
	for(auto tcase: cases){
		create_case(tcase);
		rmmc::Driver driver(case_file);
		EXPECT_EQ(driver.get_error_count(), 0);
	}
}

TEST(parser, let_test) {
	std::string filename = "cases/let.rmm";
	auto cases = split_files(filename);
	for(auto tcase: cases){
		create_case(tcase);
		rmmc::Driver driver(case_file);
		EXPECT_EQ(driver.get_error_count(), 0);
	}
}

TEST(parser, type_test) {
	std::string filename = "cases/type.rmm";
	auto cases = split_files(filename);
	for(auto tcase: cases){
		create_case(tcase);
		rmmc::Driver driver(case_file);
		EXPECT_EQ(driver.get_error_count(), 0);
	}
}

TEST(parser, expression_test) {
	std::string filename = "cases/expression.rmm";
	auto cases = split_files(filename);
	for(auto tcase: cases){
		create_case(tcase);
		rmmc::Driver driver(case_file);
		EXPECT_EQ(driver.get_error_count(), 0);
	}
}

TEST(parser, function_test) {
	std::string filename = "cases/function.rmm";
	auto cases = split_files(filename);
	for(auto tcase: cases){
		create_case(tcase);
		rmmc::Driver driver(case_file);
		EXPECT_EQ(driver.get_error_count(), 0);
	}
}

TEST(parser, mod_test) {
	std::string filename = "cases/mod.rmm";
	auto cases = split_files(filename);
	for(auto tcase: cases){
		create_case(tcase);
		rmmc::Driver driver(case_file);
		EXPECT_EQ(driver.get_error_count(), 0);
	}
}

TEST(parser, syntax_error_test) {
	/* Mute stdout if no error occurs */
	std::stringstream buffer;

	// Save cout's buffer here
	std::streambuf *sbuf = std::cout.rdbuf();

	// Redirect cout to our stringstream buffer or any other ostream
	std::cout.rdbuf(buffer.rdbuf());

	std::string filename = "cases/error.rmm";
	auto cases = split_files(filename);
	for(auto tcase: cases){
		if(tcase=="")continue;
		create_case(tcase);
		rmmc::Driver driver(case_file);
		std::cout.rdbuf(sbuf);
		if(driver.get_error_count()==0){
			std::cout<<"\033[1;31mCase Failed\033[30m:\n\n"<< tcase <<"\033[0m\n";
		}
		EXPECT_EQ(driver.get_error_count()>0, true);
		std::cout.rdbuf(buffer.rdbuf());
	}

	/* print to log file */
	std::ofstream f("test.log");
	std::string s = buffer.str();
	std::stringstream result;
	/* remove escape sequence */
	std::regex re("\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])");
	std::regex_replace(std::ostream_iterator<char>(result), s.begin(), s.end(), re, "");
	f<<result.str();

	std::cout.rdbuf(sbuf);
}

int main(int argc, char** argv){
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
