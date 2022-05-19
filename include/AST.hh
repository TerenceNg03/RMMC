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
		std::map<std::string, custom_type> custom_types; 
		context* parent = nullptr;
		Driver* driver = nullptr;

		context(Driver* _driver);
		std::optional<variable> find_var_by_name(const std::string& name);
		std::optional<custom_type> find_type_by_name(const std::string& name);
	};

	struct emit_code {
		std::string decl;
		std::string exec;
		emit_code();
		emit_code(std::string _decl, std::string _exec);
	};

	class emittable {
		public:
		virtual emit_code emit_c_code(context& cont) = 0;
	};
	
	/***** type system *************/ 

	class type_general : public has_loc {
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

	class const_general : virtual public has_type ,public has_loc, public emittable{
		public:
		virtual emit_code emit_c_code(context& cont) = 0;
		virtual ~const_general(){};
	};

	class const_basic : public const_general{
		std::variant<long long, double> value;
		public:
		const_basic(rmm_type _type, long long _value);
		const_basic(rmm_type _type, double _value);
		const_basic(const_basic &&) = default;
		virtual emit_code emit_c_code(context& cont);
		virtual ~const_basic(){};
	};

	class const_array : public const_general{
		std::vector<std::unique_ptr<const_general>> values;
		public:
		const_array(std::string str);
		const_array(rmm_type inner_type, std::vector<std::unique_ptr<const_general>> _values);
		const_array(const_array&&) = default;
		virtual emit_code emit_c_code(context& cont);
		virtual ~const_array(){};
	};

	/***** const ends here **********/
	/***** expression related *******/

	class exp_general : public has_loc, public has_type, virtual public emittable {
		protected:
		bool require_parentheses = false;
		exp_general(){};
		public:
		void set_parentheses();
		virtual emit_code emit_c_code(context& cont) = 0;
		virtual ~exp_general(){};
	};

	class exp_dummy : public exp_general, virtual public emittable{
		public:
		virtual emit_code emit_c_code(context& cont);			
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
		virtual ~exp_binary(){};
	};

	class exp_cast : public exp_general, virtual public emittable  {
		std::unique_ptr<exp_general> expr;
		std::unique_ptr<type_general> cast_type;
		public:
		exp_cast(std::unique_ptr<exp_general> _expr, std::unique_ptr<type_general> _type);
		exp_cast(exp_cast&&) = default;
		virtual emit_code emit_c_code(context& cont);
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
		exp_unary(unary_op _op, std::unique_ptr<exp_general> _expr);
		virtual emit_code emit_c_code(context& cont);
	};

	class exp_ternary : public exp_general, virtual public emittable  {
		std::unique_ptr<exp_general> condition;
		std::unique_ptr<exp_general> expr_true;
		std::unique_ptr<exp_general> expr_false;
		public:
		exp_ternary(std::unique_ptr<exp_general> _condition, std::unique_ptr<exp_general> _expr_true, std::unique_ptr<exp_general> _expr_false);
		virtual emit_code emit_c_code(context& cont);
	};

	class exp_funct_call : public exp_general, virtual public emittable  {
		std::unique_ptr<exp_general> callable;
		std::vector<std::unique_ptr<exp_general>> parameters;
		public:
		exp_funct_call(std::unique_ptr<exp_general> _callable, std::vector<std::unique_ptr<exp_general>> _parameters);
		virtual emit_code emit_c_code(context& cont);
	};

	class exp_id : public exp_general, virtual public emittable  {
		std::string id;
		public:
		exp_id(std::string _id);
		virtual emit_code emit_c_code(context& cont);
	};

	class exp_const : public exp_general, virtual public emittable  {
		std::unique_ptr<const_general> value;
		public:
		exp_const(std::unique_ptr<const_general> _value);
		virtual emit_code emit_c_code(context& cont);
	};

	/***** expression ends here *****/

	/***** statements here **********/

	class stat_general : public has_loc, virtual public emittable{
		public:
		virtual emit_code emit_c_code(context& cont) = 0;
		virtual ~stat_general(){};
	};

	class stat_dummy : public stat_general, virtual public emittable{
		public:
		virtual emit_code emit_c_code(context& cont);
		virtual ~stat_dummy(){};	
	};

	class stat_decl : public stat_general, virtual public emittable{
		bool exportable;
		var_traits traits;
		std::string var_name;
		std::unique_ptr<type_general> type;
		std::unique_ptr<exp_general> init_value; // Nullable
		public:
		stat_decl(bool _exportable, var_traits _traits, std::string name, std::unique_ptr<type_general> _type, std::unique_ptr<exp_general> init = nullptr);
		virtual emit_code emit_c_code(context& cont);
	};

	class stat_block : public has_loc, public emittable {
		protected:
		context stat_context;
		std::vector<std::unique_ptr<stat_general>> stats;
		public:
		stat_block(Driver* driver, std::vector<std::unique_ptr<stat_general>> _stats);
		virtual emit_code emit_c_code(context& cont);
		virtual ~stat_block(){};
	};



	/***** statements ends here *****/

}

#endif
