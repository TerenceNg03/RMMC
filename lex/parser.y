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

	typedef make_unique<rmmc::ASTNode> make_node;
	typedef make_unique<rmmc::Expression> make_expr;
	#define dloc (*(driver.location))
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

%token<std::string> id "identifier"
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

%type <std::string> str var_name
%type <char> character
%type <std::unique_ptr<rmmc::Expression>> const_value exp assignment_exp conditional_exp logical_or_exp logical_and_exp inclusive_or_exp exclusive_or_exp and_exp equality_exp relational_exp shift_expression additive_exp mult_exp cast_exp unary_exp postfix_exp
%type <rmmc::SingleOperator> unary_operator

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
declare variable_traits id ":" typename_incomplete init_statement
| declare variable_traits id ":" typename optional_init_statement
| opt_export comp id
| opt_export union_ id;
| declare variable_traits id ":" typename_incomplete
{
	error(*(driver.location), "Incomplete type must have an initial value");
}
| declare variable_traits id
{
	error(*(driver.location), "Type must be specified");
}

/* declare keyword*/
declare:
let
| var

/* string preprocess */
str: rawstr
{
	$$ = rmmc::str_process($1);	
}

character: rawchar
{
	auto c = rmmc::char_process($1);
	if(!c){
		error(*(driver.location), "Invalid char literal: " + $1);
		$$ = '\0';
	}else{
		$$ = *c;
	}
}

/* variable trait*/
variable_traits:
| variable_traits variable_trait

variable_trait:
export_
| unique
| ref

/* namespace */
var_name: 
var_name "::" id { $$ = $1 + "::" + $3; }
| id { $$ = $1; }

/* This part deal with init value */
optional_init_statement:
/* empty */
| init_statement

init_statement:
"=" exp

const_value:
long_ { $$ = make_node(new IntegerExpr($1, dloc)); }
| float_ { $$ = make_node(new Doublexpr($1, dloc)); }
| str
| character { $$ = make_node(new CharExpr($1, dloc)); }
| true_ { $$ = make_node(new BooleanExpr(false, dloc); }
| false_ { $$ = make_node(new BooleanExpr(false, dloc); }
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
	error(*(driver.location), "Qualified id not allowed here");
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
type opt_export id typename
| opt_export comp_type
| opt_export union_type

opt_export:
/* empty */
| export_

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

assignment_exp: conditional_exp { $$ = std::move($1); }
| unary_exp "=" assignment_exp

conditional_exp: logical_or_exp { $$ = std::move($1); }
| logical_or_exp "?" exp ":" conditional_exp
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::E, dloc)); 
}

logical_or_exp: logical_and_exp { $$ = std::move($1); }
| logical_or_exp "||" logical_and_exp
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::LOGICAL_OR, dloc)); 
}

logical_and_exp: inclusive_or_exp { $$ = std::move($1); }
| logical_and_exp "&&" inclusive_or_exp
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::LOGICAL_AND, dloc)); 
}

inclusive_or_exp: exclusive_or_exp { $$ = std::move($1); }
| inclusive_or_exp "|" exclusive_or_exp
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::E, dloc)); 
}

exclusive_or_exp: and_exp { $$ = std::move($1); }
| exclusive_or_exp "^" and_exp
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::E, dloc)); 
}

and_exp: equality_exp { $$ = std::move($1); }
| and_exp "&" equality_exp
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::E, dloc)); 
}

equality_exp: relational_exp { $$ = std::move($1); }
| equality_exp "==" relational_exp
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::E, dloc)); 
}
| equality_exp "!=" relational_exp
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::NE, dloc)); 
}

relational_exp: shift_expression { $$ = std::move($1); }
| relational_exp "<" shift_expression
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::LT, dloc)); 
}
| relational_exp ">" shift_expression
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::GT, dloc)); 
}
| relational_exp "<=" shift_expression
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::ELT, dloc)); 
}
| relational_exp ">=" shift_expression
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::EGT, dloc)); 
}

shift_expression: additive_exp { $$ = std::move($1); }
| shift_expression "<<" additive_exp
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::LEFT_SHIFT, dloc)); 
}
| shift_expression ">>" additive_exp
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::RIGHT_SHIFT, dloc)); 
}

