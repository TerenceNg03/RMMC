// A Bison parser, made by GNU Bison 3.5.1.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file parser.hh
 ** Define the rmmc::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.

#ifndef YY_YY_PARSER_HH_INCLUDED
# define YY_YY_PARSER_HH_INCLUDED
// "%code requires" blocks.
#line 12 "parser.y"

	#include "driver.hh"
	#include "location.hh"
	#include "position.hh"
	#include "rmm_types.hh"
	#include "rmm_utility.hh"

#line 56 "parser.hh"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif
# include "location.hh"

#ifndef YY_ASSERT
# include <cassert>
# define YY_ASSERT assert
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

#line 38 "parser.y"
namespace rmmc {
#line 191 "parser.hh"




  /// A Bison parser.
  class Parser
  {
  public:
#ifndef YYSTYPE
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class semantic_type
  {
  public:
    /// Type of *this.
    typedef semantic_type self_type;

    /// Empty construction.
    semantic_type () YY_NOEXCEPT
      : yybuffer_ ()
    {}

    /// Construct and fill.
    template <typename T>
    semantic_type (YY_RVREF (T) t)
    {
      YY_ASSERT (sizeof (T) <= size);
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

    /// Destruction, allowed only if empty.
    ~semantic_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
    /// Prohibit blind copies.
    self_type& operator= (const self_type&);
    semantic_type (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // " float constant"
      char dummy1[sizeof (double)];

      // "integer constant"
      char dummy2[sizeof (long)];

      // "identifier"
      // "string"
      // "character"
      // str
      // var_name
      char dummy3[sizeof (std::string)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[size];
    } yybuffer_;
  };

#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m)
        : std::runtime_error (m)
        , location (l)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
        , location (s.location)
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;

      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        let = 258,
        var = 259,
        mut = 260,
        as = 261,
        break_ = 262,
        return_ = 263,
        continue_ = 264,
        use = 265,
        for_ = 266,
        while_ = 267,
        void_ = 268,
        auto_ = 269,
        if_ = 270,
        else_ = 271,
        elif = 272,
        bool_ = 273,
        true_ = 274,
        false_ = 275,
        import_ = 276,
        from = 277,
        export_ = 278,
        mod = 279,
        type = 280,
        comp = 281,
        u8 = 282,
        u16 = 283,
        u32 = 284,
        u64 = 285,
        i8 = 286,
        i16 = 287,
        i32 = 288,
        i64 = 289,
        f32 = 290,
        f64 = 291,
        nullptr_ = 292,
        move = 293,
        unique = 294,
        union_ = 295,
        ref = 296,
        match = 297,
        unknown = 298,
        eof = 299,
        id = 300,
        rawstr = 301,
        rawchar = 302,
        long_ = 303,
        float_ = 304,
        minus = 305,
        plus = 306,
        div = 307,
        mul = 308,
        assign = 309,
        roundbl = 310,
        roundbr = 311,
        boxbl = 312,
        boxnr = 313,
        curlybl = 314,
        curlybr = 315,
        lt = 316,
        gt = 317,
        ge = 318,
        le = 319,
        shiftright = 320,
        shiftleft = 321,
        eq = 322,
        noteq = 323,
        point = 324,
        leftarror = 325,
        colon = 326,
        comma = 327,
        doublecolon = 328,
        bitand_ = 329,
        bitor_ = 330,
        bitxor_ = 331,
        bitnot_ = 332,
        semicolon = 333,
        and_ = 334,
        or_ = 335,
        not_ = 336,
        math_mod = 337,
        q_mark = 338
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef signed char token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get ().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ()
        : value ()
        , location ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that);
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, location_type&& l)
        : Base (t)
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const location_type& l)
        : Base (t)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, double&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const double& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, long&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const long& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, std::string&& v, location_type&& l)
        : Base (t)
        , value (std::move (v))
        , location (std::move (l))
      {}
#else
      basic_symbol (typename Base::kind_type t, const std::string& v, const location_type& l)
        : Base (t)
        , value (v)
        , location (l)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }

      /// Destroy contents, and record that is empty.
      void clear ()
      {
        // User destructor.
        symbol_number_type yytype = this->type_get ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yytype)
        {
       default:
          break;
        }

        // Type destructor.
