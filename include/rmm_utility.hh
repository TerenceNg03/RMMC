#ifndef RMM_UTILITY_HH
#define RMM_UTILITY_HH

#include <string>
#include "location.hh"
#include "AST.hh"
#include "driver.hh"

namespace rmmc{
	std::string str_process(const std::string& src);
	std::string str_unescape(const std::string& src);
	std::string str_unquote(const std::string& src);
	void report_error(context& cont, const location& loc, const std::string& msg);
	void report_error(Driver& driver, const location& loc, const std::string& msg);
	void report_warning(context& cont, const location& loc, const std::string& msg);
	void report_warning(Driver& driver, const location& loc, const std::string& msg);
}

#endif
