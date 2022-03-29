
#ifndef DRIVER_HH_
# define DRIVER_HH_

# include <string>
# include <fstream>

namespace MyParser
{
    /// Forward declarations of classes
    class Parser;
    class Scanner;
    class location;

    class Driver
    {
    public:
        Driver();
        ~Driver();

        int parse();
        int parse_file(std::string& path);

    private:
        Scanner*      scanner;
        Parser*       parser;
        MyParser::location*     location;


        /// Allows Parser and Scanner to access private attributes
        /// of the Driver class
        friend class  Parser;
        friend class  Scanner;
    };
}

#endif /* !DRIVER_HH_ */

