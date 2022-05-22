#include "AST.hh"

using namespace rmmc;

has_loc::has_loc(location _loc): loc(_loc){};

void has_loc::set_loc(location _loc){ loc = _loc; };

has_type::has_type (rmm_type _type): type(_type){};

has_type::has_type (): type(make_u8()){};

type_basic::type_basic(rmm_type t): type(t){};
rmm_type type_basic::get_type(const context& cont){
	return type;
}

type_external::type_external(std::string _name): name(_name){};
rmm_type type_external::get_type(const context& cont){
	std::cout<<"external type not supported yet!\n";
	return make_u8();
}

type_array::type_array(std::unique_ptr<type_general> _inner_type, size_t len): inner_type(std::move(_inner_type)), array_length(len){};
rmm_type type_array::get_type(const context& cont){
	return make_array(inner_type->get_type(cont), array_length);
}

const_basic::const_basic(rmm_type _type, long long _value): has_type(_type), value(_value){};
const_basic::const_basic(rmm_type _type, double _value): has_type(_type), value(_value){};

const_array::const_array(std::string str): has_type(make_u8()){
	for(auto c: str){
		std::unique_ptr<const_general> cons = std::make_unique<const_basic>(const_basic(make_u8(), (long long)c));
		std::unique_ptr<exp_general> exp = std::make_unique<exp_const>(exp_const(std::move(cons)));
		values.push_back(std::move(exp));
	}
};
const_array::const_array(std::vector<std::unique_ptr<exp_general>> _values) {
	values = std::move(_values);
};

void exp_general::set_parentheses(){
	require_parentheses = true;
};

exp_binary::exp_binary(binary_op _op, std::unique_ptr<exp_general> _lhs, std::unique_ptr<exp_general> _rhs): op(_op), lhs(std::move(_lhs)), rhs(std::move(_rhs)){};

exp_cast::exp_cast(std::unique_ptr<exp_general> _expr, std::unique_ptr<type_general> _type): expr(std::move(_expr)), cast_type(std::move(_type)){};

exp_unary::exp_unary(unary_op _op, std::unique_ptr<exp_general> _expr): op(_op), expr(std::move(_expr)){};

exp_ternary::exp_ternary(std::unique_ptr<exp_general> _condition, std::unique_ptr<exp_general> _expr_true, std::unique_ptr<exp_general> _expr_false): condition(std::move(_condition)), expr_true(std::move(_expr_true)), expr_false(std::move(_expr_false)){};

exp_funct_call::exp_funct_call(std::unique_ptr<exp_general> _callable, std::vector<std::unique_ptr<exp_general>> _parameters): callable(std::move(_callable)), parameters(std::move(_parameters)){};

exp_id::exp_id(std::string _id): id(_id){};

exp_const::exp_const(std::unique_ptr<const_general> _value): value(std::move(_value)){ type = make_i64(); };

stat_decl::stat_decl(bool _exportable, var_traits _traits, std::string name, std::unique_ptr<type_general> _type, std::unique_ptr<exp_general> init): exportable(_exportable), traits(_traits), var_name(name), type(std::move(_type)), init_value(std::move(init)){};
	
stat_ret::stat_ret(std::unique_ptr<exp_general> _ret_val): ret_val(std::move(_ret_val)) {};

stat_func_decl::stat_func_decl(var_traits _traits, std::string name, std::unique_ptr<type_general> _type): traits(_traits), var_name(name), type(std::move(_type)){};

const_function::const_function(std::vector<std::unique_ptr<stat_func_decl>> _parameters, std::unique_ptr<stat_func_decl> _return_var, std::unique_ptr<stat_block> _body) : parameters(std::move(_parameters)), return_var(std::move(_return_var)), body(std::move(_body)){};

stat_exp::stat_exp(std::unique_ptr<exp_general> _expr): expr(std::move(_expr)){};

stat_block::stat_block(Driver* driver, std::vector<std::unique_ptr<stat_general>> _stats) : stat_context(driver), stats(std::move(_stats)){};
