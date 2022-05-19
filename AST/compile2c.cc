#include "AST.hh"
#include "rmm_utility.hh"

using namespace rmmc;
using std::cout;

bool check_assignable(context& cont, rmm_type lhs, rmm_type rhs, location l_loc, location r_loc){
	if((lhs.is_int()||lhs.is_float()||lhs.is_bool()) && (rhs.is_int()||rhs.is_float()||rhs.is_bool())) return true;

	if(lhs!= rhs){
		report_error(cont, l_loc + r_loc, "Miss matched type: "+ lhs.str() + " and " + rhs.str()); return false;
	}
	else if(lhs.is_union()){
		report_error(cont, l_loc, "Cannot assign union : "+ lhs.str() );
		return false;
	}else if(lhs.is_comp()){
		report_error(cont, l_loc, "Cannot assign compound : "+ lhs.str() );	
		return false;
	}else if(lhs.is_array()){
		report_error(cont, l_loc, "Cannot assign array: "+ lhs.str() );	
		return false;
	}else{
		return true;
	}
}

bool check_valid_number(context& cont, rmm_type t, location loc){
	if( t.is_int() || t.is_float() || t.is_bool() || t.is_ptr() ) return true;
	report_error(cont, loc, "Can not convert type \""+ t.str() +"\" to a number." );
	return false;
};

bool check_valid_int(context& cont, rmm_type t, location loc){
	if( t.is_int()) return true;
	report_error(cont, loc, "Can not convert type \""+ t.str() +"\" to an integer." );
	return false;
};

bool check_valid_condition(context& cont, rmm_type cond, location loc){

	if( cond.is_func() ) report_warning(cont, loc, "Function will always return true!");
	if( cond.is_union() || cond.is_comp() || cond.is_array() ){
		report_error(cont, loc, "Can not convert type \""+ cond.str() +"\" to boolean." );
		return false;		
	}
	return true;
};

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
			type = rhs->type;
			break;
		case binary_op::assign:// =
			if(check_assignable(cont, lhs->type, rhs->type, lhs->loc, rhs->loc)){
				exec = code1.exec + " = " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::logical_or:// ||
			if(check_valid_condition(cont, lhs->type, lhs->loc) && check_valid_condition(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " || " + code2.exec; 
			}
			type = make_bool();
			break;
		case binary_op::logical_and:// &&
			if(check_valid_condition(cont, lhs->type, lhs->loc) && check_valid_condition(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " && " + code2.exec; 
			}
			type = make_bool();
			break;
		case binary_op::bit_or:// |
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " | " + code2.exec; 
			}
			type = make_bool();
			break;
		case binary_op::bit_xor:// ^
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " ^ " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::bit_and:// &
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " & " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::eq:// ==
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " == " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::neq:// !=
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " != " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::gt:// >
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " > " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::lt:// <
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " < " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::ge:// >=
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " >= " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::le:// <=
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " <= " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::shift_left:// <<
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " << " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::shift_right:// >>
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " >> " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::plus:// +
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " + " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::minus:// -
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " - " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::div:// /
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " / " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::mul:// *
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " * " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::mod:// %
			if(check_valid_int(cont, lhs->type, lhs->loc) && check_valid_int(cont, rhs->type, rhs->loc)){
				exec = code1.exec + " % " + code2.exec; 
			}
			type = lhs->type;
			break;
		case binary_op::subscript:// [  ]
			if(!lhs->type.is_array()){
				report_error(cont, lhs->loc, "Can only subscript an array.");
			}else if(check_valid_int(cont, rhs->type, rhs->loc)){
				exec = code1.exec + "[" + code2.exec + "]"; 
				type = *(std::get<array_type>(lhs->type.content).content_type);
			}
			break;
		case binary_op::comp_ref:// .
			report_warning(cont, loc, "Not supported yet!");
			break;
		case binary_op::comp_deref: // ->
			report_warning(cont, loc, "Not supported yet!");
			break;
	}

	if(require_parentheses){
		exec = "(" + exec + ")"; 
	}

	return emit_code(decl, exec);
}

emit_code exp_cast::emit_c_code(context& cont){
	auto code_content = expr->emit_c_code(cont);
	emit_code ec;
	type = cast_type->get_type(cont);
	auto new_type = type.to_c_type();
	std::string exec = "((" + new_type.first + new_type.second +")"+  code_content.exec + ")";
	return emit_code(code_content.decl , exec);
}

emit_code exp_unary::emit_c_code(context& cont){
	return emit_code("", "");
}

emit_code exp_ternary::emit_c_code(context& cont){
	return emit_code("", "");
}

emit_code exp_funct_call::emit_c_code(context& cont){
	return emit_code("", "");
}

emit_code exp_id::emit_c_code(context& cont){
	
	return emit_code("", " " + id +" ");
}

emit_code exp_const::emit_c_code(context& cont){
	auto ret = value->emit_c_code(cont);
	type = value->type;
	return ret;
}

emit_code stat_dummy::emit_c_code(context& cont){
	return emit_code("", "");
}

emit_code stat_decl::emit_c_code(context& cont){
	auto init_code = init_value ? init_value->emit_c_code(cont) : emit_code();
	if(init_value){

		if(!check_assignable(cont, type->get_type(cont), init_value->type, type->loc, init_value->loc )){
			report_error(cont, loc, "Mismatched initial value type : expected " + type->get_type(cont).str() + " got " + init_value->type.str() );
	}
	} 

	auto c_type = type->get_type(cont).to_c_type();

	std::string exec = "";

	if(traits.ref){
		exec = c_type.first + "(* USER_" + var_name + ")" + c_type.second;
		if(init_value)exec += " = &(" + init_code.exec + ");";
		else exec += ";";
	}
	else if(traits.unique){
		exec = c_type.first + "(* USER_" + var_name + ")" + c_type.second;
		exec += " = (void*)malloc(sizeof(" + c_type.first + c_type.second + "));\n";
		if(init_value)exec += "*(USER_"+ var_name + ") = " + init_code.exec + ";\n";
		else exec += ";";
	}
	else{
		exec += c_type.first + " USER_" + var_name + c_type.second; 
		if(init_value)exec += " = " + init_code.exec + ";";
		else exec += ";";
	}
	return emit_code(init_code.decl , exec);
}

emit_code stat_block::emit_c_code(context& cont){
	std::string decl = "";
	std::string exec = "";
	for (int i=0; i<stats.size(); ++i){
		auto tmp = stats[i]->emit_c_code(stat_context);
		decl += tmp.decl;
		exec += tmp.exec;
	}
	return emit_code("", decl+exec);
}
