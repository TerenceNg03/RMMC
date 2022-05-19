#include "AST.hh"
#include "rmm_utility.hh"

using namespace rmmc;

context::context(Driver* _driver) : driver(_driver){};

emit_code::emit_code(){};
emit_code::emit_code(std::string _decl, std::string _exec): decl(_decl), exec(_exec){};


std::optional<context::variable> context::find_var_by_name(const std::string& name){
	auto result = variables.find(name);
	if(result != variables.end()){
		return result->second;
	}else{
		if(!parent) return {};
		else return parent->find_var_by_name(name);
	}
}

std::optional<context::custom_type> context::find_type_by_name(const std::string& name){
	auto result = custom_types.find(name);
	if(result != custom_types.end()){
		return result->second;
	}else{
		if(!parent) return {};
		else return parent->find_type_by_name(name);
	}
}

emit_code const_basic::emit_c_code(context& cont){
	std::string code = "";
	std::visit([&](auto&& arg){ code = std::to_string(arg);}, value);
	return emit_code("", code);
}


emit_code const_array::emit_c_code(context& cont){
	std::string decl_pre = "";
	std::string var_name = " RMMC_" + std::to_string(cont.anonymous_cnt)+ " ";
	cont.anonymous_cnt++;
	std::string decl_this = var_name;
	auto p = type.to_c_type();
	decl_this = "const " + p.first + var_name + p.second + " = {";
		for(int i=0; i<values.size(); ++i){
			emit_code code = values[i]->emit_c_code(cont);
			decl_pre += code.decl;
			decl_this += code.exec + ",\n";
		}
	decl_this.pop_back();
	decl_this += "};\n";
	return emit_code(decl_pre + decl_this , var_name);
}

emit_code exp_dummy::emit_c_code(context& cont){return emit_code();};			

emit_code exp_binary::emit_c_code(context& cont){
	auto code1 = lhs->emit_c_code(cont);
	auto code2 = rhs->emit_c_code(cont);
	
	std::string decl = code1.decl + "\n" + code2.decl;
	std::string exec = "";
	typedef exp_binary::binary_op binary_op;
	switch (op){
		case binary_op::comma: // ,
			exec = code1.exec + "," + code2.exec;
			type = rmm_type(rhs->type);
			break;
		case binary_op::assign:// =
			if(lhs->type != rhs->type){
				report_error(cont, loc, "Miss matched type: "+ lhs->type.str() + " and " + rhs->type.str());
			}
			else if(lhs->type.is_union()){
				report_error(cont, loc, "Cannot assign union : "+ lhs->type.str() );
			}else if(lhs->type.is_comp()){
				report_error(cont, loc, "Cannot assign compound : "+ lhs->type.str() );
			}else{
				exec = code1.exec + " = " + code2.exec; 
			}
			break;
		case binary_op::logical_or:// ||
			if( lhs->type.is_func() ) report_warning(cont, loc, "Function will always return true!");
			break;
		case binary_op::logical_and:// &&
			break;
		case binary_op::bit_or:// |
			break;
		case binary_op::bit_xor:// ^
			break;
		case binary_op::bit_and:// &
			break;
		case binary_op::eq:// ==
			break;
		case binary_op::neq:// !=
			break;
		case binary_op::gt:// >
			break;
		case binary_op::lt:// <
			break;
		case binary_op::ge:// >=
			break;
		case binary_op::le:// <=
			break;
		case binary_op::shift_left:// <<
			break;
		case binary_op::shift_right:// >>
			break;
		case binary_op::plus:// +
			break;
		case binary_op::minus:// -
			break;
		case binary_op::div:// /
			break;
		case binary_op::mul:// *
			break;
		case binary_op::mod:// %
			break;
		case binary_op::subscript:// [  ]
			break;
		case binary_op::comp_ref:// .
			report_warning(cont, loc, "Function will always return true!");
			break;
		case binary_op::comp_deref: // ->
			report_warning(cont, loc, "Function will always return true!");
			break;
	}

	if(require_parentheses){
		exec = "(" + exec + ")"; 
	}

	return emit_code(decl, exec);
}

