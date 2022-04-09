%skeleton "lalr1.cc"

%{
#include <stdio.h>
#include <string>
#include "parser.hh"
#include "scanner.hh"
#include "rmm_types.hh"
#include <fstream>
#define yylex driver.scanner->lex
%}

%code requires{
	#include "driver.hh"
	#include "location.hh"
	#include "position.hh"
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

%token<std::string> name "identifier"
rawstr "string"
rawchar "character"

%token <long> long_ "integer constant"

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


%%
STATEMENTS:
/* empty */
{
#if DEBUG
	std::cout<<"[DEBUG] Parsing step started\n";
#endif
}
| STATEMENTS STATEMENT 
| STATEMENTS eof
{
#if DEBUG
	if(!driver.get_error_count())std::cout<<"[DEBUG] Parsing step succeeded with no error\n";
#endif
	if(driver.get_error_count())std::cout<<"\033[1;31mAborting\033[0m: \033[1;31m"<<driver.get_error_count()<<" fatal errors \033[0mencountered.\n";
	YYACCEPT;
}


STATEMENT:
declare_statement ";"
| import_statement ";"
| type_statement ";"
| mod_statement ";"
| use_statement ";"
| error_statement

/* assign statement */
declare_statement:
declare variable_traits name ":" typename_incomplete init_statement
| declare variable_traits name ":" typename optional_init_statement
| opt_export comp name
| opt_export union_ name;
| declare variable_traits name ":" typename_incomplete
{
	error(*(driver.location), "Incomplete type must have an initial value");
}
| declare variable_traits name
{
	error(*(driver.location), "Type must be specified");
}

/* declare keyword*/
declare:
let
| var

/* string preprocess */
str: rawstr

character: rawchar

/* variable trait*/
variable_traits:
| variable_traits variable_trait

variable_trait:
export_
| unique
| ref

/* namespace */
var_name: 
var_name "::" name
| name

/* This part deal with init value */
optional_init_statement:
/* empty */
| init_statement

init_statement:
"=" exp

const_value:
long_
| float_
| str
| character
| true_
| false_
| nullptr_


/* This part deal with typename */
typename_incomplete:
"[" typename "," "]"
| auto_
| "[" typename "," var_name "]"

typename:
"[" typename "," long_ "]"
| "*" typename
| "(" func_para_typelist ")" "->" func_para_traits typename
| basictype
| var_name /* defined by type keyword */
| comp_type
| union_type


comp_type:
comp name "{" comp_decl_list "}" /* named comp */

union_type:
union_ name "{" comp_decl_list "}"

comp_decl_list:
/* empty */
| comp_decl_list comp_decl_item

comp_decl_item:
func_para_traits name ":" typename ";"
| func_para_traits name "::" var_name ":" typename ";"
{
	error(*(driver.location), "Qualified name not allowed here");
}

func_para_typelist:
func_para_typelist "," func_para_traits typename
| func_para_traits typename

func_para_traits:
| func_para_traits func_para_trait

func_para_trait:
unique
| ref
| mut

basictype:
void_
| bool_
| u8
| u16
| u32
| u64
| i8
| i16
| i32
| i64
| f32
| f64

/* import statement */
import_statement:
from var_name import_ var_name
| from str import_ var_name
| import_ var_name
| import_ str

/* type statement */
type_statement:
type opt_export name typename
| opt_export comp_type
| opt_export union_type

opt_export:
/* empty */
| export_

/* mod_statement */ 
mod_statement:
mod name "{" inmod_satements "}"

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
exp: assignment_exp
| exp "," assignment_exp

assignment_exp: conditional_exp
| unary_exp "=" assignment_exp

conditional_exp: logical_or_exp
| logical_or_exp "?" exp ":" conditional_exp

logical_or_exp: logical_and_exp
| logical_or_exp "||" logical_and_exp

logical_and_exp: inclusive_or_exp
| logical_and_exp "&&" inclusive_or_exp

inclusive_or_exp: exclusive_or_exp
| inclusive_or_exp "|" exclusive_or_exp

exclusive_or_exp: and_exp
| exclusive_or_exp "^" and_exp

and_exp: equality_exp
| and_exp "&" equality_exp

equality_exp: relational_exp
| equality_exp "==" relational_exp
| equality_exp "!=" relational_exp

relational_exp: shift_expression
| relational_exp "<" shift_expression
| relational_exp ">" shift_expression
| relational_exp "<=" shift_expression
| relational_exp ">=" shift_expression

shift_expression: additive_exp
| shift_expression "<<" additive_exp
| shift_expression ">>" additive_exp

additive_exp: mult_exp
| additive_exp "+" mult_exp
| additive_exp "-" mult_exp

mult_exp: cast_exp
| mult_exp "*" cast_exp
| mult_exp "/" cast_exp
| mult_exp "%" cast_exp

cast_exp: unary_exp
| cast_exp as typename

unary_exp: postfix_exp
| unary_operator unary_exp 

unary_operator: "&" | "*" | "+" | "-" | "~" | "!" | move

postfix_exp: primary_exp
| postfix_exp "[" exp "]"
| postfix_exp "(" argument_exp_list ")"
| postfix_exp "("			")"
| postfix_exp "." name
| postfix_exp "->" name

argument_exp_list: assignment_exp
| argument_exp_list "," assignment_exp

primary_exp: var_name
| const_value
| "(" exp ")"
| function_literal
| array_literal
| compound_literal

array_literal:
"[" init_list_array "]"
| "[" "]"

init_list_array:
assignment_exp
| init_list_array "," assignment_exp

compound_literal:
var_name "{" init_list_comp "}"

init_list_comp:
/* empty */
| init_list_comp name init_statement ";"

/* functional */ 
function_literal:
"<" parameters_list ";" func_para_traits typename ">" "{" function_body "}"
| "<" void_ ";" func_para_traits typename ">" "{" function_body "}"
| "<" ";" typename ">" "{" function_body "}"
{
	error(*(driver.location), "Parameter list cannot be empty. Use 'void' instead.");
}

parameters_list:
parameters_list "," parameter_decl
| parameter_decl

parameter_decl:
func_para_traits name ":" typename

function_body:
/* empty */
| function_body function_statement

function_statement:
branch_statement ";"
| declare_statement ";"
| exp ";"
| import_statement ";"
| type_statement ";"
| use_statement ";"
| jump_statement ";"
| error_statement

/* branch statements */
branch_statement:
if_statement
| while_statement
| match_statement

if_statement: 
if_ "(" exp ")" "{" function_body "}" elif_statement else_statement
| if_ "(" exp ")" exp elif_statement else_statement
{
	error(*(driver.location), "if statement must be in a code block");
}

elif_statement:
/* empty */
| elif_statement elif "(" exp ")"  "{" function_body "}"
| elif_statement elif "(" exp ")" exp
{
	error(*(driver.location), "elif statement must be in a code block");
}

else_statement:
/* empty */
| else_ "{" function_body "}"
| else_ exp
{
	error(*(driver.location), "else statement must be in a code block");
}

while_statement:
while_  "(" exp ")" "{" function_body "}"

match_statement:
match exp "{" match_list "}"

match_list:
/* empty */
| match_list match_item

match_item:
match_type ":" "{" function_body "}" ";"

match_type:
/* empty */
| name
| move name

/* jump_statement */
jump_statement:
break_
| continue_
| return_ assignment_exp
| return_

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
