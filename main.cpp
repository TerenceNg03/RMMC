#include "driver.hh"
#include <signal.h>

using namespace std;

int main(int argc, const char * argv[]) {

    //setup driver
    MyParser::Driver driver;

    //run parser
    driver.parse();

    return 0;
}
