#include "rmm_utility.hh"
#include "driver.hh"

namespace rmmc{

	std::string str_process(const std::string& src){
		return str_unescape(str_unquote(src));
	}

	std::string str_unescape(const std::string& s){
		std::string ret = "";
		int len = (int)s.length();
		bool translate=false;
		int num=0;
		for(int i=0; i<len; i++){
			if(translate){
				switch (s[i]) {
					case 'n':
						ret += '\n';
						translate = false;
						break;
					case 'r':
						ret += '\r';
						translate = false;
						break;
					case 't':
						ret += '\t';
						translate = false;
						break;
					case 'a':
						ret += '\a';
						translate = false;
						break;
					case 'f':
						ret += '\f';
						translate = false;
						break;
					case 'v':
						ret += '\v';
						translate = false;
						break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
						num = 0;
						num += (s[i]-'0');
						if(i+1<len && s[i+1]<'8' && s[i+1]>='0'){
							num*=8;
							num+=s[i+1]-'0';
							++i;
						}
						if(i+1<len && s[i+1]<'8' && s[i+1]>='0'){
							num*=8;
							num+=s[i+1]-'0';
							++i;
						}
						ret += num;
						translate = false;
						break;
					default:
						ret += s[i];
						translate = false;
						break;
				}
			}else{
				if(s[i]=='\\'){
					translate = true;
				}else{
					ret += s[i];
				}
			}
		}
		return ret;
	}

	std::string str_unquote(const std::string& src){
		if(src.length()>=2){
			return src.substr(1, src.length()-2);
		}
		return src;
	}

	void report_error(context& cont, const location& loc, const std::string& msg){
		if(cont.driver){
			report_error(*(cont.driver), loc, msg);
		}else{
			std::cout<<" report_error: No driver in this context. Error printed.\n";
			std::cout << "line " << loc << ": " << msg << "\n";
		}
	}

	void report_error(Driver& driver, const location& loc, const std::string& msg){
		std::cout << "line " << loc << ": " << msg << "\n";
		++driver.error_count;
		int begin_line = loc.begin.line;
		int begin_col = loc.begin.column;
		int end_col = loc.end.column;
		/* Read that line from file */
		std::fstream file(driver.curr_file);
		file.seekg(std::ios::beg);
		for(int i=0; i < begin_line - 1; ++i){
			file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}
		std::string line;
		std::getline(file, line);
		std::cout<<"\t";
		for(int i=0; i<(int)line.size(); ++i){
			if(i == begin_col-1)std::cout<<"\033[1;31m";
			if(i == end_col-1)std::cout<<"\033[0m";
			std::cout<<line[i];
		}
		std::cout<<"\n\t";std::cout<<"\033[1;32m";
		for(int i = 0; i < begin_col-1; i++)
		std::cout<<"~";
		std::cout<<"^\n";std::cout<<"\033[0m";
	}

	void report_warning(context& cont, const location& loc, const std::string& msg){
		if(cont.driver){
			report_warning(*(cont.driver), loc, msg);
		}else{
			std::cout<<" report_error: No driver in this context. Error printed.\n";
			std::cout << "line " << loc << ": " << msg << "\n";
		}
	}

	void report_warning(Driver& driver, const location& loc, const std::string& msg){
		std::cout << "line " << loc << ": " << msg << "\n";
		++driver.error_count;
		int begin_line = loc.begin.line;
		int begin_col = loc.begin.column;
		int end_col = loc.end.column;
		/* Read that line from file */
		std::fstream file(driver.curr_file);
		file.seekg(std::ios::beg);
		for(int i=0; i < begin_line - 1; ++i){
			file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}
		std::string line;
		std::getline(file, line);
		std::cout<<"\t";
		for(int i=0; i<(int)line.size(); ++i){
			if(i == begin_col-1)std::cout<<"\033[1;33m";
			if(i == end_col-1)std::cout<<"\033[0m";
			std::cout<<line[i];
		}
		std::cout<<"\n\t";std::cout<<"\033[1;32m";
		for(int i = 0; i < begin_col-1; i++)
		std::cout<<"~";
		std::cout<<"^\n";std::cout<<"\033[0m";
	}
}