switch (yytype)
    {
      case 49: // " float constant"
        value.template destroy< double > ();
        break;

      case 48: // "integer constant"
        value.template destroy< long > ();
        break;

      case 45: // "identifier"
      case 46: // "string"
      case 47: // "character"
      case 89: // str
      case 93: // var_name
        value.template destroy< std::string > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_type (by_type&& that);
#endif

      /// Copy constructor.
      by_type (const by_type& that);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_type>
    {
      /// Superclass.
      typedef basic_symbol<by_type> super_type;

      /// Empty symbol.
      symbol_type () {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, location_type l)
        : super_type(token_type (tok), std::move (l))
      {
        YY_ASSERT (tok == 0 || tok == token::let || tok == token::var || tok == token::mut || tok == token::as || tok == token::break_ || tok == token::return_ || tok == token::continue_ || tok == token::use || tok == token::for_ || tok == token::while_ || tok == token::void_ || tok == token::auto_ || tok == token::if_ || tok == token::else_ || tok == token::elif || tok == token::bool_ || tok == token::true_ || tok == token::false_ || tok == token::import_ || tok == token::from || tok == token::export_ || tok == token::mod || tok == token::type || tok == token::comp || tok == token::u8 || tok == token::u16 || tok == token::u32 || tok == token::u64 || tok == token::i8 || tok == token::i16 || tok == token::i32 || tok == token::i64 || tok == token::f32 || tok == token::f64 || tok == token::nullptr_ || tok == token::move || tok == token::unique || tok == token::union_ || tok == token::ref || tok == token::match || tok == token::unknown || tok == token::eof || tok == token::minus || tok == token::plus || tok == token::div || tok == token::mul || tok == token::assign || tok == token::roundbl || tok == token::roundbr || tok == token::boxbl || tok == token::boxnr || tok == token::curlybl || tok == token::curlybr || tok == token::lt || tok == token::gt || tok == token::ge || tok == token::le || tok == token::shiftright || tok == token::shiftleft || tok == token::eq || tok == token::noteq || tok == token::point || tok == token::leftarror || tok == token::colon || tok == token::comma || tok == token::doublecolon || tok == token::bitand_ || tok == token::bitor_ || tok == token::bitxor_ || tok == token::bitnot_ || tok == token::semicolon || tok == token::and_ || tok == token::or_ || tok == token::not_ || tok == token::math_mod || tok == token::q_mark);
      }
#else
      symbol_type (int tok, const location_type& l)
        : super_type(token_type (tok), l)
      {
        YY_ASSERT (tok == 0 || tok == token::let || tok == token::var || tok == token::mut || tok == token::as || tok == token::break_ || tok == token::return_ || tok == token::continue_ || tok == token::use || tok == token::for_ || tok == token::while_ || tok == token::void_ || tok == token::auto_ || tok == token::if_ || tok == token::else_ || tok == token::elif || tok == token::bool_ || tok == token::true_ || tok == token::false_ || tok == token::import_ || tok == token::from || tok == token::export_ || tok == token::mod || tok == token::type || tok == token::comp || tok == token::u8 || tok == token::u16 || tok == token::u32 || tok == token::u64 || tok == token::i8 || tok == token::i16 || tok == token::i32 || tok == token::i64 || tok == token::f32 || tok == token::f64 || tok == token::nullptr_ || tok == token::move || tok == token::unique || tok == token::union_ || tok == token::ref || tok == token::match || tok == token::unknown || tok == token::eof || tok == token::minus || tok == token::plus || tok == token::div || tok == token::mul || tok == token::assign || tok == token::roundbl || tok == token::roundbr || tok == token::boxbl || tok == token::boxnr || tok == token::curlybl || tok == token::curlybr || tok == token::lt || tok == token::gt || tok == token::ge || tok == token::le || tok == token::shiftright || tok == token::shiftleft || tok == token::eq || tok == token::noteq || tok == token::point || tok == token::leftarror || tok == token::colon || tok == token::comma || tok == token::doublecolon || tok == token::bitand_ || tok == token::bitor_ || tok == token::bitxor_ || tok == token::bitnot_ || tok == token::semicolon || tok == token::and_ || tok == token::or_ || tok == token::not_ || tok == token::math_mod || tok == token::q_mark);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, double v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::float_);
      }
#else
      symbol_type (int tok, const double& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::float_);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, long v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::long_);
      }
