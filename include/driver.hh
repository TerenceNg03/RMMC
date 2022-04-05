
#ifndef DRIVER_HH_
# define DRIVER_HH_

# include <string>
# include <fstream>

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

	private:
		int parse();
		int parse_file(const std::string& path);

		Scanner*	  scanner;
		Parser*	   parser;
		rmmc::location*	 location;
		std::string curr_file;
		unsigned int error_count;
		unsigned int warning_count;


		/// Allows Parser and Scanner to access private attributes
		/// of the Driver class
		friend class  Parser;
		friend class  Scanner;
	};
}

#endif /* !DRIVER_HH_ */

