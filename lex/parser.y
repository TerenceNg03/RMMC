%skeleton "lalr1.cc"

%{
#include <stdio.h>
#include <string>
#include "parser.hh"
#include "scanner.hh"
#include <fstream>
#define yylex driver.scanner->lex
%}

%code requires{
	#include "driver.hh"
	#include "location.hh"
	#include "position.hh"
	#include "rmm_types.hh"
	#include "rmm_utility.hh"
	#include "AST.hh"

	using namespace rmmc;
	typedef exp_binary::binary_op binary_op;
	typedef exp_unary::unary_op unary_op;
}

%code provides
{

namespace rmmc
	{
		// Forward declaration of the Driver class
		class Driver;

inline void
		yyerror (const char* msg)
		{
			std::cout << msg << "\n";
		}
	}

}

%locations
%define api.namespace {rmmc}
%define api.parser.class {Parser}
%lex-param {rmmc::Driver &driver}
%parse-param {rmmc::Driver &driver}
%define parse.error verbose
%language "c++"
%define api.value.type variant
%define api.token.constructor

%token
let "keyword let"
var "keyword var"
mut "keyword mut"
as "keyword as"
break_ "keyword break"
return_ "keyword return"
continue_ "keyword continue"
use "keyword use"
for_ "keyword for" 
while_ "keyword while"
void_ "keyword void"
auto_ "keyword auto"
if_ "keyword if" 
else_ "keyword else" 
elif "keyword elif"
bool_ "keyword bool"
true_ "keyword true"
false_ "keyword false"
import_ "keyword import"
from "keyword from"
export_ "keyword export"
mod "keyword mod"
type "keyword type"
comp "keyword comp"
u8 "keyword u8"
u16 "keyword u16"
u32 "keyword u32"
u64 "keyword u64"
i8 "keyword i8"
i16 "keyword i16"
i32 "keyword i32"
i64 "keyword i64"
f32 "keyword f32"
f64 "keyword f64"
nullptr_ "nullptr"
move "keyword move"
unique "keyword unique"
union_ "keyword union"
ref "keyword ref"
match "keyword match"

%token

unknown "unknown character"
eof "end of file"

%token<std::string> rawid "identifier"
rawstr "string"
rawchar "character"

%token <long long> long_ "integer constant"

%token <double> float_ " float constant"

%token
minus "-"
plus "+"
div "/"
mul "*"
assign "="

roundbl "("
roundbr ")"
boxbl "["
boxnr "]"
curlybl "{"
curlybr "}"
lt "<"
gt ">"
ge ">="
le "<="
shiftright ">>"
shiftleft "<<"
eq "=="
noteq "!="
point "."
leftarror "->"
colon ":"
comma ","
doublecolon "::"

bitand_ "&"
bitor_ "|"
bitxor_ "^"
bitnot_ "~"
semicolon ";"

and_ "&&"
or_ "||"
not_ "!"

math_mod "%"
q_mark "?"

%left
"::"
"."
"->"
as

%right
"!"
"~"

%type <std::string> str var_name id
%type <std::unique_ptr<const_general>> const_value array_literal function_literal
%type <std::vector<std::unique_ptr<stat_general>>> STATEMENTS function_body
%type <std::unique_ptr<stat_general>> STATEMENT declare_statement function_statement jump_statement // import_statement type_statement mod_statement use_statement 
%type <bool> declare opt_export
%type <char> character
%type <std::unique_ptr<type_general>> typename
%type <std::unique_ptr<rmm_type>> basictype
%type <std::unique_ptr<exp_general>> exp assignment_exp conditional_exp logical_or_exp logical_and_exp inclusive_or_exp exclusive_or_exp and_exp equality_exp relational_exp shift_expression additive_exp mult_exp cast_exp unary_exp postfix_exp primary_exp 
%type <unary_op> unary_operator
%type <std::vector<std::unique_ptr<exp_general>>> argument_exp_list init_list_array
%type <var_traits> func_para_traits variable_traits
%type <int> func_para_trait variable_trait
%type <std::unique_ptr<stat_func_decl>> parameter_decl
%type <std::vector<std::unique_ptr<stat_func_decl>>> parameters_list
%type <std::unique_ptr<stat_block>> function_body_stat


