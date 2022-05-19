#include "driver.hh"
#include "parser.hh"
#include "scanner.hh"

using namespace std;

namespace rmmc 
{
	Driver::Driver(const std::string& filename)
	{
		parser  = new Parser(*this);
		scanner = new Scanner();
		location = new class location();
		error_count = 0;
		warning_count = 0;
		parse_file(filename);
	}

	unsigned int Driver::get_error_count() const{
		return error_count;
	}

	unsigned int Driver::get_warning_count() const{
		return warning_count;
	}

	Driver::~Driver()
	{
		delete parser;
		delete scanner;
		delete location;
	}

	int Driver::parse()
	{
		scanner->switch_streams(&std::cin, &std::cerr);
		return parser->parse();
	}

	int Driver::parse_file (const std::string& path)
	{
		curr_file = path;
		std::ifstream s(path.c_str(), std::ifstream::in);
		scanner->switch_streams(&s, &std::cerr);

		int return_code = parser->parse();

		s.close();

		return return_code;
	}

	void Driver::generate_c(const std::string& path){
		std::ofstream s(path.c_str(), std::ofstream::out);
		context cont_no_use(this);
		auto code = ast_root ? ast_root->emit_c_code(cont_no_use) : emit_code();
		const std::string c_include = "#include<stdlib.h>\n";
		s << c_include << code.exec;
		s.close();
	}
}