#else
      symbol_type (int tok, const long& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::long_);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, std::string v, location_type l)
        : super_type(token_type (tok), std::move (v), std::move (l))
      {
        YY_ASSERT (tok == token::id || tok == token::rawstr || tok == token::rawchar);
      }
#else
      symbol_type (int tok, const std::string& v, const location_type& l)
        : super_type(token_type (tok), v, l)
      {
        YY_ASSERT (tok == token::id || tok == token::rawstr || tok == token::rawchar);
      }
#endif
    };

    /// Build a parser object.
    Parser (rmmc::Driver &driver_yyarg);
    virtual ~Parser ();

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    // Implementation of make_symbol for each symbol type.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_let (location_type l)
      {
        return symbol_type (token::let, std::move (l));
      }
#else
      static
      symbol_type
      make_let (const location_type& l)
      {
        return symbol_type (token::let, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_var (location_type l)
      {
        return symbol_type (token::var, std::move (l));
      }
#else
      static
      symbol_type
      make_var (const location_type& l)
      {
        return symbol_type (token::var, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_mut (location_type l)
      {
        return symbol_type (token::mut, std::move (l));
      }
#else
      static
      symbol_type
      make_mut (const location_type& l)
      {
        return symbol_type (token::mut, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_as (location_type l)
      {
        return symbol_type (token::as, std::move (l));
      }
#else
      static
      symbol_type
      make_as (const location_type& l)
      {
        return symbol_type (token::as, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_break_ (location_type l)
      {
        return symbol_type (token::break_, std::move (l));
      }
#else
      static
      symbol_type
      make_break_ (const location_type& l)
      {
        return symbol_type (token::break_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_return_ (location_type l)
      {
        return symbol_type (token::return_, std::move (l));
      }
#else
      static
      symbol_type
      make_return_ (const location_type& l)
      {
        return symbol_type (token::return_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_continue_ (location_type l)
      {
        return symbol_type (token::continue_, std::move (l));
      }
#else
      static
      symbol_type
      make_continue_ (const location_type& l)
      {
        return symbol_type (token::continue_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_use (location_type l)
      {
        return symbol_type (token::use, std::move (l));
      }
#else
      static
      symbol_type
      make_use (const location_type& l)
      {
        return symbol_type (token::use, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_for_ (location_type l)
      {
        return symbol_type (token::for_, std::move (l));
      }
#else
      static
      symbol_type
      make_for_ (const location_type& l)
      {
        return symbol_type (token::for_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_while_ (location_type l)
      {
        return symbol_type (token::while_, std::move (l));
      }
#else
      static
      symbol_type
      make_while_ (const location_type& l)
      {
        return symbol_type (token::while_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_void_ (location_type l)
      {
        return symbol_type (token::void_, std::move (l));
      }
#else
      static
      symbol_type
      make_void_ (const location_type& l)
      {
        return symbol_type (token::void_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_auto_ (location_type l)
      {
        return symbol_type (token::auto_, std::move (l));
      }
#else
      static
      symbol_type
      make_auto_ (const location_type& l)
      {
        return symbol_type (token::auto_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_if_ (location_type l)
      {
        return symbol_type (token::if_, std::move (l));
      }
#else
      static
      symbol_type
      make_if_ (const location_type& l)
      {
        return symbol_type (token::if_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_else_ (location_type l)
      {
        return symbol_type (token::else_, std::move (l));
      }
#else
      static
      symbol_type
      make_else_ (const location_type& l)
      {
        return symbol_type (token::else_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_elif (location_type l)
      {
        return symbol_type (token::elif, std::move (l));
      }
#else
      static
      symbol_type
      make_elif (const location_type& l)
      {
        return symbol_type (token::elif, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_bool_ (location_type l)
      {
        return symbol_type (token::bool_, std::move (l));
      }
#else
      static
      symbol_type
      make_bool_ (const location_type& l)
      {
        return symbol_type (token::bool_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_true_ (location_type l)
      {
        return symbol_type (token::true_, std::move (l));
      }
#else
      static
      symbol_type
      make_true_ (const location_type& l)
      {
        return symbol_type (token::true_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_false_ (location_type l)
      {
        return symbol_type (token::false_, std::move (l));
      }
#else
      static
      symbol_type
      make_false_ (const location_type& l)
      {
        return symbol_type (token::false_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_import_ (location_type l)
      {
        return symbol_type (token::import_, std::move (l));
      }
#else
      static
      symbol_type
      make_import_ (const location_type& l)
      {
        return symbol_type (token::import_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_from (location_type l)
      {
        return symbol_type (token::from, std::move (l));
      }
#else
      static
      symbol_type
      make_from (const location_type& l)
      {
        return symbol_type (token::from, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_export_ (location_type l)
      {
        return symbol_type (token::export_, std::move (l));
      }
#else
      static
      symbol_type
      make_export_ (const location_type& l)
      {
        return symbol_type (token::export_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_mod (location_type l)
      {
        return symbol_type (token::mod, std::move (l));
      }
#else
      static
      symbol_type
      make_mod (const location_type& l)
      {
        return symbol_type (token::mod, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_type (location_type l)
      {
        return symbol_type (token::type, std::move (l));
      }
#else
      static
      symbol_type
      make_type (const location_type& l)
      {
        return symbol_type (token::type, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_comp (location_type l)
      {
        return symbol_type (token::comp, std::move (l));
      }
#else
      static
      symbol_type
      make_comp (const location_type& l)
      {
        return symbol_type (token::comp, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_u8 (location_type l)
      {
        return symbol_type (token::u8, std::move (l));
      }
#else
      static
      symbol_type
      make_u8 (const location_type& l)
      {
        return symbol_type (token::u8, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_u16 (location_type l)
      {
        return symbol_type (token::u16, std::move (l));
      }
#else
      static
      symbol_type
      make_u16 (const location_type& l)
      {
        return symbol_type (token::u16, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_u32 (location_type l)
      {
        return symbol_type (token::u32, std::move (l));
      }
#else
      static
      symbol_type
      make_u32 (const location_type& l)
      {
        return symbol_type (token::u32, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_u64 (location_type l)
      {
        return symbol_type (token::u64, std::move (l));
      }
#else
      static
      symbol_type
      make_u64 (const location_type& l)
      {
        return symbol_type (token::u64, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_i8 (location_type l)
      {
        return symbol_type (token::i8, std::move (l));
      }
#else
      static
      symbol_type
      make_i8 (const location_type& l)
      {
        return symbol_type (token::i8, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_i16 (location_type l)
      {
        return symbol_type (token::i16, std::move (l));
      }
#else
      static
      symbol_type
      make_i16 (const location_type& l)
      {
        return symbol_type (token::i16, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_i32 (location_type l)
      {
        return symbol_type (token::i32, std::move (l));
      }
#else
      static
      symbol_type
      make_i32 (const location_type& l)
      {
        return symbol_type (token::i32, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_i64 (location_type l)
      {
        return symbol_type (token::i64, std::move (l));
      }
#else
      static
      symbol_type
      make_i64 (const location_type& l)
      {
        return symbol_type (token::i64, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_f32 (location_type l)
      {
        return symbol_type (token::f32, std::move (l));
      }
#else
      static
      symbol_type
      make_f32 (const location_type& l)
      {
        return symbol_type (token::f32, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_f64 (location_type l)
      {
        return symbol_type (token::f64, std::move (l));
      }
#else
      static
      symbol_type
      make_f64 (const location_type& l)
      {
        return symbol_type (token::f64, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_nullptr_ (location_type l)
      {
        return symbol_type (token::nullptr_, std::move (l));
      }
#else
      static
      symbol_type
      make_nullptr_ (const location_type& l)
      {
        return symbol_type (token::nullptr_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_move (location_type l)
      {
        return symbol_type (token::move, std::move (l));
      }
#else
      static
      symbol_type
      make_move (const location_type& l)
      {
        return symbol_type (token::move, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_unique (location_type l)
      {
        return symbol_type (token::unique, std::move (l));
      }
#else
      static
      symbol_type
      make_unique (const location_type& l)
      {
        return symbol_type (token::unique, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_union_ (location_type l)
      {
        return symbol_type (token::union_, std::move (l));
      }
#else
      static
      symbol_type
      make_union_ (const location_type& l)
      {
        return symbol_type (token::union_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ref (location_type l)
      {
        return symbol_type (token::ref, std::move (l));
      }
#else
      static
      symbol_type
      make_ref (const location_type& l)
      {
        return symbol_type (token::ref, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_match (location_type l)
      {
        return symbol_type (token::match, std::move (l));
      }
#else
      static
      symbol_type
      make_match (const location_type& l)
      {
        return symbol_type (token::match, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_unknown (location_type l)
      {
        return symbol_type (token::unknown, std::move (l));
      }
#else
      static
      symbol_type
      make_unknown (const location_type& l)
      {
        return symbol_type (token::unknown, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_eof (location_type l)
      {
        return symbol_type (token::eof, std::move (l));
      }
#else
      static
      symbol_type
      make_eof (const location_type& l)
      {
        return symbol_type (token::eof, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_id (std::string v, location_type l)
      {
        return symbol_type (token::id, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_id (const std::string& v, const location_type& l)
      {
        return symbol_type (token::id, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_rawstr (std::string v, location_type l)
      {
        return symbol_type (token::rawstr, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_rawstr (const std::string& v, const location_type& l)
      {
        return symbol_type (token::rawstr, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_rawchar (std::string v, location_type l)
      {
        return symbol_type (token::rawchar, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_rawchar (const std::string& v, const location_type& l)
      {
        return symbol_type (token::rawchar, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_long_ (long v, location_type l)
      {
        return symbol_type (token::long_, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_long_ (const long& v, const location_type& l)
      {
        return symbol_type (token::long_, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_float_ (double v, location_type l)
      {
        return symbol_type (token::float_, std::move (v), std::move (l));
      }
#else
      static
      symbol_type
      make_float_ (const double& v, const location_type& l)
      {
        return symbol_type (token::float_, v, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_minus (location_type l)
      {
        return symbol_type (token::minus, std::move (l));
      }
#else
      static
      symbol_type
      make_minus (const location_type& l)
      {
        return symbol_type (token::minus, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_plus (location_type l)
      {
        return symbol_type (token::plus, std::move (l));
      }
#else
      static
      symbol_type
      make_plus (const location_type& l)
      {
        return symbol_type (token::plus, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_div (location_type l)
      {
        return symbol_type (token::div, std::move (l));
      }
#else
      static
      symbol_type
      make_div (const location_type& l)
      {
        return symbol_type (token::div, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_mul (location_type l)
      {
        return symbol_type (token::mul, std::move (l));
      }
#else
      static
      symbol_type
      make_mul (const location_type& l)
      {
        return symbol_type (token::mul, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_assign (location_type l)
      {
        return symbol_type (token::assign, std::move (l));
      }
#else
      static
      symbol_type
      make_assign (const location_type& l)
      {
        return symbol_type (token::assign, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_roundbl (location_type l)
      {
        return symbol_type (token::roundbl, std::move (l));
      }
#else
      static
      symbol_type
      make_roundbl (const location_type& l)
      {
        return symbol_type (token::roundbl, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_roundbr (location_type l)
      {
        return symbol_type (token::roundbr, std::move (l));
      }
#else
      static
      symbol_type
      make_roundbr (const location_type& l)
      {
        return symbol_type (token::roundbr, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_boxbl (location_type l)
      {
        return symbol_type (token::boxbl, std::move (l));
      }
#else
      static
      symbol_type
      make_boxbl (const location_type& l)
      {
        return symbol_type (token::boxbl, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_boxnr (location_type l)
      {
        return symbol_type (token::boxnr, std::move (l));
      }
#else
      static
      symbol_type
      make_boxnr (const location_type& l)
      {
        return symbol_type (token::boxnr, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_curlybl (location_type l)
      {
        return symbol_type (token::curlybl, std::move (l));
      }
#else
      static
      symbol_type
      make_curlybl (const location_type& l)
      {
        return symbol_type (token::curlybl, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_curlybr (location_type l)
      {
        return symbol_type (token::curlybr, std::move (l));
      }
#else
      static
      symbol_type
      make_curlybr (const location_type& l)
      {
        return symbol_type (token::curlybr, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_lt (location_type l)
      {
        return symbol_type (token::lt, std::move (l));
      }
#else
      static
      symbol_type
      make_lt (const location_type& l)
      {
        return symbol_type (token::lt, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_gt (location_type l)
      {
        return symbol_type (token::gt, std::move (l));
      }
#else
      static
      symbol_type
      make_gt (const location_type& l)
      {
        return symbol_type (token::gt, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ge (location_type l)
      {
        return symbol_type (token::ge, std::move (l));
      }
#else
      static
      symbol_type
      make_ge (const location_type& l)
      {
        return symbol_type (token::ge, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_le (location_type l)
      {
        return symbol_type (token::le, std::move (l));
      }
#else
      static
      symbol_type
      make_le (const location_type& l)
      {
        return symbol_type (token::le, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_shiftright (location_type l)
      {
        return symbol_type (token::shiftright, std::move (l));
      }
#else
      static
      symbol_type
      make_shiftright (const location_type& l)
      {
        return symbol_type (token::shiftright, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_shiftleft (location_type l)
      {
        return symbol_type (token::shiftleft, std::move (l));
      }
#else
      static
      symbol_type
      make_shiftleft (const location_type& l)
      {
        return symbol_type (token::shiftleft, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_eq (location_type l)
      {
        return symbol_type (token::eq, std::move (l));
      }
#else
      static
      symbol_type
      make_eq (const location_type& l)
      {
        return symbol_type (token::eq, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_noteq (location_type l)
      {
        return symbol_type (token::noteq, std::move (l));
      }
#else
      static
      symbol_type
      make_noteq (const location_type& l)
      {
        return symbol_type (token::noteq, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_point (location_type l)
      {
        return symbol_type (token::point, std::move (l));
      }
#else
      static
      symbol_type
      make_point (const location_type& l)
      {
        return symbol_type (token::point, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_leftarror (location_type l)
      {
        return symbol_type (token::leftarror, std::move (l));
      }
#else
      static
      symbol_type
      make_leftarror (const location_type& l)
      {
        return symbol_type (token::leftarror, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_colon (location_type l)
      {
        return symbol_type (token::colon, std::move (l));
      }
#else
      static
      symbol_type
      make_colon (const location_type& l)
      {
        return symbol_type (token::colon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_comma (location_type l)
      {
        return symbol_type (token::comma, std::move (l));
      }
#else
      static
      symbol_type
      make_comma (const location_type& l)
      {
        return symbol_type (token::comma, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_doublecolon (location_type l)
      {
        return symbol_type (token::doublecolon, std::move (l));
      }
#else
      static
      symbol_type
      make_doublecolon (const location_type& l)
      {
        return symbol_type (token::doublecolon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_bitand_ (location_type l)
      {
        return symbol_type (token::bitand_, std::move (l));
      }
#else
      static
      symbol_type
      make_bitand_ (const location_type& l)
      {
        return symbol_type (token::bitand_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_bitor_ (location_type l)
      {
        return symbol_type (token::bitor_, std::move (l));
      }
#else
      static
      symbol_type
      make_bitor_ (const location_type& l)
      {
        return symbol_type (token::bitor_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_bitxor_ (location_type l)
      {
        return symbol_type (token::bitxor_, std::move (l));
      }
#else
      static
      symbol_type
      make_bitxor_ (const location_type& l)
      {
        return symbol_type (token::bitxor_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_bitnot_ (location_type l)
      {
        return symbol_type (token::bitnot_, std::move (l));
      }
#else
      static
      symbol_type
      make_bitnot_ (const location_type& l)
      {
        return symbol_type (token::bitnot_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_semicolon (location_type l)
      {
        return symbol_type (token::semicolon, std::move (l));
      }
#else
      static
      symbol_type
      make_semicolon (const location_type& l)
      {
        return symbol_type (token::semicolon, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_and_ (location_type l)
      {
        return symbol_type (token::and_, std::move (l));
      }
#else
      static
      symbol_type
      make_and_ (const location_type& l)
      {
        return symbol_type (token::and_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_or_ (location_type l)
      {
        return symbol_type (token::or_, std::move (l));
      }
#else
      static
      symbol_type
      make_or_ (const location_type& l)
      {
        return symbol_type (token::or_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_not_ (location_type l)
      {
        return symbol_type (token::not_, std::move (l));
      }
#else
      static
      symbol_type
      make_not_ (const location_type& l)
      {
        return symbol_type (token::not_, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_math_mod (location_type l)
      {
        return symbol_type (token::math_mod, std::move (l));
      }
#else
      static
      symbol_type
      make_math_mod (const location_type& l)
      {
        return symbol_type (token::math_mod, l);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_q_mark (location_type l)
      {
        return symbol_type (token::q_mark, std::move (l));
      }
#else
      static
      symbol_type
      make_q_mark (const location_type& l)
      {
        return symbol_type (token::q_mark, l);
      }
#endif


  private:
    /// This class is not copyable.
    Parser (const Parser&);
    Parser& operator= (const Parser&);

    /// Stored state numbers (used for stacks).
    typedef short state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    /// In theory \a t should be a token_type, but character literals
    /// are valid, yet not members of the token_type enum.
    static token_number_type yytranslate_ (int t);

    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const unsigned char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const short yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const short yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
    // symbol of state STATE-NUM.
    static const unsigned char yystos_[];

    // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
    static const unsigned char yyr1_[];

    // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
    static const signed char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::reverse_iterator iterator;
      typedef typename S::const_reverse_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200)
        : seq_ (n)
      {}

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      std::ptrdiff_t
      ssize () const YY_NOEXCEPT
      {
        return std::ptrdiff_t (size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.rbegin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.rend ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range)
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
      stack (const stack&);
      stack& operator= (const stack&);
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1);

    /// Some specific tokens.
    static const token_number_type yy_error_token_ = 1;
    static const token_number_type yy_undef_token_ = 2;

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 1125,     ///< Last index in yytable_.
      yynnts_ = 69,  ///< Number of nonterminal symbols.
      yyfinal_ = 2, ///< Termination state number.
      yyntokens_ = 84  ///< Number of tokens.
    };


    // User arguments.
    rmmc::Driver &driver;
  };

  inline
  Parser::token_number_type
  Parser::yytranslate_ (int t)
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const token_number_type
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83
    };
    const int user_token_number_max_ = 338;

    if (t <= 0)
      return yyeof_;
    else if (t <= user_token_number_max_)
      return translate_table[t];
    else
      return yy_undef_token_;
  }

  // basic_symbol.
#if 201103L <= YY_CPLUSPLUS
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (basic_symbol&& that)
    : Base (std::move (that))
    , value ()
    , location (std::move (that.location))
  {
    switch (this->type_get ())
    {
      case 49: // " float constant"
        value.move< double > (std::move (that.value));
        break;

      case 48: // "integer constant"
        value.move< long > (std::move (that.value));
        break;

      case 45: // "identifier"
      case 46: // "string"
      case 47: // "character"
      case 89: // str
      case 93: // var_name
        value.move< std::string > (std::move (that.value));
        break;

      default:
        break;
    }

  }
#endif

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
    , location (that.location)
  {
    switch (this->type_get ())
    {
      case 49: // " float constant"
        value.copy< double > (YY_MOVE (that.value));
        break;

      case 48: // "integer constant"
        value.copy< long > (YY_MOVE (that.value));
        break;

      case 45: // "identifier"
      case 46: // "string"
      case 47: // "character"
      case 89: // str
      case 93: // var_name
        value.copy< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }



  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->type_get ())
    {
      case 49: // " float constant"
        value.move< double > (YY_MOVE (s.value));
        break;

      case 48: // "integer constant"
        value.move< long > (YY_MOVE (s.value));
        break;

      case 45: // "identifier"
      case 46: // "string"
      case 47: // "character"
      case 89: // str
      case 93: // var_name
        value.move< std::string > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

    location = YY_MOVE (s.location);
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

#if 201103L <= YY_CPLUSPLUS
  inline
  Parser::by_type::by_type (by_type&& that)
    : type (that.type)
  {
    that.clear ();
  }
#endif

  inline
  Parser::by_type::by_type (const by_type& that)
    : type (that.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const YY_NOEXCEPT
  {
    return type;
  }

#line 38 "parser.y"
} // rmmc
#line 2540 "parser.hh"



// "%code provides" blocks.
#line 21 "parser.y"


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


#line 2561 "parser.hh"


#endif // !YY_YY_PARSER_HH_INCLUDED
