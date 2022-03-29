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

    namespace MyParse
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
%define api.namespace {MyParser}
%define api.parser.class {Parser}
%lex-param {MyParser::Driver &driver}
%parse-param {MyParser::Driver &driver}
%define parse.error verbose
%language "c++"
%define api.value.type variant
%define api.token.constructor

%token NEWLINE PLUS MINUS 
%token <int> NUM 
%token END
%token<std::string> ILLEGAL

%type<float> EXPR
%%
STATEMENT : 
{  
	printf("Enter expression:");
}
| STATEMENT EXPR NEWLINE
{
	printf("The result is %f\n",$2);
	printf("Enter expression:");
	driver.location->lines();
    driver.location->step();
    driver.scanner->reset_current_col();
}
| STATEMENT error NEWLINE
{
	driver.location->lines();
    driver.location->step();
    driver.scanner->reset_current_col();
	printf("Enter expression:");
}

EXPR: NUM
{
	$$ = $1;
}
| NUM PLUS EXPR
{
	$$ = $1 + $3;
}
| NUM MINUS EXPR
{
	$$ = $1 - $3;
}

%%

namespace MyParser
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