%%
STATEMENTS:
/* empty */
{
#if DEBUG
	std::cout<<"[DEBUG] Parsing step started\n";
#endif
}
| STATEMENTS STATEMENT 
{
	$1.push_back(std::move($2));
	$$ = std::move($1);
}
| STATEMENTS eof
{
#if DEBUG
	if(!driver.get_error_count())std::cout<<"[DEBUG] Parsing step succeeded with no error\n";
#endif
	if(driver.get_error_count())std::cout<<"\033[1;31mAborting\033[0m: \033[1;31m"<<driver.get_error_count()<<" fatal errors \033[0mencountered.\n";
	driver.ast_root = std::make_unique<stat_block>(&driver, std::move($1));
	YYACCEPT;
}


STATEMENT:
";" { $$ = std::make_unique<stat_dummy>(stat_dummy()); }
| declare_statement ";" { $$ = std::move($1); }
| import_statement ";" { $$ = std::make_unique<stat_dummy>(stat_dummy()); }
| type_statement ";" { $$ = std::make_unique<stat_dummy>(stat_dummy()); }
| mod_statement ";" { $$ = std::make_unique<stat_dummy>(stat_dummy()); }
| use_statement ";" { $$ = std::make_unique<stat_dummy>(stat_dummy()); }
| error_statement { $$ = std::make_unique<stat_dummy>(stat_dummy()); }

/* assign statement */
declare_statement:
declare opt_export variable_traits id ":" typename_incomplete "=" exp
{
	$$ = std::make_unique<stat_decl>(stat_decl($2, $3, $4, nullptr, std::move($8))); 
	$$->loc = @7;
}
| declare opt_export variable_traits id ":" typename "=" exp
{
	$$ = std::make_unique<stat_decl>(stat_decl($2, $3, $4, std::move($6), std::move($8)));
	$$->loc = @7;
}
| declare opt_export variable_traits id ":" typename 
{
	$$ = std::make_unique<stat_decl>(stat_decl($2, $3, $4, std::move($6)));
}
| opt_export comp id
{
	$$ = std::make_unique<stat_dummy>(stat_dummy()); 
}
| opt_export union_ id
{
	$$ = std::make_unique<stat_dummy>(stat_dummy()); 
}
| declare opt_export variable_traits id ":" typename_incomplete
{
	error(@6, "Incomplete type must have an initial value");
	$$ = std::make_unique<stat_dummy>(stat_dummy()); 
}
| declare opt_export variable_traits id
{
	error(@4, "Type must be specified");
	$$ = std::make_unique<stat_dummy>(stat_dummy()); 
}

/* declare keyword*/
declare:
let { $$ = false; }
| var { $$ = true; }

/* string preprocess */
str: rawstr
{
	$$ = str_process($1);	
}

character: rawchar
{
	std::string __tmp =  str_process($1);
	if(__tmp.length() != 1){
		error(@1, "Invalid char litheral : " + $1);
		$$ = '\0';
	}else{
		$$ = __tmp[0];
	}
}

id: rawid {
	$$ = "";
	for(auto c: $1){
		if(c=='_') $$ += "__";
		else $$ += c;
	}
}

/* variable trait*/
variable_traits:
{}
| variable_traits variable_trait
 {
	$$ = $1;
	if($2 == 1){
		$$.ref = true;
		if($$.unique) error(@2, "Traits confilct detected.");
	}
	if($2 == 2){
		$$.unique = true;
		if($$.ref) error(@2, "Traits confilct detected.");
	}

 }


variable_trait:
unique { $$ = 2; }
| ref { $$ = 1; }

/* namespace */
var_name: 
var_name "::" id { $$ = $1 + "_" + $3; }
| id { $$ = $1; }

/* This part deal with init value */

