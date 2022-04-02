#include "driver.hh"
#include <signal.h>

using namespace std;

int main(int argc, const char * argv[]) {

    //setup driver
    rmmc::Driver driver;

    //run parser
    driver.parse();

    return 0;
}
