#include "AST.hh"
#include "rmm_utility.hh"

using namespace rmmc;
using std::cout;

struct temp_var{
	std::string decl;
	std::string name;
};

std::vector<std::string> context::find_dead_var(bool local) // var needs to be free, local block or return statement
{
	std::vector<std::string> vec;
	for(auto p: variables){
		if(!(p.second.traits.unique))continue;
		if(moved.find(p.first) == moved.end())vec.push_back(p.first);
	}
	if(!local && !is_function_body && parent){
		auto vec_p = parent->find_dead_var(false);
		for(auto p: vec_p){
			vec.push_back(p);
		}
	} 

	return vec;
}

bool is_moved(exp_general* exp){
	exp_unary* moved = dynamic_cast<exp_unary*>(exp);
	if(!moved) return false;
	else return moved->moved;
}

bool is_unique(context& cont, exp_general* exp){
	exp_id* var_exp = dynamic_cast<exp_id*>(exp);
	if(!var_exp) return false;
	
	auto var = cont.find_var_by_name("USER_" + var_exp->id);
	return var->traits.unique;
}

std::string generate_name(context& cont){
	std::string var_name = "RMMC_" + cont.context_tag + "_" + std::to_string(cont.anonymous_cnt);
	cont.anonymous_cnt++;
	return var_name;
}

temp_var generate_temp_var(context& cont, rmm_type t){
	auto c_type = t.to_c_type();
	auto var_name = generate_name(cont);
	std::string decl = c_type.first + var_name + c_type.second + ";\n";
	return {decl, var_name};
}

std::string generate_user_name(context& cont, std::string name){
	return "USER_"+cont.context_tag+"_"+ name;
}