const_value:
long_
{
	$$ = std::make_unique<const_basic>(const_basic(::make_i64(), $1));
	$$->loc = @1;
}
| float_
{
	$$ = std::make_unique<const_basic>(const_basic(::make_f64(), $1));
	$$->loc = @1;
}
| str
{
	$$ = std::make_unique<const_array>(const_array($1));
	$$->loc = @1;
}
| character
{
	$$ = std::make_unique<const_basic>(const_basic(::make_u8(), (long long)$1));
	$$->loc = @1;
}
| true_
{
	$$ = std::make_unique<const_basic>(const_basic(::make_bool(), (long long)1));
	$$->loc = @1;
}
| false_
{
	$$ = std::make_unique<const_basic>(const_basic(::make_bool(), (long long)1));
	$$->loc = @1;
}
| nullptr_
{
	$$ = std::make_unique<const_basic>(const_basic(::make_u8(), (long long)0));
	$$->loc = @1;
}


/* This part deal with typename */
typename_incomplete:
| auto_
/*
| "[" typename "," "]"
| "[" typename "," var_name "]" */

typename:
"[" typename "," long_ "]"
{
	$$ = std::make_unique<type_array>(type_array(std::move($2), $4));
	$$->loc = @$;
}
| "*" typename
{
	$$ = std::make_unique<type_basic>(type_basic(::make_u8()));
	$$->loc = @$;
}
| "(" func_para_typelist ")" "->" func_para_traits typename
{
	$$ = std::make_unique<type_basic>(type_basic(::make_u8()));
	$$->loc = @$;
}
| "(" void_ ")" "->" func_para_traits typename
{
	$$ = std::make_unique<type_basic>(type_basic(::make_u8()));
	$$->loc = @$;
}
| "(" func_para_typelist ")" "->" void_
{
	$$ = std::make_unique<type_basic>(type_basic(::make_u8()));
	$$->loc = @$;
}
| "(" void_ ")" "->" void_
{
	$$ = std::make_unique<type_basic>(type_basic(::make_u8()));
	$$->loc = @$;
}
| basictype
{
	$$ = std::make_unique<type_basic>(type_basic(*$1));
	$$->loc = @$;
}
| var_name /* defined by type keyword */
{
	$$ = std::make_unique<type_external>(type_external($1));
	$$->loc = @$;
}
| comp_type
{
	$$ = std::make_unique<type_basic>(type_basic(::make_u8()));
	$$->loc = @$;
}
| union_type
{
	$$ = std::make_unique<type_basic>(type_basic(::make_u8()));
	$$->loc = @$;
}


comp_type:
comp id "{" comp_decl_list "}" /* named comp */

union_type:
union_ id "{" comp_decl_list "}"

comp_decl_list:
/* empty */
| comp_decl_list comp_decl_item

comp_decl_item:
func_para_traits id ":" typename ";"
| func_para_traits id "::" var_name ":" typename ";"
{
	error(@2, "Qualified id not allowed here");
}

func_para_typelist:
func_para_typelist "," func_para_traits typename
| func_para_traits typename

func_para_traits: { $$ = make_traits(); }
| func_para_traits func_para_trait
{
	$$ = $1;
	if($2 == 1){ $$.mut = true; }
	if($2 == 2){ 
		$$.ref = true; 
		if($$.unique) error(@2, "Conflict traits detected");
	}
	if($2 == 4){ 
		$$.unique = true; 
		if($$.ref) error(@2, "Conflict traits detected");
	}
}

func_para_trait:
unique { $$ = 4; }
| ref { $$ = 2; }
| mut { $$ = 1; }

basictype:
bool_ { $$ = std::make_unique<rmm_type>(::make_bool());}
| u8 { $$ = std::make_unique<rmm_type>(::make_u8());}
| u16 { $$ = std::make_unique<rmm_type>(::make_u16());}
| u32 { $$ = std::make_unique<rmm_type>(::make_u32());}
| u64 { $$ = std::make_unique<rmm_type>(::make_u64());}
| i8 { $$ = std::make_unique<rmm_type>(::make_i8());}
| i16 { $$ = std::make_unique<rmm_type>(::make_i16());}
| i32 { $$ = std::make_unique<rmm_type>(::make_i32());}
| i64 { $$ = std::make_unique<rmm_type>(::make_i64());}
| f32 { $$ = std::make_unique<rmm_type>(::make_f32());}
| f64 { $$ = std::make_unique<rmm_type>(::make_f64());}

