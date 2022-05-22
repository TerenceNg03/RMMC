#include "AST.hh"

using namespace rmmc;

std::string type_basic::to_xml(){
	return type.str();
}

std::string type_external::to_xml(){
	return name;
}

std::string type_array::to_xml(){
	std::string ret = "<array_type length=\""+ std::to_string(array_length) + "\">\n";
	ret += inner_type->to_xml();
	ret += "</array_type>";
	return ret;
}

std::string const_dummy::to_xml(){
	return "dummy const values";
}

std::string const_basic::to_xml(){
	std::string val = "";
	std::visit([&](auto&& arg){ val = std::to_string(arg);}, value);
	return val;
}

std::string const_array::to_xml(){
	std::string ret = "<array>\n";
	for(int i=0; i<values.size(); ++i){
		ret += values[i]->to_xml();
	}
	ret += "</array>";
	return ret;
}

std::string exp_dummy::to_xml(){
	return "dummy expression";
}

std::string exp_binary::to_xml(){

	std::string op_name;
	switch(op){
		case binary_op::comma: // ,
			op_name = ",";break;
		case binary_op::assign:// =
			op_name = "=";break;
		case binary_op::logical_or:// ||
			op_name = "||";break;
		case binary_op::logical_and:// &&
			op_name = "&amp;&amp;";break;
		case binary_op::bit_or:// |
			op_name = "|";break;
		case binary_op::bit_xor:// ^
			op_name = "^";break;
		case binary_op::bit_and:// &
			op_name = "&amp;";break;
		case binary_op::eq:// ==
			op_name = "==";break;
		case binary_op::neq:// !=
			op_name = "!=";break;
		case binary_op::gt:// >
			op_name = ">";break;
		case binary_op::lt:// <
			op_name = "<";break;
		case binary_op::ge:// >=
			op_name = ">=";break;
		case binary_op::le:// <=
			op_name = "<=";break;
		case binary_op::shift_left:// <<
			op_name = "<<";break;
		case binary_op::shift_right:// >>
			op_name = ">>";break;
		case binary_op::plus:// +
			op_name = "+";break;
		case binary_op::minus:// -
			op_name = "-";break;
		case binary_op::div:// /
			op_name = "/";break;
		case binary_op::mul:// *
			op_name = "*";break;
		case binary_op::mod:// %
			op_name = "%";break;
		case binary_op::subscript:// [  ]
			op_name = "[]";break;
		case binary_op::comp_ref:// .
			op_name = ".";break;
		case binary_op::comp_deref: // ->
			op_name = "->";break;
	}

	std::string ret = "<binary_operator_exp op=\"" +op_name+ "\">\n";
	ret += "<lhs>\n" + lhs->to_xml() + "</lhs>\n";
	ret += "<rhs>\n" + rhs->to_xml() + "</rhs>\n";
	ret += "</binary_operator_exp>\n";
	return ret;
}


std::string stat_break::to_xml(){
	return "<break />\n";
}

std::string stat_continue::to_xml(){
	return "<continue />\n";
}

std::string stat_dummy::to_xml(){
	return "<stat> dummy stat </stat>\n";
}

std::string exp_ternary::to_xml(){
	return "<stat> ternary not implemeted <stat/>";
}

std::string const_function::to_xml(){
	std::string ret = "<function>\n<parameters>\n";
	for(int i=0; i<parameters.size(); ++i){
		ret += parameters[i]->to_xml();
	}
	ret += "</parameters>\n";
	ret += "<return>\n" + (return_var ? return_var->to_xml() : "") + "</return>\n";
	ret += "<body>\n" + body->to_xml() + "</body>\n";
	ret += "</function>\n";

	return ret;
}

std::string exp_funct_call::to_xml(){
	std::string ret = "<call>\n<callable>\n";
	ret += callable->to_xml() + "</callable>\n";
	ret += "<parameters>\n";
	for(int i=0; i<parameters.size(); ++i){
		ret += parameters[i]->to_xml();
	}
	ret += "</parameters>\n</call>\n";
	return ret;
}

std::string stat_func_decl::to_xml(){
	std::string ret = "<parameter traits=\"";
	ret += traits.mut ? "mut " : "";
	ret += traits.ref ? "ref " : "";
	ret += traits.unique ? "unique " : "";
	ret += "\">\n<type>\n";
	if(type)ret += type->to_xml();
	else ret += "void";
	ret += "</type>\n</parameter>\n";
	return ret;
}

std::string exp_id::to_xml(){
	return id;
}

std::string exp_cast::to_xml(){
	std::string ret = "<cast>\n<type>\n";
	ret += cast_type->to_xml();
	ret += "</type>\n<expr>\n" + expr->to_xml() + "</expr>\n</cast>\n";
	return ret;
}

std::string stat_exp::to_xml(){
	return "<stat>\n" + expr->to_xml() + "</stat>\n";
}

std::string exp_const::to_xml(){
	return "<expr>\n" + value->to_xml() + "</expr>\n";
}

std::string stat_decl::to_xml(){
	std::string ret = "<decalration exportable=\"" + std::to_string(exportable) + "\" traits=\"";
	ret += traits.mut ? "mut " : "";
	ret += traits.ref ? "ref " : "";
	ret += traits.unique ? "unique " : "";
	ret += "\">\n";
	ret += "<name>" + var_name + "</name>";
	ret += "<type>\n" + (type? type->to_xml() : std::string("auto")) + "</type>\n";
	ret += "<initialize>\n" + (init_value ? init_value->to_xml() : std::string("")) + "</initialize>\n</decalration>\n";
	return ret;
}

std::string stat_ret::to_xml(){
	return ret_val ? "<return />" : "<return>\n" + ret_val->to_xml() + "</return>\n";
}

std::string exp_unary::to_xml(){
	std::string op_name;
	switch(op){
		case unary_op::addr_of: // &
			op_name = "&amp;";break;
		case unary_op::indirect: // *
			op_name = "*";break;
		case unary_op::pos: // +
			op_name = "+";break;
		case unary_op::neg: // -
			op_name = "-";break;
		case unary_op::bit_not: // ~
			op_name = "~";break;
		case unary_op::logical_not: // !
			op_name = "!";break;
		case unary_op::move: // move		
			op_name = "move";break;
	}
	return "<expression_unary op=\""+ op_name +"\">\n" + expr->to_xml() + "</expression_unary>\n";
}

std::string stat_block::to_xml(){
	std::string ret = "<code_block>\n";
	for(int i=0; i<stats.size(); ++i){
		ret += stats[i]->to_xml();
	}
	ret += "</code_block>\n";
	return ret;
}