additive_exp: mult_exp { $$ = std::move($1); }
| additive_exp "+" mult_exp
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::ADD, dloc)); 
}
| additive_exp "-" mult_exp
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::SUB, dloc)); 
}

mult_exp: cast_exp { $$ = std::move($1); }
| mult_exp "*" cast_exp 
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::MUL, dloc)); 
}
| mult_exp "/" cast_exp 
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::DIV, dloc)); 
}
| mult_exp "%" cast_exp 
{ 
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::MOD, dloc));
}

cast_exp: unary_exp { $$ = std::move($1); }
| cast_exp as typename
{
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($3), BinaryOperator::AS, dloc));
}

unary_exp: postfix_exp { $$ = std::move($1); }
| unary_operator unary_exp
{
	$$ = make_expr(new SingleOperatorExpr (std::move($1), std::move($2), BinaryOperator::AS, dloc));
}

unary_operator: "&" { $$ = SingleOperator::ADDRESS_OF; }
| "*" { $$ = SingleOperator::INDIRECTION; }
| "+" 
| "-" 
| "~" { $$ = SingleOperator::BITWISE_NOT; }
| "!" { $$ = SingleOperator::LOGICAL_NOT; }
| move { $$ = SingleOperator::move; }

postfix_exp: primary_exp
| postfix_exp "[" exp "]"
{
	$$ = make_expr(new SingleOperatorExpr (std::move($1), std::move($2), BinaryOperator::AS, dloc));
}
| postfix_exp "(" argument_exp_list ")"
{
	$$ = make_expr(new FunctionCallExpr(std::move($1), std::move($3), dloc));
}
| postfix_exp "("			")"
{
	$$ = make_expr(new FunctionCallExpr(std::move($1), dloc));
}

| postfix_exp "." id
{
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($2), BinaryOperator::MEMBER_ACCESS, dloc));
}
| postfix_exp "->" id
{
	$$ = make_expr(new BinaryOperatorExpr(std::move($1), std::move($2), BinaryOperator::MEMBER_ACCESS_PTR, dloc));
}

argument_exp_list: assignment_exp
| argument_exp_list "," assignment_exp

primary_exp: var_name
{
	$$ = make_expr(new IdentifierExpr($1, dloc));
}
| const_value { $$ = std::move($1); }
| "(" exp ")" { $$ = std::move($2); }
| function_literal { $$ = std::move($1); }
| array_literal { $$ = std::move($1); }
| compound_literal { $$ = std::move($1); }

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
| init_list_comp id init_statement ";"

/* functional */ 
function_literal:
"<" parameters_list ";" func_para_traits typename ">" function_block
| "<" void_ ";" func_para_traits typename ">" function_block
| "<" ";" typename ">" function_block
{
	error(*(driver.location), "Parameter list cannot be empty. Use 'void' instead.");
}

parameters_list:
parameters_list "," parameter_decl
| parameter_decl

parameter_decl:
func_para_traits id ":" typename

function_body:
/* empty */
| function_body function_statement

function_block:
"{" function_body "}"

function_statement:
branch_statement ";"
| declare_statement ";"
| exp ";"
| import_statement ";"
| type_statement ";"
| use_statement ";"
| jump_statement ";"
| function_block ";"
| error_statement

/* branch statements */
branch_statement:
if_statement
| while_statement
| match_statement

if_statement: 
if_ "(" exp ")" function_block elif_statement else_statement
| if_ "(" exp ")" exp elif_statement else_statement
{
	error(*(driver.location), "if statement must be in a code block");
}

elif_statement:
/* empty */
| elif_statement elif "(" exp ")"  function_block
| elif_statement elif "(" exp ")" exp
{
	error(*(driver.location), "elif statement must be in a code block");
}

else_statement:
/* empty */
| else_ function_block
| else_ exp
{
	error(*(driver.location), "else statement must be in a code block");
}

while_statement:
while_  "(" exp ")" function_block

match_statement:
match  "(" exp ")" "{" match_list "}"

match_list:
/* empty */
| match_list match_item

match_item:
match_type ":" function_block ";"

match_type:
/* empty */
| id
| move id

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
