#include "rmm_types.hh"
#include <iostream>

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

	rmm_type::rmm_type(const function_type& t) : func(t){
		tag = rmm_type::TAG::function;
	}

	rmm_type::rmm_type(const basic_type& t){
		tag = rmm_type::TAG::basic;
		bas = t;
	}

	rmm_type::rmm_type(const union_type& t){
		tag = rmm_type::TAG::union_;
		uni = t;
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
			case rmm_type::TAG::union_:
				uni = t.uni;
		}
	}

	bool rmm_type::operator==(const rmm_type& x) const{
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
			case rmm_type::TAG::union_:
				return uni == x.uni;
		}
		return true;
	}

	bool rmm_type::operator!=(const rmm_type& x) const{
		return !(*this == x);
	}

	rmm_type& rmm_type::operator=(const rmm_type& t){
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
			case rmm_type::TAG::union_:
				uni = t.uni;
				break;
		}
		return *this;
	}
	

	std::string rmm_type::str() const{
		switch(tag){
			case rmm_type::TAG::basic:
				switch(bas){
					case rmmc::basic_type::u8:
						return "u8";
					case rmmc::basic_type::u16:
						return "u16";
					case rmmc::basic_type::u32:
						return "u32";
					case rmmc::basic_type::u64:
						return "u64";
					case rmmc::basic_type::i8:
						return "i8";
					case rmmc::basic_type::i16:
						return "i16";
					case rmmc::basic_type::i32:
						return "i32";
					case rmmc::basic_type::i64:
						return "i64";
					case rmmc::basic_type::f32:
						return "f32";
					case rmmc::basic_type::f64:
						return "f64";
					case rmmc::basic_type::boolean:
						return "bool";
				};
				return "Unknown base_type" + std::to_string((int)bas);
				break;
			case rmm_type::TAG::array:
				return arr.str();	
				break;
			case rmm_type::TAG::compound:
				return comp.str();
				break;
			case rmm_type::TAG::pointer:
				return ptr.str();
				break;
			case rmm_type::TAG::function:
				return func.str();
				break;
			case rmm_type::TAG::union_:
				return uni.str();
			default:
				return "unknown type" + std::to_string((int)tag); 		
		}
		return "Error: type incorrect";
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
			case rmm_type::TAG::union_:
				uni.~union_type();
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

	bool array_type::operator==(const array_type& x) const{
		if(*(x.content_type) != *(this->content_type))return false;
		if(x.length != length)return false;
		return true;
	}

	array_type& array_type::operator =(const array_type& arr_t) {
		length = arr_t.length;
		content_type = new rmm_type(*(arr_t.content_type));
		return *this;	
	};
	

	std::string array_type::str() const {
		return "[" + content_type->str() + "," + std::to_string(length) + "]";
	}

	array_type::~array_type(){
		delete content_type;
	}

	compound_type::compound_type(const std::string& name, const std::vector<std::pair<std::string, rmm_type>>& t){
		this->name = name;
		for(auto &p: t){
			rmm_type* tmp = new rmm_type(p.second);
			type_list.push_back(std::make_pair(tmp, p.first));
		}
	}

	compound_type::compound_type(const compound_type& t){
		name = t.name;
		for(auto &p: t.type_list){
			rmm_type* tmp = new rmm_type(*(p.first));
			type_list.push_back(std::make_pair(tmp, p.second));
		}
	}

	bool compound_type::operator==(const compound_type& x) const{
		return name == x.name;
	}

	compound_type& compound_type::operator=(const compound_type& t){
		name = t.name;
		for(auto &p: t.type_list){
			rmm_type* tmp = new rmm_type(*(p.first));
			type_list.push_back(std::make_pair(tmp, p.second));
		}
		return *this;
	}

	std::string compound_type::str() const {
		std::string tmp = "comp " + name + "{";
		for(auto t: type_list){
			tmp += t.first->str() + "," + t.second + ";";
		}
		tmp += "}";
		return tmp;
	};

	compound_type::~compound_type(){
		for(auto &p: type_list){
			delete p.first;
		}
	}

	union_type::union_type(const std::string& name, const std::vector<std::pair<std::string, rmm_type>>& t) {
		this->name = name;
		for (auto& p : t) {
			rmm_type* tmp = new rmm_type(p.second);
			type_list.push_back(std::make_pair(tmp, p.first));
		}
	}

	union_type::union_type(const union_type& t) {
		name = t.name;
		for (auto& p : t.type_list) {
			rmm_type* tmp = new rmm_type(*(p.first));
			type_list.push_back(std::make_pair(tmp, p.second));
		}
	}

	bool union_type::operator==(const union_type& x) const {
		return name == x.name;
	}

	union_type& union_type::operator=(const union_type& t){
		name = t.name;
		for (auto& p : t.type_list) {
			rmm_type* tmp = new rmm_type(*(p.first));
			type_list.push_back(std::make_pair(tmp, p.second));
		}
		return *this;
	}
	

	std::string union_type::str() const {
		std::string tmp = "comp " + name + "{";
		for(auto t: type_list){
			tmp += t.first->str() + "," + t.second + ";";
		}
		tmp += "}";
		return tmp;
	};

	union_type::~union_type() {
		for (auto& p : type_list) {
			delete p.first;
		}
	}

	var_traits::var_traits(const bool mut, const bool ref, const bool unique)
	{
		this->mut = mut;
		this->ref = ref;
		this->unique = unique;
	}

	var_traits::var_traits(const var_traits& var_t)
	{
		this->mut = var_t.mut;
		this->ref = var_t.ref;
		this->unique = var_t.unique;
	}

	std::string var_traits::str() const{
		std::string tmp = "";
		if(mut) tmp += "mut ";
		if(ref) tmp += "ref ";
		if(unique) tmp += "unique ";
		return tmp;
	}

	bool var_traits::operator==(const var_traits& v) const{
		if(mut != v.mut)return false;
		if(ref != v.ref)return false;
		if(unique != v.unique) return false;
		return true;
	}
	
	var_traits::~var_traits()
	{

	}

	pointer_type::pointer_type(const rmm_type& t){
		content_type = new rmm_type(t);
	}

	pointer_type::pointer_type(const pointer_type& t){
		content_type = new rmm_type(*(t.content_type));
	}

	bool pointer_type::operator==(const pointer_type& x) const{
		return *content_type == *(x.content_type);
	}

	pointer_type& pointer_type::operator=(const pointer_type& t) {
		content_type = new rmm_type(*(t.content_type));
		return *this;
	}

	std::string pointer_type::str() const {
		return "*" + content_type->str();
	}

	pointer_type::~pointer_type(){
		delete content_type;
	}

	function_type::function_type(const std::vector<std::pair<var_traits, rmm_type>>& pars, const std::optional<rmm_type>& ret){
		for(auto& p: pars){
			rmm_type* ptr = new rmm_type(p.second);
			parameters.push_back(std::make_pair(p.first, ptr));
		}
		if(ret)return_type = new rmm_type(*ret);
		else return_type = nullptr;
	}

	function_type::function_type(const function_type& t){
		if(t.return_type)return_type = new rmm_type(*(t.return_type));
		else return_type = nullptr;
		for(auto &p: t.parameters){
			rmm_type* ptr = new rmm_type(*(p.second));
			parameters.push_back(std::make_pair(p.first, ptr));
		}
	}

	bool function_type::operator==(const function_type& x) const{
		if(x.parameters.size()!=parameters.size())return false;
		for(size_t i=0; i<parameters.size(); ++i){
			if(!(x.parameters[i].first==parameters[i].first))return false;
			if(*(x.parameters[i].second)!=*(parameters[i].second))return false;
		}

		if(!x.return_type){
			if(return_type)return false;
			else return true;
		}else{
			if(return_type && (*(x.return_type) == *return_type))return true;
			return false;
		}
		
	}

	function_type& function_type::operator=(const function_type& t){
		std::cout<<"function assign begin "<<t.str()<<std::endl;
		if(t.return_type)return_type = new rmm_type(*(t.return_type));
		else return_type = nullptr;
		parameters = std::vector<std::pair<var_traits, rmm_type*>>();
		 
		for(auto p: t.parameters){
			rmm_type* ptr = new rmm_type(*(p.second));
			parameters.push_back(std::make_pair(p.first, ptr));
		}
		std::cout<<"function assign done "<<this->str()<<std::endl;
		return *this;
	}

	std::string function_type::str() const {
		std::string tmp = "<";
		for(auto t: parameters){
			tmp += t.first.str() + t.second->str() + ",";
		}
		if(return_type)tmp += ";" + return_type->str() + ">";
		else tmp += ";void>";
		return tmp;
	}

	function_type::~function_type(){
		std::cout<<this->str()<<" freed"<<std::endl;
		for(auto& p: parameters){
			delete p.second;
		}
		delete return_type;
	}

	rmm_type make_u8(void)
	{
		basic_type t =  basic_type::u8;
		rmm_type x = rmm_type(t);
		return x;
	}
	rmm_type make_u16(void)
	{
		basic_type t =  basic_type::u16;
		rmm_type x = rmm_type(t);
		return x;
	}
	rmm_type make_u32(void)
	{
		basic_type t =  basic_type::u32;
		rmm_type x = rmm_type(t);
		return x;
	}
	rmm_type make_u64(void)
	{
		basic_type t =  basic_type::u64;
		rmm_type x = rmm_type(t);
		return x;
	}
	rmm_type make_i8(void)
	{
		basic_type t =  basic_type::i8;
		rmm_type x = rmm_type(t);
		return x;
	}
	rmm_type make_i16(void)
	{
		basic_type t =  basic_type::i16;
		rmm_type x = rmm_type(t);
		return x;
	}
	rmm_type make_i32(void)
	{
		basic_type t =  basic_type::i32;
		rmm_type x = rmm_type(t);
		return x;
	}
	rmm_type make_i64(void)
	{
		basic_type t = basic_type::i64;
		rmm_type x = rmm_type(t);
		return x;
	}
	rmm_type make_f32(void)
	{
		basic_type t = basic_type::f32;
		rmm_type x = rmm_type(t);
		return x;
	}
	rmm_type make_f64(void)
	{
		basic_type t = basic_type::f64;
		rmm_type x = rmm_type(t);
		return x;
	}
	rmm_type make_bool(void)
	{
		basic_type t =  basic_type::boolean;
		rmm_type x = rmm_type(t);
		return x;
	}
	

	rmm_type make_array(const rmm_type& inner_type, size_t array_size)
	{
		array_type t = array_type(array_size, inner_type);
		return t;
	}

	rmm_type make_array(const rmm_type& inner_type)
	{
		array_type t = array_type(0, inner_type);
		rmm_type x = rmm_type(t);
		return x;
	}

	std::optional<var_traits> make_traits(bool mut, bool ref, bool unique) noexcept
	{
		if (ref && unique) return {};
		var_traits t = var_traits(mut, ref, unique);
		return t;
	}

	

	rmm_type make_pointer(const rmm_type& t)
	{
		pointer_type k = pointer_type(t);
		rmm_type x = rmm_type(k);
		return x;
	}
}


