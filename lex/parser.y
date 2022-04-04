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
let for_ while_ void_ auto_ nullptr_ if_ else_ elif bool_ true_ false_ import_ from export_ mod type comp
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

%left
"::"
"."
"->"

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
| STATEMENTS STATEMENT ";"
| STATEMENTS eof
{
#if DEBUG
	printf("[DEBUG] Parsing step succeeded with no error\n");
#endif
	YYACCEPT;
}


STATEMENT:
		 assign_statement
| import_statement
| type_statement

/* assign statement */
assign_statement:
				let opt_export var_name ":" typename_incomplete init_statement

/* string preprocess */
str: rawstr

character: rawchar

/* optional export */
opt_export:
		  | export_

/* namespace */
var_name: var_name "::" name
		| name

/* This part deal with init value */
init_statement:
			  | "=" init_value

init_value:
		  long_
| float_
| str
| character
| true_
| false_
| init_compound

init_compound:
			 "{" init_list "}"

init_list:
		 init_list "," init_value
| init_value

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


%%

namespace rmmc
{
	void Parser::error(const location& loc, const std::string& m)
	{
		std::cout << "line " << loc << ": " << m << "\n";

		int begin_line = loc.begin.line;
		int begin_col = loc.begin.column;
		/* Read that line from file */
		std::fstream file(driver.curr_file);
		file.seekg(std::ios::beg);
		for(int i=0; i < begin_line - 1; ++i){
			file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
		}
		std::string line;
		std::getline(file, line);
		printf("\t%s\n\t", line.c_str());
		for(int i = 0; i < begin_col-1; i++)
		printf("~");
		printf("^\n");
	}

}
