%{
#include <iostream>
#include "parser.hh"
#include "scanner.hh"
#define loc (*driver.location)
#ifndef register
#define register
#endif


#define YY_USER_ACTION                                \
{loc.columns(yyleng); driver.scanner->current_col =driver.scanner->current_col_end; driver.scanner->current_col_end += yyleng;}

using namespace rmmc;

%}

%option nodefault
%option debug
%option noyywrap
%option prefix="rmmc"
%option yylineno
%option c++
%%

let  return Parser::make_let(loc);
for return Parser::make_for_(loc);
while return Parser::make_while_(loc);
void return Parser::make_void_(loc);
auto return Parser::make_auto_(loc);
nullptr return Parser::make_nullptr_(loc);
if return Parser::make_if_(loc);
else return Parser::make_else_(loc);
elif return Parser::make_elif(loc);
i8 return Parser::make_i8(loc);
i16 return Parser::make_i16(loc);
i32 return Parser::make_i32(loc);
i64 return Parser::make_i64(loc);
u8 return Parser::make_u8(loc);
u16 return Parser::make_u16(loc);
u32 return Parser::make_u32(loc);
u64 return Parser::make_u64(loc);
f32 return Parser::make_f32(loc);
f64 return Parser::make_f64(loc);
bool return Parser::make_bool_(loc);
true return Parser::make_true_(loc);
false return Parser::make_false_(loc);
import return Parser::make_import_(loc);
from return Parser::make_from(loc);
export return Parser::make_export_(loc);
mod return Parser::make_mod(loc);
type return Parser::make_type(loc);
comp return Parser::make_comp(loc);


[a-zA-Z]{1,}[0-9a-zA-Z]* return Parser::make_name(std::string(yytext),loc);

\"(\\.|[^\\"])*\"  return Parser::make_rawstr(std::string(yytext),loc);/* string literal (remove \") */
\'(\\.|[^\\'])*\' return Parser::make_rawchar(std::string(yytext),loc);/* char literal (remove \r') */

[0-9]{1,} return Parser::make_long_(atoi(yytext),loc); /* decimal number */
0[xX][0-9a-fA-F]+ return Parser::make_long_(strtol(yytext, NULL, 16),loc); /* hex number */
0[bB][0-1]+ return Parser::make_long_(strtol(yytext, NULL, 2),loc); /* binary number */

([0-9]+([.][0-9]*)?|[.][0-9]+) return Parser::make_float_(std::atof(yytext),loc); /* float point number */

"-" return Parser::make_minus(loc);
"+" return Parser::make_plus(loc);
"/" return Parser::make_div(loc);
"*" return Parser::make_mul(loc);
"=" return Parser::make_assign(loc);

"(" return Parser::make_roundbl(loc);
")" return Parser::make_roundbr(loc);
"[" return Parser::make_boxbl(loc);
"]" return Parser::make_boxnr(loc);
"{" return Parser::make_curlybl(loc);
"}" return Parser::make_curlybr(loc);
"<" return Parser::make_lt(loc);
">" return Parser::make_gt(loc);
">=" return Parser::make_ge(loc);
"<=" return Parser::make_le(loc);
">>" return Parser::make_shiftright(loc);
"<<" return Parser::make_shiftleft(loc);
"==" return Parser::make_eq(loc);
"!=" return Parser::make_noteq(loc);
"." return Parser::make_point(loc);
"->" return Parser::make_leftarror(loc);
":" return Parser::make_colon(loc);
"::" return Parser::make_doublecolon(loc);

"&" return Parser::make_bitand_(loc);
"|" return Parser::make_bitor_(loc);
"^" return Parser::make_bitxor_(loc);
"~" return Parser::make_bitnot_(loc);
"#"[^\n]*\n /* comments */
";" return Parser::make_semicolon(loc);

"&&" return Parser::make_and_(loc);
"||" return Parser::make_or_(loc);
"!" return Parser::make_not_(loc);

\n driver.location->lines();driver.location->step();driver.scanner->reset_current_col();

<<EOF>> return Parser::make_eof(loc);

[ \t]+ /* ignore whitespace */
. return Parser::make_unknown(loc);

%%

namespace rmmc
{

    Scanner::Scanner()
    {
        log = fopen(logfile,"w");
        if(!log)perror("Scanner Error : Cannot create log!\n");
    }

    Scanner::~Scanner()
    {
        fclose(log);
    }

    void Scanner::reset_current_col() {
        current_col = current_col_end = 0;
        fprintf(log,"%s",current_line.c_str());
        current_line_sent = current_line_len = 0;
        current_line = "";
    }

    size_t Scanner::LexerInput(char* buf, size_t max_size) {
        size_t avail = current_line_len - current_line_sent;
		std::cout<<"LexerInput called"<<std::endl;
        if (!avail) {
            current_line_sent = 0;
            getline(yyin,current_line);
            avail = current_line.length();
            if(yyin.bad()){
                avail = 0;
                return -1;
            }else{
                if(!yyin.eof()){
                    current_line+='\n';
                    avail++;
                }
            }
            current_line_len = avail;
        }
        if (avail > max_size) avail = max_size;
        memcpy(buf, current_line.c_str() + current_line_sent, avail);

        current_line_sent += avail;
        if (!avail) reset_current_col();
        return avail;
    }



}

#ifdef yylex
# undef yylex
#endif


int yyFlexLexer::yylex()
{
  std::cerr << "call parseFlexLexer::yylex()!" << std::endl;
  return 0;
}