/* import statement */
import_statement:
from var_name import_ var_name
| from str import_ var_name
| import_ var_name
| import_ str

/* type statement */
type_statement:
type opt_export id typename
| opt_export comp_type
| opt_export union_type

opt_export:
 { $$ = false; }/* empty */
| export_ { $$ = true; }

/* mod_statement */ 
mod_statement:
mod id "{" inmod_satements "}"

inmod_satements:
/* empty */
| inmod_satements inmod_satement

inmod_satement:
declare_statement ";"
| type_statement ";"
| mod_statement ";"
| use_statement ";"
| error_statement

/* use_statement */
use_statement:
use var_name

/* expression */ 
exp: assignment_exp { $$ = std::move($1); }
| exp "," assignment_exp 
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::comma, std::move($1), std::move($3)));
	$$->loc = @2;
}

assignment_exp: conditional_exp { $$ = std::move($1); }
| unary_exp "=" assignment_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::assign, std::move($1), std::move($3)));
	$$->loc = @2;
}

conditional_exp: logical_or_exp { $$ = std::move($1); }
| logical_or_exp "?" exp ":" conditional_exp
{ 
	$$ = std::make_unique<exp_ternary>(exp_ternary(std::move($1), std::move($3), std::move($5)));
	$$->loc = @2;
}

logical_or_exp: logical_and_exp { $$ = std::move($1); }
| logical_or_exp "||" logical_and_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::logical_or, std::move($1), std::move($3)));
	$$->loc = @2;
}

logical_and_exp: inclusive_or_exp { $$ = std::move($1); }
| logical_and_exp "&&" inclusive_or_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::logical_and, std::move($1), std::move($3)));
	$$->loc = @2;
}

inclusive_or_exp: exclusive_or_exp { $$ = std::move($1); }
| inclusive_or_exp "|" exclusive_or_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::bit_or, std::move($1), std::move($3)));
	$$->loc = @2;
}

exclusive_or_exp: and_exp { $$ = std::move($1); }
| exclusive_or_exp "^" and_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::bit_xor, std::move($1), std::move($3)));
	$$->loc = @2;
}

and_exp: equality_exp { $$ = std::move($1); }
| and_exp "&" equality_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::bit_and, std::move($1), std::move($3)));
	$$->loc = @2;
}

equality_exp: relational_exp { $$ = std::move($1); }
| equality_exp "==" relational_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::eq, std::move($1), std::move($3)));
	$$->loc = @2;
}
| equality_exp "!=" relational_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::neq, std::move($1), std::move($3)));
	$$->loc = @2;
}

relational_exp: shift_expression { $$ = std::move($1); }
| relational_exp "<" shift_expression
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::lt, std::move($1), std::move($3)));
	$$->loc = @2;
}
| relational_exp ">" shift_expression
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::gt, std::move($1), std::move($3)));
	$$->loc = @2;
}
| relational_exp "<=" shift_expression
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::le, std::move($1), std::move($3)));
	$$->loc = @2;
}
| relational_exp ">=" shift_expression
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::ge, std::move($1), std::move($3)));
	$$->loc = @2;
}

shift_expression: additive_exp { $$ = std::move($1); }
| shift_expression "<<" additive_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::shift_left, std::move($1), std::move($3)));
	$$->loc = @2;
}
| shift_expression ">>" additive_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::shift_right, std::move($1), std::move($3)));
	$$->loc = @2;
}

additive_exp: mult_exp { $$ = std::move($1); }
| additive_exp "+" mult_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::plus, std::move($1), std::move($3)));
	$$->loc = @2;
}
| additive_exp "-" mult_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::minus, std::move($1), std::move($3)));
	$$->loc = @2;
}

mult_exp: cast_exp { $$ = std::move($1); }
| mult_exp "*" cast_exp 
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::mul, std::move($1), std::move($3)));
	$$->loc = @2;
}
| mult_exp "/" cast_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::div, std::move($1), std::move($3)));
	$$->loc = @2;
}
| mult_exp "%" cast_exp
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::mod, std::move($1), std::move($3)));
	$$->loc = @2;
}

