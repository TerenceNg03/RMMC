//
// Created by Yuying on 2022/5/3.
//

#ifndef __AST_H__
#define __AST_H__

#include <iostream>
#include <cstdlib>
#include <memory>
#include <vector>
#include <cstring>
#include <map>
#include <set>
#include "location.hh"
#include "rmm_types.hh"

namespace rmmc{

	class has_loc {
	public:
		location loc;
		has_loc(){};
		has_loc(location _loc);
		void set_loc(location _loc);
	};

	class has_type {
		public:
		rmm_type type;
		has_type (rmm_type _type);
		has_type ();
	};

	class AST_node {
		public:
		virtual std::string to_xml() = 0;
	};

	class Driver;
	struct context {
		struct variable {
			var_traits traits;
			rmm_type var_type;
			bool exportable;
		};

		unsigned long long anonymous_cnt = 0;

		struct custom_type {
			std::optional<rmm_type> real_type;
		};

		std::map<std::string, variable> variables;
		std::set<std::string> moved;
		std::map<std::string, custom_type> custom_types; 
		context* parent = nullptr;
		Driver* driver = nullptr;
		bool is_function_body = false;
		std::string context_tag;

		context(Driver* _driver);
		std::optional<variable> find_var_by_name(const std::string& name);
		std::optional<custom_type> find_type_by_name(const std::string& name);
		std::string find_return_tag();
		std::vector<std::string> find_dead_var(bool local); // var needs to be free, local block or return statement
	};

	struct emit_code {
		std::string decl;
		std::string exec;
		std::string name;
		emit_code();
		emit_code(std::string _decl, std::string _exec, std::string _name);
	};

	class emittable {
		public:
		virtual emit_code emit_c_code(context& cont) = 0;
	};
	
	/***** base class **************/

	class type_general : public has_loc, public AST_node {
		public:
		virtual std::string to_xml() = 0;
		virtual rmm_type get_type(const context& cont) = 0;
		virtual ~type_general(){};
	};


	class const_general : virtual public has_type ,public has_loc, public emittable, public AST_node{
		public:
		virtual std::string to_xml() = 0;
		virtual emit_code emit_c_code(context& cont) = 0;
		virtual ~const_general(){};
	};

	class exp_general : public has_loc, public has_type, virtual public emittable, public AST_node {
		protected:
		bool require_parentheses = false;
		exp_general(){};
		public:
		virtual std::string to_xml() = 0;
		void set_parentheses();
		virtual emit_code emit_c_code(context& cont) = 0;
		virtual ~exp_general(){};
	};

	class stat_general : public has_loc, virtual public emittable, public AST_node{
		public:
		virtual std::string to_xml() = 0;
		virtual emit_code emit_c_code(context& cont) = 0;
		virtual ~stat_general(){};
	};

	/***** type system *************/ 

	class type_basic : public type_general{
		rmm_type type;
		public:
		type_basic(rmm_type t);
		virtual rmm_type get_type(const context& cont);
		virtual std::string to_xml();
	};

	class type_external : public type_general {
		std::string name;
		public:
		type_external(std::string _name);
		virtual rmm_type get_type(const context& cont);
		virtual std::string to_xml();
	};

	class type_array : public type_general {
		std::unique_ptr<type_general> inner_type;
		size_t array_length;
		public:
		type_array(std::unique_ptr<type_general> _inner_type, size_t len);
		virtual rmm_type get_type(const context& cont);
		virtual std::string to_xml();
	};
	/***** type system ends here ***/

	/***** const value **************/

	class const_dummy : public const_general {
		public:
		const_dummy(){};
		const_dummy(const_dummy &&) = default;
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
		virtual ~const_dummy(){};
	};

	class const_basic : public const_general{
		std::variant<long long, double> value;
		public:
		const_basic(rmm_type _type, long long _value);
		const_basic(rmm_type _type, double _value);
		const_basic(const_basic &&) = default;
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
		virtual ~const_basic(){};
	};

	class const_array : public const_general{
		std::vector<std::unique_ptr<exp_general>> values;
		public:
		const_array(std::string str);
		const_array(std::vector<std::unique_ptr<exp_general>> _values);
		const_array(const_array&&) = default;
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
		virtual ~const_array(){};
	};

	/***** const ends here **********/
	/***** expression related *******/

	class exp_dummy : public exp_general, virtual public emittable{
		public:
		virtual emit_code emit_c_code(context& cont);			
		virtual std::string to_xml();
		virtual ~exp_dummy(){};
	};


	class exp_binary : public exp_general, virtual public emittable  {
		public:
		enum class binary_op {
			comma,	// ,
			assign, // =
			logical_or, // ||
			logical_and, // &&
			bit_or, // |
			bit_xor, // ^
			bit_and, // &
			eq, // ==
			neq, // !=
			gt, // >
			lt, // <
			ge, // >=
			le, // <=
			shift_left, // <<
			shift_right, // >>
			plus, // +
			minus, // -
			div, // /
			mul, // *
			mod, // %
			subscript, // [  ]
			comp_ref, // .
			comp_deref // ->
		};

