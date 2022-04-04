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
let as for_ while_ void_ auto_ nullptr_ if_ else_ elif bool_ true_ false_ import_ from export_ mod type comp
u8 u16 u32 u64 i8 i16 i32 i64 f32 f64

%token

unknown "unknown character"
eof "end of file"

%token<std::string> name rawstr rawchar

%token <long> long_

%token <double> float_

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
	printf("[DEBUG] Parsing step started\n");
#endif
}
| STATEMENTS STATEMENT 
| STATEMENTS eof
{
#if DEBUG
	printf("[DEBUG] Parsing step succeeded with no error\n");
#endif
	YYACCEPT;
}


STATEMENT:
declare_statement ";"
| import_statement ";"
| type_statement ";"

/* assign statement */
declare_statement:
let opt_export var_name ":" typename_incomplete init_statement

/* string preprocess */
str: rawstr

character: rawchar

/* optional export */
opt_export:
| export_

/* namespace */
var_name: 
var_name "::" name
| name

/* This part deal with init value */
init_statement:
| "=" exp
| "=" init_compound

const_value:
long_
| float_
| str
| character
| true_
| false_

init_compound:
"{" init_list "}"

init_list:
| init_list "," init_compound
| init_compound
| init_list "," assignment_exp
| assignment_exp

/* This part deal with typename */
typename_incomplete:
"[" typename "," "]"
| auto_
| typename

typename:
"[" typename "," long_ "]"
| "*" typename
| "(" typenamelist ")" "->" typename
| basictype
| name /* defined by type keyword */

typenamelist:
typenamelist "," typename
| typename

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
type name typename

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

unary_operator: "&" | "*" | "+" | "-" | "~" | "!"

postfix_exp: primary_exp
| postfix_exp "[" exp "]"
| postfix_exp "(" argument_exp_list ")"
| postfix_exp "("			")"
| postfix_exp "." name
| postfix_exp "->" name

primary_exp: var_name
| const_value
| "(" exp ")"

argument_exp_list: assignment_exp
| argument_exp_list "," assignment_exp



%%

namespace rmmc
{
	void Parser::error(const location& loc, const std::string& m)
	{
		std::cout << "line " << loc << ": " << m << "\n";

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
		printf("\t");
		for(size_t i=0; i<line.size(); ++i){
			if(i == begin_col-1)printf("\033[1;31m");
			if(i == end_col-1)printf("\033[0m");
			putchar(line[i]);
		}
		printf("\n\t");printf("\033[1;32m");
		for(int i = 0; i < begin_col-1; i++)
		printf("~");
		printf("^\n");printf("\033[0m");
	}

}
