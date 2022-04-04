
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
		bool failed() const;
		~Driver();

	private:
		int parse();
		int parse_file(const std::string& path);

		Scanner*	  scanner;
		Parser*	   parser;
		rmmc::location*	 location;
		std::string curr_file;
		bool is_failed;


		/// Allows Parser and Scanner to access private attributes
		/// of the Driver class
		friend class  Parser;
		friend class  Scanner;
	};
}

#endif /* !DRIVER_HH_ */

