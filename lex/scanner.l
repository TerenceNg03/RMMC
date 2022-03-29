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


%}

%option nodefault
%option debug
%option noyywrap
%option prefix="MyParser"
%option yylineno
%option c++
%%

[0-9]{1,} return MyParser::Parser::make_NUM(atoi(yytext),loc);
"-" return MyParser::Parser::make_MINUS(loc);
"+" return MyParser::Parser::make_PLUS(loc);

\n return MyParser::Parser::make_NEWLINE(loc);

<<EOF>> return MyParser::Parser::make_END(loc);

[ \t]+ /* ignore whitespace */
. return MyParser::Parser::make_ILLEGAL(std::string(yytext),loc);

%%

namespace MyParser
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
