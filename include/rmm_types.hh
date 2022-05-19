#ifndef RMM_TYPES_HH
#define RMM_TYPES_HH

#include <variant>
#include <vector>
#include <utility>
#include <string>
#include <memory>
#include <optional>
#include <iostream>


namespace rmmc{

	enum class basic_type{
		u8, u16, u32, u64,
		i8, i16, i32, i64,
		f32, f64,
		boolean
	};

	typedef std::pair<std::string, std::string> c_type_name;

	class rmm_type;

	struct var_traits{
		bool mut;
		bool ref;
		bool unique;
		public:
		var_traits(const bool mut, const bool ref, const bool unique);
		var_traits(const var_traits& var_t);
		std::string str() const;
		bool operator==(const var_traits& v) const;
		~var_traits();

	};

	class array_type{
		size_t length;
		public:
		rmm_type* content_type;
		array_type(const size_t length, const rmm_type& t);
		array_type(const array_type& arr_t);
		bool operator==(const array_type& x) const;
		array_type& operator =(const array_type& b) = delete;
		std::string str() const;
		c_type_name to_c_type() const;
		~array_type();
	};

	class compound_type{
		std::vector<std::tuple<var_traits, rmm_type*, std::string>> type_list;
		std::string name;
		public:
		compound_type(const std::string& name, const std::vector<std::tuple<var_traits, std::string, rmm_type>>& t);
		compound_type(const compound_type& t);
		std::string get_name() const;
		/* only compare name */
		bool operator==(const compound_type& x) const;
		compound_type& operator=(const compound_type& x) = delete;
		std::string str() const;
		c_type_name to_c_type() const;
		~compound_type();
	};

	class pointer_type{
		rmm_type* content_type;
		public:
		pointer_type(const rmm_type& t);
		pointer_type(const pointer_type& t);
		bool operator==(const pointer_type& x) const;
		pointer_type& operator=(const pointer_type& x) = delete;
		std::string str() const;
		c_type_name to_c_type() const;
		~pointer_type();
	};

	class function_type{
		std::vector<std::pair<var_traits, rmm_type*>> parameters;
		var_traits return_traits;
		rmm_type* return_type; //null if is void
		public:
		function_type(const std::vector<std::pair<var_traits, rmm_type>>& pars, const var_traits& return_traits, const std::optional<rmm_type>& ret);
		function_type(const function_type& t);
		bool operator==(const function_type& x) const;
		function_type& operator=(const function_type& x) = delete;
		std::string str() const;
		c_type_name to_c_type() const;
		~function_type();
	};

	class union_type{
		std::vector<std::tuple<var_traits, rmm_type*, std::string>> type_list;
		std::string name;
	public:
		union_type(const std::string& name, const std::vector<std::tuple<var_traits, std::string, rmm_type>>& t);
		union_type(const union_type& t);
		std::string get_name() const;
		/* only compare name */
		bool operator==(const union_type& x) const;
		union_type& operator=(const union_type& x) = delete;
		std::string str() const;
		c_type_name to_c_type() const;
		~union_type();
	};

	/* this class represents all possible variable type */
	class rmm_type{
		public:
		enum class TAG{
			basic,
			array,
			compound,
			union_,
			pointer,
			function
		};
		TAG tag;

		std::variant<array_type, compound_type, pointer_type, function_type, basic_type, union_type> content;
		rmm_type(const array_type& t);
		rmm_type(const compound_type& t);
		rmm_type(const pointer_type& t);
		rmm_type(const function_type& t);
		rmm_type(const union_type& t);
		rmm_type(const basic_type& t);
		rmm_type(const rmm_type & t);

		bool operator==(const rmm_type& x) const;
		bool operator!=(const rmm_type& x) const;
		rmm_type& operator=(const rmm_type& t);

		std::string str() const;
		c_type_name to_c_type() const;
		TAG get_tag() const;

		bool is_int();
		bool is_float();
		bool is_bool();
		bool is_func();
		bool is_comp();
		bool is_union();
		bool is_ptr();
		bool is_array();

		~rmm_type();
	};

	/* utility: make_types */
	rmm_type make_u8(void);
	rmm_type make_u16(void);
	rmm_type make_u32(void);
	rmm_type make_u64(void);
	rmm_type make_i8(void);
	rmm_type make_i16(void);
	rmm_type make_i32(void);
	rmm_type make_i64(void);
	rmm_type make_f32(void);
	rmm_type make_f64(void);
	rmm_type make_bool(void);

	/* Accepts a iterator with type std::tuple<var_traits, std::string, rmm_type> */
	template <
		typename Iter,
		std::enable_if_t<(std::is_same<typename std::iterator_traits<Iter>::value_type, std::tuple<var_traits, std::string, rmm_type>>::value), std::nullptr_t> = nullptr
	>
	rmm_type make_comp(std::string name ,Iter begin, Iter end)
	{
		std::vector<std::tuple<var_traits, std::string, rmm_type>> tv;
		Iter k = begin;
		while (k != end)
		{
			tv.push_back(*k);
			++k;
		}
		compound_type t = compound_type(name, tv);
		rmm_type x = rmm_type(t);
		return x;
	}
	

	/* Accepts a iterator with type std::tuple<var_traits, std::string, rmm_type> */
	template <
		typename Iter,
		std::enable_if_t<(std::is_same<typename std::iterator_traits<Iter>::value_type, std::tuple<var_traits, std::string, rmm_type>>::value), std::nullptr_t> = nullptr
	>
	rmm_type make_union(std::string name, Iter begin, Iter end){
		std::vector<std::tuple<var_traits, std::string, rmm_type>> tv;
		Iter k = begin;
		while (k != end)
		{
			tv.push_back(*k);
			++k;
		}
		union_type t = union_type(name, tv);
		rmm_type x = rmm_type(t);
		return x;
	}
	

	/* normal array */
	rmm_type make_array(const rmm_type& inner_type, size_t array_size);
	/* variable length array */
	rmm_type make_array(const rmm_type& inner_type);

	/* return if invalid */
	std::optional<var_traits> make_traits(bool mut, bool ref, bool unique) noexcept;
	var_traits make_traits() noexcept;

	/* Accept a Iterator with type std::pair<var_traits, rmm_type> */
	template <
		typename Iter,
		std::enable_if_t<(std::is_same<typename std::iterator_traits<Iter>::value_type, std::pair<var_traits , rmm_type>>::value), std::nullptr_t> = nullptr
	>
	rmm_type make_function(Iter para_begin, Iter para_end, const var_traits& ret_traits,const std::optional<rmm_type> return_type){
		std::vector<std::pair<var_traits, rmm_type>> tv;
		Iter k = para_begin;
		while (k != para_end)
		{
			tv.push_back(*k);
			++k;
		}
		
		function_type t(tv, ret_traits, return_type);
		return t;
	}
	

	rmm_type make_pointer(const rmm_type& t);

}

#endif