bool check_assignable(context& cont, rmm_type lhs, rmm_type rhs, location l_loc, location r_loc, bool is_init = false){
	if((lhs.is_int()||lhs.is_float()||lhs.is_bool()) && (rhs.is_int()||rhs.is_float()||rhs.is_bool())) return true;

	if(lhs!= rhs){
		report_error(cont, l_loc + r_loc, "Miss matched type: "+ lhs.str() + " and " + rhs.str()); return false;
	}
	else if(!is_init && lhs.is_union()){
		report_error(cont, l_loc, "Cannot assign union : "+ lhs.str() );
		return false;
	}else if(!is_init && lhs.is_comp()){
		report_error(cont, l_loc, "Cannot assign compound : "+ lhs.str() );	
		return false;
	}else if(!is_init && lhs.is_array()){
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
emit_code::emit_code(std::string _decl, std::string _exec, std::string _name): decl(_decl), exec(_exec), name(_name){};


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

std::string context::find_return_tag(){
	if(is_function_body)return context_tag;
	if(!parent){
		return "";
	}else{
		return parent->find_return_tag();
	}
}


emit_code const_dummy::emit_c_code(context& cont){
	return emit_code();
}

emit_code const_basic::emit_c_code(context& cont){
	std::string code = "";
	std::visit([&](auto&& arg){ code = std::to_string(arg);}, value);
	auto tmp = generate_temp_var(cont, type);
	return emit_code(tmp.decl, tmp.name + " = " + code + '\n', tmp.name);
}


emit_code const_array::emit_c_code(context& cont){
	std::string decl_pre = "";
	std::string var_name = " RMMC_" + std::to_string(cont.anonymous_cnt)+ " ";
	cont.anonymous_cnt++;
	std::string decl_this = var_name;
	type = make_array(type, values.size());
	auto p = type.to_c_type();
	std::string exec;
	/*** to do : type check **/
	decl_this = p.first + var_name + p.second + " = {\n";
		for(int i=0; i<values.size(); ++i){
			emit_code code = values[i]->emit_c_code(cont);
			decl_pre += code.decl;
			decl_this += code.name + ",\n";
			exec += code.exec;
		}
	decl_this.pop_back();
	decl_this.pop_back();
	decl_this += "};\n";
	auto tmp = generate_temp_var(cont, type);
	return emit_code(decl_pre + decl_this, exec , var_name);
}

emit_code exp_dummy::emit_c_code(context& cont){return emit_code();};			

emit_code exp_binary::emit_c_code(context& cont){
	auto code1 = lhs->emit_c_code(cont);
	auto code2 = rhs->emit_c_code(cont);
	
	std::string decl = code1.decl + code2.decl;
	std::string code1_real_name = code1.name;

	if(dynamic_cast<exp_id*>(lhs.get())){
		auto var = cont.find_var_by_name(code1.name);
		if(var && (var->traits.ref || var->traits.unique)){
			code1.name = "(*" + code1.name + ")";
		}
	}

	if(dynamic_cast<exp_id*>(rhs.get())){
		auto var = cont.find_var_by_name(code2.name);
		if(var && (var->traits.ref || var->traits.unique)){
			code2.name = "(*" + code2.name + ")";
		}
	}
	
	std::string exec = "";
	typedef exp_binary::binary_op binary_op;
	switch (op){
		case binary_op::comma: // ,
			exec = code1.name + "," + code2.name;
			type = rhs->type;
			break;
		case binary_op::assign:// =
			if(dynamic_cast<exp_id*>(lhs.get())){
				auto var = cont.find_var_by_name(code1_real_name);
				if(var && !var->traits.mut) report_error(cont, lhs->loc, "Assign to immutable vairable \""+ code1.name + "\" is not allowed.");
			}
			if(dynamic_cast<exp_const*>(lhs.get())){
				report_error(cont, lhs->loc, "Can not assign to rvalue.");
			}
			if(check_assignable(cont, lhs->type, rhs->type, lhs->loc, rhs->loc)){
				exec = code1.name + " = " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::logical_or:// ||
			if(check_valid_condition(cont, lhs->type, lhs->loc) && check_valid_condition(cont, rhs->type, rhs->loc)){
				exec = code1.name + " || " + code2.name; 
			}
			type = make_bool();
			break;
		case binary_op::logical_and:// &&
			if(check_valid_condition(cont, lhs->type, lhs->loc) && check_valid_condition(cont, rhs->type, rhs->loc)){
				exec = code1.name + " && " + code2.name; 
			}
			type = make_bool();
			break;
		case binary_op::bit_or:// |
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " | " + code2.name; 
			}
			type = make_bool();
			break;
		case binary_op::bit_xor:// ^
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " ^ " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::bit_and:// &
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " & " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::eq:// ==
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " == " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::neq:// !=
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " != " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::gt:// >
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " > " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::lt:// <
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " < " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::ge:// >=
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " >= " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::le:// <=
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " <= " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::shift_left:// <<
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " << " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::shift_right:// >>
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " >> " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::plus:// +
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " + " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::minus:// -
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " - " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::div:// /
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " / " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::mul:// *
			if(check_valid_number(cont, lhs->type, lhs->loc) && check_valid_number(cont, rhs->type, rhs->loc)){
				exec = code1.name + " * " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::mod:// %
			if(check_valid_int(cont, lhs->type, lhs->loc) && check_valid_int(cont, rhs->type, rhs->loc)){
				exec = code1.name + " % " + code2.name; 
			}
			type = lhs->type;
			break;
		case binary_op::subscript:// [  ]
			if(!lhs->type.is_array()){
				report_error(cont, lhs->loc, "Can only subscript an array.");
			}else if(check_valid_int(cont, rhs->type, rhs->loc)){
				exec = code1.name + "[" + code2.name + "]"; 
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
	/*
	if(require_parentheses){
		exec = "(" + exec + ")"; 
	}
	*/
	auto tmp = generate_temp_var(cont, type);
	exec = tmp.name + " = " + exec;
	return emit_code(decl + tmp.decl, code1.exec + code2.exec +exec + '\n', tmp.name);
}

emit_code exp_cast::emit_c_code(context& cont){
	auto code_content = expr->emit_c_code(cont);
	emit_code ec;
	type = cast_type->get_type(cont);
	auto new_type = type.to_c_type();
	std::string exec = "((" + new_type.first + new_type.second +")"+  code_content.exec + ")";
	auto tmp = generate_temp_var(cont, type);
	return emit_code(code_content.decl + tmp.decl, tmp.name + " = " + exec, tmp.name);
}

emit_code exp_unary::emit_c_code(context& cont){
	auto code = expr->emit_c_code(cont);
	if(op == unary_op::move){
		auto var_exp = dynamic_cast<exp_id*>(expr.get());
		if(!var_exp){
			report_error(cont, loc, "Can only move unique variables.");
			return emit_code();
		}else{
			auto var = cont.find_var_by_name("USER_" + var_exp->id);
			if(!(var->traits.unique)){
				report_error(cont, loc, "Can only move unique variables.");
				return emit_code();
			}
			cont.moved.insert("USER_" + var_exp->id);
			moved = true;
			return code;
		}
	}

	return emit_code();
}

emit_code exp_ternary::emit_c_code(context& cont){
	report_error(cont, loc, "Not supported yet");
	return emit_code();
}

emit_code exp_funct_call::emit_c_code(context& cont){
	auto call_code = callable->emit_c_code(cont);

	std::string pre_decl = call_code.decl;
	std::string pre_exec = call_code.exec;

	if(!callable->type.is_func()){
		report_error(cont, loc, "Can only call a function.");
		return emit_code();
	}

	function_type ft = std::get<function_type>(callable->type.content);

	std::vector<std::string> para_names;
	for(int i=0; i<parameters.size(); ++i){
		/** declaration for parameters **/

		std::string var_name = generate_name(cont);
		para_names.push_back(var_name);

		auto c_type = ft.parameters[i].second->to_c_type();
		auto traits = ft.parameters[i].first;
		auto init_code = parameters[i]->emit_c_code(cont);

		std::string exec = " ";

		check_assignable(cont, *(ft.parameters[i].second), parameters[i]->type, parameters[i]->loc, parameters[i]->loc);

		if(traits.ref){
			exec = c_type.first + "(* " + var_name + ")" + c_type.second + "\n";
			exec += " *("+ var_name + ") = " + init_code.name + "\n";
		}
		else if(traits.unique){
			exec = c_type.first + "(* " + var_name + ")" + c_type.second;
			exec += " = malloc(sizeof(" + c_type.first + c_type.second + "))\n";
			exec += " *("+ var_name + ") = " + init_code.name + "\n";
		}
		else{
			exec += c_type.first + " " + var_name + c_type.second + '\n'; 
			exec +=  var_name + " = " + init_code.name + "\n";
		}

		pre_decl += init_code.decl + exec;
		pre_exec += init_code.exec;

	}
	
	if(ft.return_type) type = *(ft.return_type);

	std::string call_exec = call_code.name + "(";
	for(auto s: para_names){
		call_exec += " " + s + " ,";
	}
	call_exec.pop_back();
	call_exec += ")\n";
	std::string tmp_name ;
	if(ft.return_type){
		tmp_name = generate_name(cont);
		call_exec = tmp_name + " = " + call_exec;
	} 

	return emit_code(pre_decl, pre_exec+ call_exec, tmp_name);
}

emit_code exp_id::emit_c_code(context& cont){
	auto var = cont.find_var_by_name("USER_" + id);
	std::string ret;
	if(!var) report_error(cont, loc, "Variable USER_" + id + " is not defined");
	else {
		type = var->var_type;
		ret = "USER_" + id; 
	}
	return emit_code("", "", ret);
}

emit_code exp_const::emit_c_code(context& cont){
	auto ret = value->emit_c_code(cont);
	type = value->type;
	return ret;
}

emit_code stat_dummy::emit_c_code(context& cont){
	return emit_code();
}

emit_code stat_func_decl::emit_c_code(context& cont){

	if(cont.find_var_by_name("USER_"+var_name)){
		report_error(cont, loc, "Redefinition of variable " + var_name );
		return emit_code("", "", "USER_"+var_name);
	}

	if(var_name == "")var_name = generate_name(cont);

	real_type = type->get_type(cont);

	auto c_type = real_type.to_c_type();

	std::string exec = " ";

	if(traits.ref){
		exec = c_type.first + "(* USER_" + var_name + ")" + c_type.second + "\n";
	}
	else if(traits.unique){
		exec = c_type.first + "(* USER_" + var_name + ")" + c_type.second;
	}
	else{
		exec += c_type.first + " USER_" + var_name + c_type.second + '\n'; 
	}

	context::variable v = {traits, real_type, false};
	cont.variables.insert(make_pair("USER_"+var_name, v));

	return emit_code("", exec, var_name);
}

emit_code stat_decl::emit_c_code(context& cont){
	auto init_code = init_value ? init_value->emit_c_code(cont) : emit_code();

	if(cont.find_var_by_name("USER_"+var_name)){
		report_error(cont, loc, "Redefinition of variable " + var_name );
		return emit_code("", "", "USER_"+var_name);
	}

	if(init_value){
		real_type = init_value->type;
		if (!type){  }
		else if(!check_assignable(cont, type->get_type(cont), init_value->type, type->loc, init_value->loc, true )){
			report_error(cont, loc, "Mismatched initial value type : expected " + type->get_type(cont).str() + " got " + init_value->type.str() );
		}
	} else{
		real_type = type->get_type(cont);
	}

	auto c_type = real_type.to_c_type();

	std::string exec = " ";

	if(traits.ref){
		exec = c_type.first + "(* USER_" + var_name + ")" + c_type.second + "\n";
		if(init_value)exec += " " + var_name + " = &(" + init_code.name + ")\n";
	}
	else if(traits.unique){
		exec = c_type.first + "(* USER_" + var_name + ")" + c_type.second + "\n";
		
		if(init_value){
			if(is_moved(init_value.get())){
				exec += "USER_"+ var_name + " = " + init_code.name + "\n";
			}else if(is_unique(cont, init_value.get())){
				report_error(cont, loc, "Cannot copy unique variable. Move it instead.");
			}else {
				exec += "USER_" + var_name + " = malloc(sizeof(" + c_type.first + c_type.second + "))\n";			
				exec += " *(USER_"+ var_name + ") = " + init_code.name + "\n";
			}
		}else{
			exec += " = malloc(sizeof(" + c_type.first + c_type.second + "))\n";			
		}
	}
	else{
		exec += c_type.first + " USER_" + var_name + c_type.second + '\n'; 
		if(init_value)exec += " USER_" + var_name +  " = " + init_code.name + "\n";
	}

	if(init_value) exec = init_code.exec + exec;

	context::variable v = {traits, real_type, exportable};
	cont.variables.insert(make_pair("USER_"+var_name, v));

	return emit_code(init_code.decl , exec, var_name);
}

emit_code const_function::emit_c_code(context& cont){
	emit_code para_init;
	emit_code ret_init;
	auto tmp = generate_temp_var(cont, type);
	body->set_parent_context(&cont);
	body->stat_context.is_function_body = true;
	body->stat_context.context_tag  = tmp.name;
	std::vector<std::pair<var_traits, rmm_type>> para_type;
	for(int i=0; i<parameters.size(); ++i){
		auto code = parameters[i]->emit_c_code(cont);
		para_init.decl += code.decl;
		para_init.exec += code.exec;
		para_type.push_back(std::make_pair(parameters[i]->traits, parameters[i]->real_type));
	}

	if(return_var){
		auto code = return_var->emit_c_code(cont);
		ret_init.decl = code.decl;
		ret_init.exec = code.exec;
		type = make_function(para_type.begin(), para_type.end(), return_var->traits, return_var->type->get_type(cont));
	}else{
		type = make_function(para_type.begin(), para_type.end(), var_traits(false, false, false), {});
	}
	std::string exec;
	exec += body->generate("", false);

	exec = tmp.name + ":\n" + ">>> function paramters >>>\n"+ para_init.decl + para_init.exec + ret_init.decl + ret_init.exec +">>> function body >>>\n" + exec + "<<< function ends <<<\n";

	return emit_code("", exec, tmp.name);

};

emit_code stat_exp::emit_c_code(context& cont){
	return expr->emit_c_code(cont);
}

emit_code stat_break::emit_c_code(context& cont){
	return emit_code("", "break", "");
}

emit_code stat_continue::emit_c_code(context& cont){
	return emit_code("", "continue", "");
}

emit_code stat_ret::emit_c_code(context& cont){
	std::string ret_tag = cont.find_return_tag();
	if( ret_tag == "" ){
		report_error(cont, loc, "Can only return inside a function.");
	}

	if(ret_val){
		auto code = ret_val->emit_c_code(cont);
		std::string free_exec = "";
		for(auto name : cont.find_dead_var(false)){
			free_exec += "free(" + name + ")\n";
		}
		return emit_code(code.decl, code.exec + free_exec + "ret " + code.name + " to "+ ret_tag + "\n", "");
	}else{
		std::string free_exec = "";
		for(auto name : cont.find_dead_var(false)){
			free_exec += "free(" + name + ")\n";
		}
		return emit_code("", free_exec + "ret to "+ ret_tag +"\n", "");
	}
}

void stat_block::set_parent_context(context* parent){
	stat_context.parent = parent;
};

std::string stat_block::generate(std::string name, bool has_mark){
	std::string decl = "";
	std::string exec = "";
	std::string blk_name = (name == "") ? generate_name(stat_context) : name;
	for (int i=0; i<stats.size(); ++i){
		auto tmp = stats[i]->emit_c_code(stat_context);
		decl += tmp.decl;
		exec += tmp.exec;
	}

	for(auto name : stat_context.find_dead_var(true)){
		exec += "free(" + name + ")\n";
	}
	if(has_mark) return ">>>>>> "+blk_name+ " symbol table >>>>>>\n\n" +decl + "\n>>>>>>>>> code >>>>>>>>>>>\n\n" + exec + "\n>>>>>>> end of "+blk_name+" >>>>>>>>\n\n";
	else return decl+exec;
}
