#ifndef RMM_UTILITY_HH
#define RMM_UTILITY_HH

#include <string>
#include <utility>

namespace rmmc{
	std::string str_process(const std::string& src);
	std::string str_unescape(const std::string& src);
	std::string str_unquote(const std::string& src);
	std::optional<char> char_process(const std::string& src);
}

#endif
