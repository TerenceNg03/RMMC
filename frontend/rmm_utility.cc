#include "rmm_utility.hh"

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

}