		protected:
		binary_op op; // operator
		std::unique_ptr<exp_general> lhs; // left hand expression
		std::unique_ptr<exp_general> rhs; // right hand expression
		public:
		exp_binary(binary_op _op, std::unique_ptr<exp_general> _lhs, std::unique_ptr<exp_general> _rhs);
		exp_binary(exp_binary&&) = default;
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
		virtual ~exp_binary(){};
	};

	class exp_cast : public exp_general, virtual public emittable  {
		std::unique_ptr<exp_general> expr;
		std::unique_ptr<type_general> cast_type;
		public:
		exp_cast(std::unique_ptr<exp_general> _expr, std::unique_ptr<type_general> _type);
		exp_cast(exp_cast&&) = default;
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
		virtual ~exp_cast(){};
	};

	class exp_unary : public exp_general, virtual public emittable  {
		public:
		enum class unary_op {
			addr_of, // &
			indirect, // *
			pos, // +
			neg, // -
			bit_not, // ~
			logical_not, // !
			move // move
		};

		protected:
		unary_op op;
		std::unique_ptr<exp_general> expr;
		public:
		bool moved = false; //if this is a moved unique variable
		exp_unary(unary_op _op, std::unique_ptr<exp_general> _expr);
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
	};

	class exp_ternary : public exp_general, virtual public emittable  {
		std::unique_ptr<exp_general> condition;
		std::unique_ptr<exp_general> expr_true;
		std::unique_ptr<exp_general> expr_false;
		public:
		exp_ternary(std::unique_ptr<exp_general> _condition, std::unique_ptr<exp_general> _expr_true, std::unique_ptr<exp_general> _expr_false);
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
	};

	class exp_funct_call : public exp_general, virtual public emittable  {
		std::unique_ptr<exp_general> callable;
		std::vector<std::unique_ptr<exp_general>> parameters;
		public:
		exp_funct_call(std::unique_ptr<exp_general> _callable, std::vector<std::unique_ptr<exp_general>> _parameters);
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
	};

	class exp_id : public exp_general, virtual public emittable  {
		public:
		std::string id;
		exp_id(std::string _id);
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
	};

	class exp_const : public exp_general, virtual public emittable  {
		std::unique_ptr<const_general> value;
		public:
		exp_const(std::unique_ptr<const_general> _value);
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
	};

	/***** expression ends here *****/

	/***** statements here **********/

	class stat_dummy : public stat_general, virtual public emittable{
		public:
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
		virtual ~stat_dummy(){};	
	};

	class stat_decl : public stat_general, virtual public emittable{
		public:
		bool exportable;
		var_traits traits;
		std::string var_name;
		rmm_type real_type = make_u8();
		std::unique_ptr<type_general> type; // Nullable
		std::unique_ptr<exp_general> init_value; // Nullable
		stat_decl(bool _exportable, var_traits _traits, std::string name, std::unique_ptr<type_general> _type = nullptr, std::unique_ptr<exp_general> init = nullptr);
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
	};

	class stat_continue : public stat_general {
		public:
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
	};

	class stat_break : public stat_general {
		public:
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
	};

	class stat_ret : public stat_general {
		std::unique_ptr<exp_general> ret_val; // Nullable
		public:
		stat_ret(std::unique_ptr<exp_general> _ret_val);
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
	};

	class stat_func_decl : public stat_general, virtual public emittable{
		public:
		var_traits traits;
		std::string var_name; // May be "" (return value)
		rmm_type real_type = make_u8();
		std::unique_ptr<type_general> type; // Nullable
		stat_func_decl(var_traits _traits, std::string name, std::unique_ptr<type_general> _type);
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
	};

	class stat_exp : public stat_general {
		std::unique_ptr<exp_general> expr;
		public:
		stat_exp(std::unique_ptr<exp_general> _expr);
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
	};

	class stat_block : public has_loc{
		public:
		context stat_context;
		protected:
		std::vector<std::unique_ptr<stat_general>> stats;
		public:
		stat_block(Driver* driver, std::vector<std::unique_ptr<stat_general>> _stats);
		void set_parent_context(context* parent);
		std::string generate(std::string name = "", bool has_mark = true);
		virtual ~stat_block(){};
		virtual std::string to_xml();
	};

	class const_function : public const_general{
		std::vector<std::unique_ptr<stat_func_decl>> parameters;
		std::unique_ptr<stat_func_decl> return_var; // Nullable
		std::unique_ptr<stat_block> body;
		public:
		const_function(std::vector<std::unique_ptr<stat_func_decl>> _parameters, std::unique_ptr<stat_func_decl> _return_var, std::unique_ptr<stat_block> body);
		virtual emit_code emit_c_code(context& cont);
		virtual std::string to_xml();
	};

	/***** statements ends here *****/

}

#endif