cast_exp: unary_exp { $$ = std::move($1); }
| cast_exp as typename
{ 
	$$ = std::make_unique<exp_cast>(exp_cast(std::move($1), std::move($3)));
	$$->loc = @2;
}

unary_exp: postfix_exp { $$ = std::move($1); }
| unary_operator unary_exp
{ 
	$$ = std::make_unique<exp_unary>(exp_unary($1, std::move($2)));
	$$->loc = @1;
}

unary_operator: "&" { $$ = unary_op::addr_of; }
| "*" { $$ = unary_op::indirect; }
| "+" { $$ = unary_op::pos; }
| "-" { $$ = unary_op::neg; }
| "~" { $$ = unary_op::bit_not; }
| "!" { $$ = unary_op::logical_not; }
| move { $$ = unary_op::move; }

postfix_exp: primary_exp { $$ = std::move($1); }
| postfix_exp "[" exp "]" 
{ 
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::subscript, std::move($1), std::move($3)));
	$$->loc = @2+@3+@4;
}
| postfix_exp "(" argument_exp_list ")" 
{ 
	$$ = std::make_unique<exp_funct_call>(exp_funct_call(std::move($1), std::move($3))); 
	$$->loc = @2+@3+@4;
}
| postfix_exp "("			")" 
{ 
	$$ = std::make_unique<exp_funct_call>(exp_funct_call(std::move($1), {})); 
	$$->loc = @2+@3;
}
| postfix_exp "." id
{ 
	auto __name = std::make_unique<exp_id>(exp_id($3));
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::comp_ref, std::move($1), std::move(__name)));
	$$->loc = @2;
}
| postfix_exp "->" id
{ 
	auto __name = std::make_unique<exp_id>(exp_id($3));
	$$ = std::make_unique<exp_binary>(exp_binary(binary_op::comp_deref, std::move($1), std::move(__name)));
	$$->loc = @2;
}

argument_exp_list: assignment_exp { $$.push_back(std::move($1)); }
| argument_exp_list "," assignment_exp
{
	$1.push_back(std::move($3));
	$$ = std::move($1);
}

primary_exp: var_name { $$ = std::make_unique<exp_id>(exp_id($1)); $$->loc = @1; }
| const_value { $$ = std::make_unique<exp_const>(exp_const(std::move($1))); $$->loc = @1; }
| "(" exp ")" { $$ = std::move($2); $$->set_parentheses(); }
| function_literal { $$ = std::make_unique<exp_const>(exp_const(std::move($1))); }
| array_literal { $$ = std::make_unique<exp_const>(exp_const(std::move($1))); }
| compound_literal { $$ = std::make_unique<exp_dummy>(exp_dummy()); }

array_literal:
"[" init_list_array "]"
{
	$$ =std::make_unique<const_array>(const_array(std::move($2)));
}

init_list_array:
assignment_exp { $$.push_back(std::move($1)); }
| init_list_array "," assignment_exp { $1.push_back(std::move($3)); $$ = std::move($1); }

compound_literal:
var_name "{" init_list_comp "}"

init_list_comp:
/* empty */
| init_list_comp id "=" exp ";"

/* functional */ 
function_literal:
"<" parameters_list ";" func_para_traits typename ">" "{" function_body_stat "}"
{
	std::unique_ptr<stat_func_decl> ret = std::make_unique<stat_func_decl>($4, "", std::move($5));
	$$ = std::make_unique<const_function>(std::move($2), std::move(ret), std::move($8));
	$$->loc = @$;
}
| "<" parameters_list ";" void_ ">" "{" function_body_stat "}"
{
	$$ = std::make_unique<const_function>(std::move($2), nullptr, std::move($7));
	$$->loc = @$;
}
| "<" void_ ";" func_para_traits typename ">" "{" function_body_stat "}"
{
	std::unique_ptr<stat_func_decl> ret = std::make_unique<stat_func_decl>($4, "", std::move($5));
	$$ = std::make_unique<const_function>(std::vector<std::unique_ptr<stat_func_decl>>(), std::move(ret), std::move($8));
	$$->loc = @$;
}
| "<" void_ ";" func_para_traits void_ ">" "{" function_body_stat "}"
{
	$$ = std::make_unique<const_function>(std::vector<std::unique_ptr<stat_func_decl>>(), nullptr, std::move($8));
	$$->loc = @$;
}
| "<" ";" typename ">" "{" function_body_stat "}"
{
	$$ = std::make_unique<const_dummy>();
	error(@1+@2+@3+@4, "Parameter list cannot be empty. Use 'void' instead.");
}

