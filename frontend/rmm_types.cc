#include "rmm_types.hh"

namespace rmmc{


	rmm_type::rmm_type(const array_type& t){
		tag = rmm_type::TAG::array;
		arr = t;
	}

	rmm_type::rmm_type(const compound_type& t){
		tag = rmm_type::TAG::compound;
		comp = t;
	}

	rmm_type::rmm_type(const pointer_type& t){
		tag = rmm_type::TAG::pointer;
		ptr = t;
	}

	rmm_type::rmm_type(const function_type& t){
		tag = rmm_type::TAG::function;
		func = t;
	}

	rmm_type::rmm_type(const basic_type& t){
		tag = rmm_type::TAG::basic;
		bas = t;
	}

	rmm_type::rmm_type(const rmm_type& t){
		tag = t.tag;
		switch(tag) {
			case rmm_type::TAG::basic:
				bas = t.bas;
				break;
			case rmm_type::TAG::array:
				arr = t.arr;
				break;
			case rmm_type::TAG::compound:
				comp = t.comp;
				break;
			case rmm_type::TAG::pointer:
				ptr = t.ptr;
				break;
			case rmm_type::TAG::function:
				func = t.func;
				break;
		}
	}

	bool rmm_type::operator==(const rmm_type& x){
		if(x.tag != tag)return false;
		switch (tag){
			case rmm_type::TAG::basic:
				return bas == x.bas;
			case rmm_type::TAG::array:
				return arr == x.arr;
			case rmm_type::TAG::compound:
				return comp == x.comp;
			case rmm_type::TAG::pointer:
				return ptr == x.ptr;
			case rmm_type::TAG::function:
				return func == x.func;
		}
		return true;
	}

	bool rmm_type::operator!=(const rmm_type& x){
		return !(*this == x);
	}

	rmm_type::~rmm_type(){
		switch(tag){
			case rmm_type::TAG::basic:
				break;
			case rmm_type::TAG::array:
				arr.~array_type();	
				break;
			case rmm_type::TAG::compound:
				comp.~compound_type();
				break;
			case rmm_type::TAG::pointer:
				ptr.~pointer_type();
				break;
			case rmm_type::TAG::function:
				func.~function_type();
				break;
		}
	}



	array_type::array_type(const size_t length, const rmm_type& t){
		this->length = length;
		content_type = new rmm_type(t);
	}

	array_type::array_type(const array_type& arr_t){
		length = arr_t.length;
		content_type = new rmm_type(*(arr_t.content_type));
	}

	bool array_type::operator==(const array_type& x){
		if(*(x.content_type) != *(this->content_type))return false;
		if(x.length != length)return false;
		return true;
	}

	array_type::~array_type(){
		delete content_type;
	}

	compound_type::compound_type(const std::string& name, const std::vector<std::pair<rmm_type, std::string>>& t){
		this->name = name;
		for(auto &p: t){
			rmm_type* tmp = new rmm_type(p.first);
			type_list.push_back(make_pair(tmp, p.second));
		}
	}

	compound_type::compound_type(const compound_type& t){
		name = t.name;
		for(auto &p: t.type_list){
			rmm_type* tmp = new rmm_type(*(p.first));
			type_list.push_back(make_pair(tmp, p.second));
		}
	}

	bool compound_type::operator==(const compound_type& x){
		return name == x.name;
	}

	compound_type::~compound_type(){
		for(auto &p: type_list){
			delete p.first;
		}
	}

	pointer_type::pointer_type(const rmm_type& t){
		content_type = new rmm_type(t);
	}

	pointer_type::pointer_type(const pointer_type& t){
		content_type = new rmm_type(*(t.content_type));
	}

	bool pointer_type::operator==(const pointer_type& x){
		return *content_type == *(x.content_type);
	}

	pointer_type::~pointer_type(){
		delete content_type;
	}

	function_type::function_type(const std::vector<rmm_type>& pars, const rmm_type& ret){
		for(auto& p: pars){
			rmm_type* ptr = new rmm_type(p);
			parameters.push_back(ptr);
		}
		return_type = new rmm_type(ret);
	}

	function_type::function_type(const function_type& t){
		return_type = new rmm_type(*(t.return_type));
		for(auto &p: t.parameters){
			rmm_type* ptr = new rmm_type(*p);
			parameters.push_back(ptr);
		}
	}

	bool function_type::operator==(const function_type& x){
		if(x.parameters.size()!=parameters.size())return false;
		if(*(x.return_type) != *return_type)return false;
		for(size_t i=0; i<parameters.size(); ++i){
			if(*(x.parameters[i])!=*(parameters[i]))return false;
		}
		return true;
	}

	function_type::~function_type(){
		for(auto& p: parameters){
			delete p;
		}
	}



}


