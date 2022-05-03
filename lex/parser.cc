// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.



// First part of user prologue.
#line 3 "parser.y"

#include <stdio.h>
#include <string>
#include "parser.hh"
#include "scanner.hh"
#include "rmm_types.hh"
#include <fstream>
#define yylex driver.scanner->lex

#line 50 "parser.cc"


#include "parser.hh"




#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 37 "parser.y"
namespace rmmc {
#line 147 "parser.cc"


  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (rmmc::Driver &driver_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_number_type
  Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 49: // " float constant"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 48: // "integer constant"
        value.YY_MOVE_OR_COPY< long > (YY_MOVE (that.value));
        break;

      case 45: // "identifier"
      case 46: // "string"
      case 47: // "character"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 49: // " float constant"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 48: // "integer constant"
        value.move< long > (YY_MOVE (that.value));
        break;

      case 45: // "identifier"
      case 46: // "string"
      case 47: // "character"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 49: // " float constant"
        value.copy< double > (that.value);
        break;

      case 48: // "integer constant"
        value.copy< long > (that.value);
        break;

      case 45: // "identifier"
      case 46: // "string"
      case 47: // "character"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 49: // " float constant"
        value.move< double > (that.value);
        break;

      case 48: // "integer constant"
        value.move< long > (that.value);
        break;

      case 45: // "identifier"
      case 46: // "string"
      case 47: // "character"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case 49: // " float constant"
        yylhs.value.emplace< double > ();
        break;

      case 48: // "integer constant"
        yylhs.value.emplace< long > ();
        break;

      case 45: // "identifier"
      case 46: // "string"
      case 47: // "character"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2:
#line 155 "parser.y"
{
#if DEBUG
	std::cout<<"[DEBUG] Parsing step started\n";
#endif
}
#line 648 "parser.cc"
    break;

  case 4:
#line 162 "parser.y"
{
#if DEBUG
	if(!driver.get_error_count())std::cout<<"[DEBUG] Parsing step succeeded with no error\n";
#endif
	if(driver.get_error_count())std::cout<<"\033[1;31mAborting\033[0m: \033[1;31m"<<driver.get_error_count()<<" fatal errors \033[0mencountered.\n";
	YYACCEPT;
}
#line 660 "parser.cc"
    break;

  case 15:
#line 186 "parser.y"
{
	error(*(driver.location), "Incomplete type must have an initial value");
}
#line 668 "parser.cc"
    break;

  case 16:
#line 190 "parser.y"
{
	error(*(driver.location), "Type must be specified");
}
#line 676 "parser.cc"
    break;

  case 53:
#line 265 "parser.y"
{
	error(*(driver.location), "Qualified name not allowed here");
}
#line 684 "parser.cc"
    break;

  case 159:
#line 424 "parser.y"
{
	error(*(driver.location), "Parameter list cannot be empty. Use 'void' instead.");
}
#line 692 "parser.cc"
    break;

  case 177:
#line 458 "parser.y"
{
	error(*(driver.location), "if statement must be in a code block");
}
#line 700 "parser.cc"
    break;

  case 180:
#line 466 "parser.y"
{
	error(*(driver.location), "elif statement must be in a code block");
}
#line 708 "parser.cc"
    break;

  case 183:
#line 474 "parser.y"
{
	error(*(driver.location), "else statement must be in a code block");
}
#line 716 "parser.cc"
    break;

  case 197:
#line 507 "parser.y"
{
	YYABORT;
}
#line 724 "parser.cc"
    break;


#line 728 "parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short Parser::yypact_ninf_ = -276;

  const signed char Parser::yytable_ninf_ = -81;

  const short
  Parser::yypact_[] =
  {
    -276,  1063,  -276,   -25,  -276,  -276,   -11,    57,    57,  -276,
      -3,    36,  -276,  -276,   -54,  -276,   -16,    29,    45,    51,
      61,  -276,  -276,  -276,  -276,    25,  -276,  -276,    25,   121,
      -8,    97,   120,  -276,     4,  -276,  -276,   128,   130,  -276,
    -276,  -276,  -276,   141,   -11,   -11,  -276,  1025,  -276,  -276,
    -276,   127,  -276,   150,   155,  -276,    25,    25,   221,  -276,
    -276,   178,  -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,   181,  1025,  -276,  1025,    25,  -276,  -276,  -276,
    -276,   992,  -276,  -276,  -276,   152,   154,   157,  -276,   158,
    -276,   150,   155,  -276,   -36,   959,   161,  -276,  1025,   183,
     183,   180,   182,  -276,  -276,  -276,  -276,   168,  -276,  -276,
    -276,  -276,  -276,  -276,   195,   176,   134,  -276,  -276,  -276,
    -276,  -276,    13,  -276,  -276,   959,   191,    89,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,  -276,  -276,   134,    67,
       1,  -276,  -276,  -276,  -276,  -276,    72,  -276,   184,  -276,
    -276,    47,   171,   177,   207,   185,   102,    88,   112,   146,
     -21,   248,   203,   134,    40,  -276,  -276,  -276,  -276,    62,
     959,  -276,  -276,  -276,    33,   -35,  -276,  -276,    68,   208,
    1025,    43,   -55,  -276,  -276,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,   134,   134,   134,   134,   134,
     134,   134,   134,   134,   134,  1025,   134,  -276,   767,   134,
     213,   215,  1025,   -11,  -276,  -276,  -276,  -276,   134,  -276,
     225,   223,  -276,  -276,    63,  -276,   171,  -276,   133,   177,
     207,   185,   102,    88,    88,   112,   112,   112,   112,   146,
     146,   -21,   -21,   248,   248,   248,  -276,  -276,  -276,  -276,
     -26,    74,  -276,  -276,   214,    95,  -276,   959,   236,  1025,
    -276,   959,   183,  -276,   134,  -276,   134,  -276,  -276,  1025,
     235,  -276,  -276,   237,   220,  -276,  -276,   227,   249,   281,
     250,  -276,  -276,  -276,  -276,   134,  -276,   255,   256,   134,
    -276,   234,   238,   239,   242,    22,  -276,   244,  -276,  -276,
    -276,   246,  -276,  -276,   344,  -276,   134,   134,   -37,  -276,
    -276,  -276,  -276,  -276,  -276,  -276,   407,  -276,    -9,    21,
    -276,  -276,   254,   812,    -5,  -276,  -276,   184,   269,  -276,
    -276,  -276,   262,   470,   533,   196,  -276,   266,  -276,  -276,
     857,   260,  -276,  -276,   196,  -276,   184,   134,   596,  -276,
     659,    27,   257,  -276,   902,  -276,  -276,   184,   722,  -276
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       2,     0,     1,     0,    17,    18,     0,     0,     0,    81,
       0,    80,     4,     3,     0,    21,     0,     0,     0,     0,
       0,    10,   197,   196,    27,    90,    19,    76,    75,     0,
       0,     0,     0,     5,     0,     6,     7,     0,     0,    78,
      79,     8,     9,     0,     0,     0,    83,     0,    23,    24,
      25,    16,    22,    13,    14,    26,    74,    73,     0,    61,
      62,     0,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,     0,     0,    56,     0,    45,    77,    46,    47,
      44,     0,    50,    50,    82,     0,     0,     0,    84,     0,
      89,     0,     0,    42,     0,     0,     0,    39,     0,    15,
      28,    56,    56,    85,    86,    87,    88,     0,    56,    60,
      58,    59,    55,    57,     0,     0,     0,    11,    12,    29,
      48,    51,     0,    49,    56,     0,     0,     0,    35,    36,
      37,   135,    20,    31,    32,   132,   131,   130,     0,     0,
      56,   129,   133,   134,    33,    34,   144,   145,    30,    91,
      93,    95,    97,    99,   101,   103,   105,   107,   110,   115,
     118,   121,   125,     0,   127,   136,   148,   149,   147,     0,
       0,    54,    41,    38,     0,     0,   151,   152,     0,     0,
       0,     0,     0,   161,   155,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   128,     0,     0,
       0,     0,     0,     0,    43,    40,   146,   150,     0,    56,
       0,     0,    56,    56,     0,    92,    98,   125,     0,   100,
     102,   104,   106,   108,   109,   111,   112,   114,   113,   117,
     116,   120,   119,   123,   122,   124,   126,    94,   139,   142,
       0,     0,   140,   141,     0,     0,   153,     0,     0,     0,
     160,     0,     0,   154,     0,   138,     0,   137,    52,     0,
       0,   163,   162,     0,     0,    96,   143,     0,     0,     0,
       0,   156,    53,   163,   192,   195,   193,     0,     0,     0,
     159,     0,     0,     0,     0,     0,   164,     0,   173,   174,
     175,     0,   172,   163,     0,   194,     0,     0,     0,   166,
     168,   169,   170,   167,   165,   171,     0,   158,     0,     0,
     186,   157,     0,     0,   189,   163,   163,   178,     0,   190,
     185,   187,     0,     0,     0,   181,   191,     0,   184,   178,
       0,     0,   177,   163,   181,   163,   183,     0,     0,   176,
       0,     0,     0,   182,     0,   188,   163,   180,     0,   179
  };

  const short
  Parser::yypgoto_[] =
  {
    -276,  -276,  -276,     6,  -276,   209,  -276,  -276,  -276,    -6,
    -276,   -95,  -276,  -276,   -69,   319,   321,   261,  -276,  -276,
     -64,  -276,  -276,   342,     8,   335,   291,  -276,  -276,    14,
    -113,  -128,    86,  -276,   174,   169,   172,   186,   187,    26,
     -34,    30,    20,    -1,    76,  -276,  -276,  -276,  -276,  -276,
    -276,  -276,  -276,  -276,  -276,   149,  -275,  -276,  -276,  -276,
      34,    24,  -276,  -276,  -276,  -276,  -276,  -276,    15
  };

  const short
  Parser::yydefgoto_[] =
  {
      -1,     1,    13,   291,    15,   144,   145,    34,    52,   146,
     118,   117,   147,    99,    77,    78,    79,   101,   121,    94,
     122,   113,    80,   292,   293,    18,    19,    58,    88,   294,
     295,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   162,   163,   164,   250,   165,   166,
     178,   167,   224,   168,   182,   183,   279,   296,   297,   298,
     335,   342,   299,   300,   324,   331,   332,   301,   302
  };

  const short
  Parser::yytable_[] =
  {
      25,    28,    30,   148,    93,   119,    96,    14,   304,    17,
      95,   177,   100,    45,   179,    20,    21,   222,   109,    22,
     107,   216,   320,   223,    33,   175,   112,    48,   316,   115,
     265,   202,   203,   328,    24,   185,   108,   185,    56,    57,
     329,    76,    31,    49,   125,    50,   266,   322,   109,    51,
     333,   334,   110,    23,   111,   330,   171,   225,   169,     9,
     170,   204,    35,   185,    85,    43,    86,    76,   348,    76,
     350,    37,    89,    90,   228,    76,   181,   323,   247,   180,
     249,   358,   110,   354,   111,    38,   128,   129,   221,    76,
     256,   215,    76,   185,   185,   208,   251,   209,    43,   185,
     313,   214,    24,    26,   130,   131,    43,    36,   262,   210,
     211,   220,    24,    26,   132,   133,   134,   135,   136,    76,
     137,   174,   138,   263,   139,   176,   217,   186,   140,    41,
     187,   184,   267,   212,    24,   213,   246,   126,   276,    42,
     218,   141,    44,   254,   142,    43,   185,   173,   143,   194,
     195,   196,   197,   128,   129,   257,    46,   305,   181,   261,
     235,   236,   237,   238,    76,    47,   269,   274,    43,   192,
     193,   130,   131,    53,    76,    54,   308,   198,   199,    24,
      26,   132,   133,   134,   135,   136,    55,   137,   270,   138,
     272,   139,   273,   318,   319,   140,   200,   201,    81,    76,
     277,   243,   244,   245,   264,   185,    76,   255,   141,    82,
     327,   142,   340,   341,    83,   143,    27,    29,   233,   234,
     241,   242,     3,    91,     4,     5,    92,   346,   239,   240,
     103,     6,   104,   114,   351,   105,   106,   116,   124,   207,
     120,   357,   123,   126,     9,    10,    11,   -80,   127,   172,
     188,    76,   189,    76,   205,    76,   185,   206,   252,   191,
     253,   -80,   227,    76,   227,   227,   227,   227,   227,   227,
     227,   227,   227,   227,   227,   227,   227,   227,   227,   227,
     227,    84,     3,   190,     4,     5,   219,   258,   284,   285,
     286,     6,   268,   287,   259,   271,   288,   278,   281,   280,
     128,   129,     7,     8,     9,   282,    11,   -80,   283,   303,
     306,   307,   309,   325,   336,   347,   310,   311,   130,   131,
     312,   -80,   314,   289,   315,   343,    24,    26,   132,   133,
     134,   135,   136,   337,   137,   355,   138,    39,   139,    40,
     227,   290,   140,    16,   102,     3,    32,     4,     5,    87,
     275,   284,   285,   286,     6,   141,   287,   229,   142,   288,
     226,   230,   143,   128,   129,     7,     8,     9,   349,    11,
     -80,   260,     0,   344,     0,     0,   231,     0,   232,     0,
       0,   130,   131,     0,   -80,     0,   289,     0,     0,    24,
      26,   132,   133,   134,   135,   136,     0,   137,     0,   138,
       0,   139,     0,     0,   317,   140,     0,     0,     3,     0,
       4,     5,     0,     0,   284,   285,   286,     6,   141,   287,
       0,   142,   288,     0,     0,   143,   128,   129,     7,     8,
       9,     0,    11,   -80,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   130,   131,     0,   -80,     0,   289,
       0,     0,    24,    26,   132,   133,   134,   135,   136,     0,
     137,     0,   138,     0,   139,     0,     0,   321,   140,     0,
       0,     3,     0,     4,     5,     0,     0,   284,   285,   286,
       6,   141,   287,     0,   142,   288,     0,     0,   143,   128,
     129,     7,     8,     9,     0,    11,   -80,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   130,   131,     0,
     -80,     0,   289,     0,     0,    24,    26,   132,   133,   134,
     135,   136,     0,   137,     0,   138,     0,   139,     0,     0,
     338,   140,     0,     0,     3,     0,     4,     5,     0,     0,
     284,   285,   286,     6,   141,   287,     0,   142,   288,     0,
       0,   143,   128,   129,     7,     8,     9,     0,    11,   -80,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     130,   131,     0,   -80,     0,   289,     0,     0,    24,    26,
     132,   133,   134,   135,   136,     0,   137,     0,   138,     0,
     139,     0,     0,   339,   140,     0,     0,     3,     0,     4,
       5,     0,     0,   284,   285,   286,     6,   141,   287,     0,
     142,   288,     0,     0,   143,   128,   129,     7,     8,     9,
       0,    11,   -80,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   130,   131,     0,   -80,     0,   289,     0,
       0,    24,    26,   132,   133,   134,   135,   136,     0,   137,
       0,   138,     0,   139,     0,     0,   352,   140,     0,     0,
       3,     0,     4,     5,     0,     0,   284,   285,   286,     6,
     141,   287,     0,   142,   288,     0,     0,   143,   128,   129,
       7,     8,     9,     0,    11,   -80,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   130,   131,     0,   -80,
       0,   289,     0,     0,    24,    26,   132,   133,   134,   135,
     136,     0,   137,     0,   138,     0,   139,     0,     0,   353,
     140,     0,     0,     3,     0,     4,     5,     0,     0,   284,
     285,   286,     6,   141,   287,     0,   142,   288,     0,     0,
     143,   128,   129,     7,     8,     9,     0,    11,   -80,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   130,
     131,     0,   -80,     0,   289,     0,     0,    24,    26,   132,
     133,   134,   135,   136,     0,   137,     0,   138,     0,   139,
       0,     0,   359,   140,     0,     0,   128,   129,     0,     0,
       0,     0,     0,     0,     0,     0,   141,     0,     0,   142,
       0,     0,     0,   143,   130,   131,     0,     0,     0,     0,
       0,     0,    24,    26,   132,   133,   134,   135,   136,     0,
     137,     0,   138,   248,   139,     0,     0,     0,   140,     0,
       0,   128,   129,     0,     0,     0,     0,     0,     0,     0,
       0,   141,     0,     0,   142,     0,     0,     0,   143,   130,
     131,     0,     0,     0,     0,     0,     0,    24,    26,   132,
     133,   134,   135,   136,     0,   137,     0,   138,     0,   139,
       0,   326,     0,   140,     0,     0,   128,   129,     0,     0,
       0,     0,     0,     0,     0,     0,   141,     0,     0,   142,
       0,     0,     0,   143,   130,   131,     0,     0,     0,     0,
       0,     0,    24,    26,   132,   133,   134,   135,   136,     0,
     137,     0,   138,     0,   139,     0,   345,     0,   140,     0,
       0,   128,   129,     0,     0,     0,     0,     0,     0,     0,
       0,   141,     0,     0,   142,     0,     0,     0,   143,   130,
     131,     0,     0,     0,     0,     0,     0,    24,    26,   132,
     133,   134,   135,   136,     0,   137,     0,   138,     0,   139,
       0,   356,     0,   140,   109,     0,     0,     0,     0,     0,
       0,     0,    59,     0,     0,     0,   141,    60,     0,   142,
       0,     0,     0,   143,     0,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,     0,     0,   110,    72,
     111,     0,     0,     0,    24,    59,    97,     0,     0,     0,
      60,     0,    73,     0,    74,     0,    75,     0,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,     0,
       0,     0,    72,     0,     0,     0,     0,    24,    59,     0,
       0,     0,     0,    60,     0,    73,     0,    74,     0,    98,
       0,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,     0,     2,     3,    72,     4,     5,     0,     0,
      24,     0,     0,     6,     0,     0,     0,     0,    73,     0,
      74,     0,    75,     0,     7,     8,     9,    10,    11,   -80,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   -80,     0,     0,     0,    12
  };

  const short
  Parser::yycheck_[] =
  {
       6,     7,     8,   116,    73,   100,    75,     1,   283,     1,
      74,   139,    81,    21,    13,     1,     1,    72,     5,    44,
      56,    56,    59,    78,    78,   138,    95,    23,   303,    98,
      56,    52,    53,    38,    45,    72,    72,    72,    44,    45,
      45,    47,    45,    39,   108,    41,    72,    56,     5,    45,
     325,   326,    39,    78,    41,    60,   125,   185,    45,    23,
     124,    82,    78,    72,    58,    73,    58,    73,   343,    75,
     345,    26,    58,    58,   187,    81,   140,    56,   206,    78,
     208,   356,    39,    56,    41,    40,    19,    20,    45,    95,
     218,    58,    98,    72,    72,    55,   209,    57,    73,    72,
      78,   170,    45,    46,    37,    38,    73,    78,    45,    69,
      70,   180,    45,    46,    47,    48,    49,    50,    51,   125,
      53,   127,    55,    60,    57,    58,    58,    80,    61,    78,
      83,    59,    58,    71,    45,    73,   205,    48,   266,    78,
      72,    74,    21,   212,    77,    73,    72,    58,    81,    61,
      62,    63,    64,    19,    20,   219,    59,   285,   222,   223,
     194,   195,   196,   197,   170,    45,    71,   262,    73,    67,
      68,    37,    38,    45,   180,    45,   289,    65,    66,    45,
      46,    47,    48,    49,    50,    51,    45,    53,   257,    55,
     259,    57,   261,   306,   307,    61,    50,    51,    71,   205,
     269,   202,   203,   204,    71,    72,   212,   213,    74,    59,
     323,    77,    16,    17,    59,    81,     7,     8,   192,   193,
     200,   201,     1,    45,     3,     4,    45,   340,   198,   199,
      78,    10,    78,    72,   347,    78,    78,    54,    70,   163,
      60,   354,    60,    48,    23,    24,    25,    26,    72,    58,
      79,   257,    75,   259,     6,   261,    72,    54,    45,    74,
      45,    40,   186,   269,   188,   189,   190,   191,   192,   193,
     194,   195,   196,   197,   198,   199,   200,   201,   202,   203,
     204,    60,     1,    76,     3,     4,    78,    62,     7,     8,
       9,    10,    78,    12,    71,    59,    15,    62,    78,    62,
      19,    20,    21,    22,    23,    78,    25,    26,    59,    59,
      55,    55,    78,    59,    45,    55,    78,    78,    37,    38,
      78,    40,    78,    42,    78,    59,    45,    46,    47,    48,
      49,    50,    51,    71,    53,    78,    55,    18,    57,    18,
     264,    60,    61,     1,    83,     1,    11,     3,     4,    58,
     264,     7,     8,     9,    10,    74,    12,   188,    77,    15,
     186,   189,    81,    19,    20,    21,    22,    23,   344,    25,
      26,   222,    -1,   339,    -1,    -1,   190,    -1,   191,    -1,
      -1,    37,    38,    -1,    40,    -1,    42,    -1,    -1,    45,
      46,    47,    48,    49,    50,    51,    -1,    53,    -1,    55,
      -1,    57,    -1,    -1,    60,    61,    -1,    -1,     1,    -1,
       3,     4,    -1,    -1,     7,     8,     9,    10,    74,    12,
      -1,    77,    15,    -1,    -1,    81,    19,    20,    21,    22,
      23,    -1,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    38,    -1,    40,    -1,    42,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    -1,    55,    -1,    57,    -1,    -1,    60,    61,    -1,
      -1,     1,    -1,     3,     4,    -1,    -1,     7,     8,     9,
      10,    74,    12,    -1,    77,    15,    -1,    -1,    81,    19,
      20,    21,    22,    23,    -1,    25,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,
      40,    -1,    42,    -1,    -1,    45,    46,    47,    48,    49,
      50,    51,    -1,    53,    -1,    55,    -1,    57,    -1,    -1,
      60,    61,    -1,    -1,     1,    -1,     3,     4,    -1,    -1,
       7,     8,     9,    10,    74,    12,    -1,    77,    15,    -1,
      -1,    81,    19,    20,    21,    22,    23,    -1,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    38,    -1,    40,    -1,    42,    -1,    -1,    45,    46,
      47,    48,    49,    50,    51,    -1,    53,    -1,    55,    -1,
      57,    -1,    -1,    60,    61,    -1,    -1,     1,    -1,     3,
       4,    -1,    -1,     7,     8,     9,    10,    74,    12,    -1,
      77,    15,    -1,    -1,    81,    19,    20,    21,    22,    23,
      -1,    25,    26,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    38,    -1,    40,    -1,    42,    -1,
      -1,    45,    46,    47,    48,    49,    50,    51,    -1,    53,
      -1,    55,    -1,    57,    -1,    -1,    60,    61,    -1,    -1,
       1,    -1,     3,     4,    -1,    -1,     7,     8,     9,    10,
      74,    12,    -1,    77,    15,    -1,    -1,    81,    19,    20,
      21,    22,    23,    -1,    25,    26,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    37,    38,    -1,    40,
      -1,    42,    -1,    -1,    45,    46,    47,    48,    49,    50,
      51,    -1,    53,    -1,    55,    -1,    57,    -1,    -1,    60,
      61,    -1,    -1,     1,    -1,     3,     4,    -1,    -1,     7,
       8,     9,    10,    74,    12,    -1,    77,    15,    -1,    -1,
      81,    19,    20,    21,    22,    23,    -1,    25,    26,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    -1,    40,    -1,    42,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    -1,    53,    -1,    55,    -1,    57,
      -1,    -1,    60,    61,    -1,    -1,    19,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    77,
      -1,    -1,    -1,    81,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    -1,    55,    56,    57,    -1,    -1,    -1,    61,    -1,
      -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    -1,    -1,    77,    -1,    -1,    -1,    81,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    -1,    53,    -1,    55,    -1,    57,
      -1,    59,    -1,    61,    -1,    -1,    19,    20,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    74,    -1,    -1,    77,
      -1,    -1,    -1,    81,    37,    38,    -1,    -1,    -1,    -1,
      -1,    -1,    45,    46,    47,    48,    49,    50,    51,    -1,
      53,    -1,    55,    -1,    57,    -1,    59,    -1,    61,    -1,
      -1,    19,    20,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    74,    -1,    -1,    77,    -1,    -1,    -1,    81,    37,
      38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    46,    47,
      48,    49,    50,    51,    -1,    53,    -1,    55,    -1,    57,
      -1,    59,    -1,    61,     5,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    13,    -1,    -1,    -1,    74,    18,    -1,    77,
      -1,    -1,    -1,    81,    -1,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    -1,    -1,    39,    40,
      41,    -1,    -1,    -1,    45,    13,    14,    -1,    -1,    -1,
      18,    -1,    53,    -1,    55,    -1,    57,    -1,    26,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    -1,
      -1,    -1,    40,    -1,    -1,    -1,    -1,    45,    13,    -1,
      -1,    -1,    -1,    18,    -1,    53,    -1,    55,    -1,    57,
      -1,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    -1,     0,     1,    40,     3,     4,    -1,    -1,
      45,    -1,    -1,    10,    -1,    -1,    -1,    -1,    53,    -1,
      55,    -1,    57,    -1,    21,    22,    23,    24,    25,    26,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    40,    -1,    -1,    -1,    44
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    85,     0,     1,     3,     4,    10,    21,    22,    23,
      24,    25,    44,    86,    87,    88,   107,   108,   109,   110,
     113,   152,    44,    78,    45,    93,    46,    89,    93,    89,
      93,    45,   109,    78,    91,    78,    78,    26,    40,    99,
     100,    78,    78,    73,    21,    21,    59,    45,    23,    39,
      41,    45,    92,    45,    45,    45,    93,    93,   111,    13,
      18,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    40,    53,    55,    57,    93,    98,    99,   100,
     106,    71,    59,    59,    60,    87,   108,   110,   112,   113,
     152,    45,    45,    98,   103,   104,    98,    14,    57,    97,
      98,   101,   101,    78,    78,    78,    78,    56,    72,     5,
      39,    41,    98,   105,    72,    98,    54,    95,    94,    95,
      60,   102,   104,    60,    70,   104,    48,    72,    19,    20,
      37,    38,    47,    48,    49,    50,    51,    53,    55,    57,
      61,    74,    77,    81,    89,    90,    93,    96,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127,   128,   129,   130,   132,   133,   135,   137,    45,
     104,    98,    58,    58,    93,   114,    58,   115,   134,    13,
      78,   104,   138,   139,    59,    72,    80,    83,    79,    75,
      76,    74,    67,    68,    61,    62,    63,    64,    65,    66,
      50,    51,    52,    53,    82,     6,    54,   128,    55,    57,
      69,    70,    71,    73,    98,    58,    56,    58,    72,    78,
      98,    45,    72,    78,   136,   115,   118,   128,   114,   119,
     120,   121,   122,   123,   123,   124,   124,   124,   124,   125,
     125,   126,   126,   127,   127,   127,    98,   115,    56,   115,
     131,   114,    45,    45,    98,    93,   115,   104,    62,    71,
     139,   104,    45,    60,    71,    56,    72,    58,    78,    71,
      98,    59,    98,    98,    95,   116,   115,    98,    62,   140,
      62,    78,    78,    59,     7,     8,     9,    12,    15,    42,
      60,    87,   107,   108,   113,   114,   141,   142,   143,   146,
     147,   151,   152,    59,   140,   115,    55,    55,   114,    78,
      78,    78,    78,    78,    78,    78,   140,    60,   114,   114,
      59,    60,    56,    56,   148,    59,    59,   114,    38,    45,
      60,   149,   150,   140,   140,   144,    45,    71,    60,    60,
      16,    17,   145,    59,   144,    59,   114,    55,   140,   145,
     140,   114,    60,    60,    56,    78,    59,   114,   140,    60
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    84,    85,    85,    85,    86,    86,    86,    86,    86,
      86,    87,    87,    87,    87,    87,    87,    88,    88,    89,
      90,    91,    91,    92,    92,    92,    93,    93,    94,    94,
      95,    96,    96,    96,    96,    96,    96,    96,    97,    97,
      97,    98,    98,    98,    98,    98,    98,    98,    99,   100,
     101,   101,   102,   102,   103,   103,   104,   104,   105,   105,
     105,   106,   106,   106,   106,   106,   106,   106,   106,   106,
     106,   106,   106,   107,   107,   107,   107,   108,   108,   108,
     109,   109,   110,   111,   111,   112,   112,   112,   112,   112,
     113,   114,   114,   115,   115,   116,   116,   117,   117,   118,
     118,   119,   119,   120,   120,   121,   121,   122,   122,   122,
     123,   123,   123,   123,   123,   124,   124,   124,   125,   125,
     125,   126,   126,   126,   126,   127,   127,   128,   128,   129,
     129,   129,   129,   129,   129,   129,   130,   130,   130,   130,
     130,   130,   131,   131,   132,   132,   132,   132,   132,   132,
     133,   133,   134,   134,   135,   136,   136,   137,   137,   137,
     138,   138,   139,   140,   140,   141,   141,   141,   141,   141,
     141,   141,   141,   142,   142,   142,   143,   143,   144,   144,
     144,   145,   145,   145,   146,   147,   148,   148,   149,   150,
     150,   150,   151,   151,   151,   151,   152,   152
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       1,     6,     6,     3,     3,     5,     3,     1,     1,     1,
       1,     0,     2,     1,     1,     1,     3,     1,     0,     1,
       2,     1,     1,     1,     1,     1,     1,     1,     4,     1,
       5,     5,     2,     6,     1,     1,     1,     1,     5,     5,
       0,     2,     5,     7,     4,     2,     0,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     4,     4,     2,     2,     4,     2,     2,
       0,     1,     5,     0,     2,     2,     2,     2,     2,     1,
       2,     1,     3,     1,     3,     1,     5,     1,     3,     1,
       3,     1,     3,     1,     3,     1,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     1,     3,     3,     3,     1,     3,     1,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     4,     3,
       3,     3,     1,     3,     1,     1,     3,     1,     1,     1,
       3,     2,     1,     3,     4,     0,     4,     9,     9,     7,
       3,     1,     4,     0,     2,     2,     2,     2,     2,     2,
       2,     2,     1,     1,     1,     1,     9,     7,     0,     8,
       6,     0,     4,     2,     7,     5,     0,     2,     6,     0,
       1,     2,     1,     1,     2,     1,     2,     2
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "$end", "error", "$undefined", "\"keyword let\"", "\"keyword var\"",
  "\"keyword mut\"", "\"keyword as\"", "\"keyword break\"",
  "\"keyword return\"", "\"keyword continue\"", "\"keyword use\"",
  "\"keyword for\"", "\"keyword while\"", "\"keyword void\"",
  "\"keyword auto\"", "\"keyword if\"", "\"keyword else\"",
  "\"keyword elif\"", "\"keyword bool\"", "\"keyword true\"",
  "\"keyword false\"", "\"keyword import\"", "\"keyword from\"",
  "\"keyword export\"", "\"keyword mod\"", "\"keyword type\"",
  "\"keyword comp\"", "\"keyword u8\"", "\"keyword u16\"",
  "\"keyword u32\"", "\"keyword u64\"", "\"keyword i8\"",
  "\"keyword i16\"", "\"keyword i32\"", "\"keyword i64\"",
  "\"keyword f32\"", "\"keyword f64\"", "\"nullptr\"", "\"keyword move\"",
  "\"keyword unique\"", "\"keyword union\"", "\"keyword ref\"",
  "\"keyword match\"", "\"unknown character\"", "\"end of file\"",
  "\"identifier\"", "\"string\"", "\"character\"", "\"integer constant\"",
  "\" float constant\"", "\"-\"", "\"+\"", "\"/\"", "\"*\"", "\"=\"",
  "\"(\"", "\")\"", "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"<\"", "\">\"",
  "\">=\"", "\"<=\"", "\">>\"", "\"<<\"", "\"==\"", "\"!=\"", "\".\"",
  "\"->\"", "\":\"", "\",\"", "\"::\"", "\"&\"", "\"|\"", "\"^\"", "\"~\"",
  "\";\"", "\"&&\"", "\"||\"", "\"!\"", "\"%\"", "\"?\"", "$accept",
  "STATEMENTS", "STATEMENT", "declare_statement", "declare", "str",
  "character", "variable_traits", "variable_trait", "var_name",
  "optional_init_statement", "init_statement", "const_value",
  "typename_incomplete", "typename", "comp_type", "union_type",
  "comp_decl_list", "comp_decl_item", "func_para_typelist",
  "func_para_traits", "func_para_trait", "basictype", "import_statement",
  "type_statement", "opt_export", "mod_statement", "inmod_satements",
  "inmod_satement", "use_statement", "exp", "assignment_exp",
  "conditional_exp", "logical_or_exp", "logical_and_exp",
  "inclusive_or_exp", "exclusive_or_exp", "and_exp", "equality_exp",
  "relational_exp", "shift_expression", "additive_exp", "mult_exp",
  "cast_exp", "unary_exp", "unary_operator", "postfix_exp",
  "argument_exp_list", "primary_exp", "array_literal", "init_list_array",
  "compound_literal", "init_list_comp", "function_literal",
  "parameters_list", "parameter_decl", "function_body",
  "function_statement", "branch_statement", "if_statement",
  "elif_statement", "else_statement", "while_statement", "match_statement",
  "match_list", "match_item", "match_type", "jump_statement",
  "error_statement", YY_NULLPTR
  };

#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   155,   155,   160,   161,   172,   173,   174,   175,   176,
     177,   181,   182,   183,   184,   185,   189,   196,   197,   200,
     202,   205,   206,   209,   210,   211,   215,   216,   219,   221,
     224,   227,   228,   229,   230,   231,   232,   233,   238,   239,
     240,   243,   244,   245,   246,   247,   248,   249,   253,   256,
     258,   260,   263,   264,   270,   271,   273,   274,   277,   278,
     279,   282,   283,   284,   285,   286,   287,   288,   289,   290,
     291,   292,   293,   297,   298,   299,   300,   304,   305,   306,
     308,   310,   314,   316,   318,   321,   322,   323,   324,   325,
     329,   332,   333,   335,   336,   338,   339,   341,   342,   344,
     345,   347,   348,   350,   351,   353,   354,   356,   357,   358,
     360,   361,   362,   363,   364,   366,   367,   368,   370,   371,
     372,   374,   375,   376,   377,   379,   380,   382,   383,   385,
     385,   385,   385,   385,   385,   385,   387,   388,   389,   390,
     391,   392,   394,   395,   397,   398,   399,   400,   401,   402,
     405,   406,   409,   410,   413,   415,   417,   421,   422,   423,
     429,   430,   433,   435,   437,   440,   441,   442,   443,   444,
     445,   446,   447,   451,   452,   453,   456,   457,   462,   464,
     465,   470,   472,   473,   479,   482,   484,   486,   489,   491,
     493,   494,   498,   499,   500,   501,   505,   506
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 37 "parser.y"
} // rmmc
#line 1538 "parser.cc"

#line 510 "parser.y"


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
