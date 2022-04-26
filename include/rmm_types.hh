#include <variant>
#include <vector>
#include <utility>
#include <string>
#include <memory>


namespace rmmc{

	enum class basic_type{
		u8, u16, u32, u64,
		i8, i16, i32, i64,
		f32, f64,
		boolean
	};

	class rmm_type;

	class array_type{
		size_t length;
		rmm_type* content_type;
		public:
		array_type(const size_t length, const rmm_type& t);
		array_type(const array_type& arr_t);
		bool operator==(const array_type& x);
		~array_type();
	};

	class compound_type{
		std::vector<std::pair<rmm_type*, std::string>> type_list;
		std::string name;
		public:
		compound_type(const std::string& name, const std::vector<std::pair<rmm_type, std::string>>& t);
        compound_type(const compound_type& t);
		std::string get_name() const;
		/* only compare name */
		bool operator==(const compound_type& x);
		~compound_type();
	};

	class pointer_type{
		rmm_type* content_type;
		public:
		pointer_type(const rmm_type& t);
		pointer_type(const pointer_type& t);
		bool operator==(const pointer_type& x);
		~pointer_type();
	};

	class function_type{
		std::vector<rmm_type*> parameters;
		rmm_type* return_type;
		public:
		function_type(const std::vector<rmm_type>& pars, const rmm_type& ret);
		function_type(const function_type& t);
		bool operator==(const function_type& x);
		~function_type();
	};

	/* this class represents all possible variable type */
	class rmm_type{

		enum class TAG{
			basic,
			array,
			compound,
			pointer,
			function
		};

		TAG tag;

		union{
			array_type arr;
			compound_type comp;
			pointer_type ptr;
			function_type func;
			basic_type bas;
		};
		public:
		rmm_type(const array_type& t);
		rmm_type(const compound_type& t);
		rmm_type(const pointer_type& t);
		rmm_type(const function_type& t);
		rmm_type(const basic_type& t);
		rmm_type(const rmm_type & t);

		bool operator==(const rmm_type& x);
		bool operator!=(const rmm_type& x);
		
		~rmm_type();
	};

}