parameters_list:
parameters_list "," parameter_decl { $1.push_back(std::move($3)); $$ = std::move($1); }
| parameter_decl { $$.push_back(std::move($1)); }

parameter_decl:
func_para_traits id ":" typename
{
	$$ = std::make_unique<stat_func_decl>($1, $2, std::move($4));
}

function_body_stat:
function_body
{
	$$ = std::make_unique<stat_block>(&driver, std::move($1));
}

function_body:
/* empty */ {  }
| function_body function_statement
{ $1.push_back(std::move($2)); $$ = std::move($1); }

function_statement:
branch_statement ";" { $$ = std::make_unique<stat_dummy>(stat_dummy()); }
| declare_statement ";" { $$ = std::move($1); }
| exp ";" { $$ = std::make_unique<stat_exp>(stat_exp(std::move($1))); }
| import_statement ";"{ $$ = std::make_unique<stat_dummy>(stat_dummy()); }
| type_statement ";" { $$ = std::make_unique<stat_dummy>(stat_dummy()); }
| use_statement ";" { $$ = std::make_unique<stat_dummy>(stat_dummy()); }
| jump_statement ";" { $$ = std::move($1); }
| error_statement { $$ = std::make_unique<stat_dummy>(stat_dummy()); }

/* branch statements */
branch_statement:
if_statement
| while_statement
| match_statement

if_statement: 
if_ "(" exp ")" "{" function_body "}" elif_statement else_statement
| if_ "(" exp ")" exp elif_statement else_statement
{
	error(@5, "if statement must be in a code block");
}

elif_statement:
/* empty */
| elif_statement elif "(" exp ")"  "{" function_body "}"
| elif_statement elif "(" exp ")" exp
{
	error(@6, "elif statement must be in a code block");
}

else_statement:
/* empty */
| else_ "{" function_body "}"
| else_ exp
{
	error(@2, "else statement must be in a code block");
}

while_statement:
while_  "(" exp ")" "{" function_body "}"

match_statement:
match  "(" exp ")" "{" match_list "}"

match_list:
/* empty */
| match_list match_item

match_item:
match_type ":" "{" function_body "}" ";"

match_type:
/* empty */
| id
| move id

/* jump_statement */
jump_statement:
break_ { $$ = std::make_unique<stat_break>(); }
| continue_ { $$ = std::make_unique<stat_break>(); }
| return_ assignment_exp { $$ = std::make_unique<stat_ret>(std::move($2)); $$->loc = @1; }
| return_ { $$ = std::make_unique<stat_ret>(nullptr); $$->loc = @1; }

/* error recovery */
error_statement:
error ";"
| error eof
{
	YYABORT;
}
%%

namespace rmmc
{
	void Parser::error(const location& loc, const std::string& m)
	{
		std::cout << "line " << loc << ": " << m << "\n";
		++driver.error_count;
		int begin_line = loc.begin.line;
		int begin_col = loc.begin.column;
		int end_col = loc.end.column;
		/* Read that line from file */
		std::fstream file(driver.curr_file);
		file.seekg(std::ios::beg);
		for(int i=0; i < begin_line - 1; ++i){
			file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}
		std::string line;
		std::getline(file, line);
		std::cout<<"\t";
		for(int i=0; i<(int)line.size(); ++i){
			if(i == begin_col-1)std::cout<<"\033[1;31m";
			if(i == end_col-1)std::cout<<"\033[0m";
			std::cout<<line[i];
		}
		std::cout<<"\n\t";std::cout<<"\033[1;32m";
		for(int i = 0; i < begin_col-1; i++)
		std::cout<<"~";
		std::cout<<"^\n";std::cout<<"\033[0m";
	}

}
