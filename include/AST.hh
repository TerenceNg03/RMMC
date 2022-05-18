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
#include "location.hh"
#include "rmm_types.hh"

namespace rmmc{

	class AST_node {
		protected:
			location loc;
			AST_node(){};
			AST_node(location _loc);
			//virtual void analyze() = 0;
	};

	class AST_node_dummy {

	};

	class has_type {
		protected:
			rmm_type type;
		public:
			has_type (rmm_type _type);
			has_type ();
	};

	struct context {
		struct variable {
			var_traits traits;
			rmm_type var_type;
			bool exportable;
		};

		struct custom_type {
			std::optional<rmm_type> real_type;
		};

		std::map<std::string, variable> variables;
		std::map<std::string, custom_type> custom_types; 
		context* parent = nullptr;

	};
	
	/***** type system *************/ 

	class type_general : public AST_node {
		public:
		virtual rmm_type get_type(const context& cont) = 0;
		virtual ~type_general(){};
	};

	class type_basic : public type_general {
		rmm_type type;
		public:
		type_basic(rmm_type t);
		virtual rmm_type get_type(const context& cont);
	};

	class type_external : public type_general {
		std::string name;
		public:
		type_external(std::string _name);
		virtual rmm_type get_type(const context& cont);
	};

	class type_array : public type_general {
		std::unique_ptr<type_general> inner_type;
		size_t array_length;
		public:
		type_array(std::unique_ptr<type_general> _inner_type, size_t len);
		virtual rmm_type get_type(const context& cont);
	};
	/***** type system ends here ***/

	/***** const value **************/

	class const_general : public AST_node{

	};

	class const_basic : public const_general{
		rmm_type type;
		std::variant<long long, double> value;
		public:
		const_basic(rmm_type _type, long long _value);
		const_basic(rmm_type _type, double _value);
	};

	class const_array : public const_general{
		std::vector<std::unique_ptr<const_general>> values;
		rmm_type type;
		public:
		const_array(std::string str);
		const_array(rmm_type inner_type, std::vector<std::unique_ptr<const_general>> _values);
	};

	/***** const ends here **********/
	/***** expression related *******/

	class exp_general : public AST_node, public has_type {
		protected:
		bool require_parentheses = false;
		bool analyzed = false;
		exp_general(){};
		public:
		void set_parentheses();

	};

	class exp_dummy : public exp_general {};


	class exp_binary : public exp_general {
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
	};

	class exp_cast : public exp_general {
		std::unique_ptr<exp_general> expr;
		std::unique_ptr<type_general> cast_type;
		public:
		exp_cast(std::unique_ptr<exp_general> _expr, std::unique_ptr<type_general> _type);
	};

	class exp_unary : public exp_general {
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
		exp_unary(unary_op _op, std::unique_ptr<exp_general> _expr);
	};

	class exp_ternary : public exp_general {
		std::unique_ptr<exp_general> condition;
		std::unique_ptr<exp_general> expr_true;
		std::unique_ptr<exp_general> expr_false;
		public:
		exp_ternary(std::unique_ptr<exp_general> _condition, std::unique_ptr<exp_general> _expr_true, std::unique_ptr<exp_general> _expr_false);
	};

	class exp_funct_call : public exp_general {
		std::unique_ptr<exp_general> callable;
		std::vector<std::unique_ptr<exp_general>> parameters;
		public:
		exp_funct_call(std::unique_ptr<exp_general> _callable, std::vector<std::unique_ptr<exp_general>> _parameters);
	};

	class exp_id : public exp_general {
		std::string id;
		public:
		exp_id(std::string _id);
	};

	class exp_const : public exp_general {
		std::unique_ptr<const_general> value;
		public:
		exp_const(std::unique_ptr<const_general> _value);
	};

	/***** expression ends here *****/

	/***** statements here **********/

	class stat_general : public AST_node{

	};

	class stat_dummy : public stat_general {};

	class stat_decl : public stat_general{
		bool exportable;
		var_traits traits;
		std::string var_name;
		std::unique_ptr<type_general> type;
		std::unique_ptr<exp_general> init_value; // Nullable
		public:
		stat_decl(bool _exportable, var_traits _traits, std::string name, std::unique_ptr<type_general> _type, std::unique_ptr<exp_general> init = nullptr);
	};

	class stat_block : public AST_node {
		protected:
		context stat_context;
		std::vector<std::unique_ptr<stat_general>> stats;
		public:
		stat_block(std::vector<std::unique_ptr<stat_general>> _stats);
	};



	/***** statements ends here *****/

}

#endif
