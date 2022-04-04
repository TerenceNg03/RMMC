#include "driver.hh"
#include "parser.hh"
#include "scanner.hh"

using namespace std;

namespace rmmc 
{
    Driver::Driver()
    {
        parser  = new Parser(*this);
        scanner = new Scanner();
        location = new class location();
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

    int Driver::parse_file (std::string& path)
    {
		curr_file = path;
        std::ifstream s(path.c_str(), std::ifstream::in);
        scanner->switch_streams(&s, &std::cerr);

        int return_code = parser->parse();

        s.close();

        return return_code;
    }
}
