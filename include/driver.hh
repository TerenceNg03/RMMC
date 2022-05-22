
#ifndef DRIVER_HH_
# define DRIVER_HH_

# include <string>
# include <fstream>
#include "AST.hh"

namespace rmmc
{
	/// Forward declarations of classes
	class Parser;
	class Scanner;
	class location;

	class Driver
	{
	public:
		Driver(const std::string& filename);
		unsigned int get_error_count() const;
		unsigned int get_warning_count() const;
		~Driver();

		int parse();
		int parse_file(const std::string& path);
		void generate_c(const std::string& path);
		void generate_ast(const std::string& path);

		Scanner*	  scanner;
		Parser*	   parser;
		rmmc::location*	 location;
		int context_cnt = 0;
		std::unique_ptr<stat_block> ast_root;
		std::string curr_file;
		unsigned int error_count;
		unsigned int warning_count;
	};
}

#endif /* !DRIVER_HH_ */

