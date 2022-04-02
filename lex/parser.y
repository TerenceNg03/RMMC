%skeleton "lalr1.cc"

%{
#include <stdio.h>
#include <string>
#include "parser.hh"
#include "scanner.hh"
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
let for_ while_ void_ auto_ nullptr_ if_ else_ elif i32 u8 char_ f32 f64 bool_ true_ false_ import_ from export_ mod type comp 

%token 

unknown "unknown character"
newline "end of line"
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
STATEMENT:
{  
	printf("parser called\n");
	YYACCEPT;
}

%%

namespace rmmc
{
    void Parser::error(const location& loc, const std::string& m)
    {
        size_t current_col = driver.scanner->current_col;
        std::cout << "line " << loc << ": " << m << "\n";
        fprintf(stderr,"\t%s\t", driver.scanner->current_line.c_str());
        for(size_t i = 0; i < current_col; i++)
        fprintf(stderr,"~");
        fprintf(stderr,"^\n");
    }
    
}
