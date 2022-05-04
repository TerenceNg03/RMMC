#ifndef SCANPIT_HH_
# define SCANPIT_HH_

# include "parser.hh"

# ifndef YY_DECL
#  define YY_DECL rmmc::Parser::symbol_type                         \
rmmc::Scanner::lex(    \
rmmc::Driver& driver)
# endif


# ifndef __FLEX_LEXER_H
#  include <FlexLexer.h>
# endif


namespace rmmc
{
    
    class Scanner : public yyFlexLexer
    {
        public:
            Scanner();

            virtual ~Scanner();

            virtual Parser::symbol_type lex(Driver& driver);

            std::string current_line="";
            size_t current_col = 0, current_col_end = 0;
            ssize_t current_line_len = 0;
            ssize_t current_line_sent = 0;

            void reset_current_col();
    };
}


#endif // SCANPIT_HH_
