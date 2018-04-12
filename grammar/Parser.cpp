// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

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


// First part of user declarations.

#line 37 "Parser.cpp" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "Parser.h"

// User implementation prologue.

#line 51 "Parser.cpp" // lalr1.cc:412
// Unqualified %code blocks.
#line 34 "parser.bison" // lalr1.cc:413

   #include <iostream>

   #include "Scanner.h"

#undef yylex
#define yylex scanner.Lex

#line 62 "Parser.cpp" // lalr1.cc:413


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
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
      *yycdebug_ << std::endl;                  \
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
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "parser.bison" // lalr1.cc:479
namespace Grammar {
#line 148 "Parser.cpp" // lalr1.cc:479

  /// Build a parser object.
  Parser::Parser (Scanner& scanner_yyarg, Program* program_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      scanner (scanner_yyarg),
      program (program_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 50: // ArgumentDeclarationList
      case 51: // NonEmptyArgumentDeclarationList
        value.move< ArgumentDeclarationList* > (that.value);
        break;

      case 55: // ArgumentsList
      case 56: // NonEmptyArgumentsList
        value.move< ArgumentsList* > (that.value);
        break;

      case 44: // ClassDeclaration
        value.move< ClassDeclaration* > (that.value);
        break;

      case 43: // ClassDeclarationList
        value.move< ClassDeclarationList* > (that.value);
        break;

      case 57: // Expression
        value.move< Expression* > (that.value);
        break;

      case 39: // ID
        value.move< Identifier > (that.value);
        break;

      case 42: // MainClass
        value.move< MainClass* > (that.value);
        break;

      case 49: // MethodDeclaration
        value.move< MethodDeclaration* > (that.value);
        break;

      case 48: // MethodDeclarationList
        value.move< MethodDeclarationList* > (that.value);
        break;

      case 54: // Statement
        value.move< Statement* > (that.value);
        break;

      case 52: // StatementList
        value.move< StatementList* > (that.value);
        break;

      case 47: // Type
        value.move< Type* > (that.value);
        break;

      case 46: // VariableDeclaration
        value.move< VariableDeclaration* > (that.value);
        break;

      case 53: // VariableDeclarationStatement
        value.move< VariableDeclarationStatement* > (that.value);
        break;

      case 45: // VariableDeclarationStatementList
        value.move< VariableDeclarationStatementList* > (that.value);
        break;

      case 37: // BOOL_VALUE
        value.move< bool > (that.value);
        break;

      case 38: // INTEGER
        value.move< int > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 50: // ArgumentDeclarationList
      case 51: // NonEmptyArgumentDeclarationList
        value.copy< ArgumentDeclarationList* > (that.value);
        break;

      case 55: // ArgumentsList
      case 56: // NonEmptyArgumentsList
        value.copy< ArgumentsList* > (that.value);
        break;

      case 44: // ClassDeclaration
        value.copy< ClassDeclaration* > (that.value);
        break;

      case 43: // ClassDeclarationList
        value.copy< ClassDeclarationList* > (that.value);
        break;

      case 57: // Expression
        value.copy< Expression* > (that.value);
        break;

      case 39: // ID
        value.copy< Identifier > (that.value);
        break;

      case 42: // MainClass
        value.copy< MainClass* > (that.value);
        break;

      case 49: // MethodDeclaration
        value.copy< MethodDeclaration* > (that.value);
        break;

      case 48: // MethodDeclarationList
        value.copy< MethodDeclarationList* > (that.value);
        break;

      case 54: // Statement
        value.copy< Statement* > (that.value);
        break;

      case 52: // StatementList
        value.copy< StatementList* > (that.value);
        break;

      case 47: // Type
        value.copy< Type* > (that.value);
        break;

      case 46: // VariableDeclaration
        value.copy< VariableDeclaration* > (that.value);
        break;

      case 53: // VariableDeclarationStatement
        value.copy< VariableDeclarationStatement* > (that.value);
        break;

      case 45: // VariableDeclarationStatementList
        value.copy< VariableDeclarationStatementList* > (that.value);
        break;

      case 37: // BOOL_VALUE
        value.copy< bool > (that.value);
        break;

      case 38: // INTEGER
        value.copy< int > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
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
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
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

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
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

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex ());
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

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
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 50: // ArgumentDeclarationList
      case 51: // NonEmptyArgumentDeclarationList
        yylhs.value.build< ArgumentDeclarationList* > ();
        break;

      case 55: // ArgumentsList
      case 56: // NonEmptyArgumentsList
        yylhs.value.build< ArgumentsList* > ();
        break;

      case 44: // ClassDeclaration
        yylhs.value.build< ClassDeclaration* > ();
        break;

      case 43: // ClassDeclarationList
        yylhs.value.build< ClassDeclarationList* > ();
        break;

      case 57: // Expression
        yylhs.value.build< Expression* > ();
        break;

      case 39: // ID
        yylhs.value.build< Identifier > ();
        break;

      case 42: // MainClass
        yylhs.value.build< MainClass* > ();
        break;

      case 49: // MethodDeclaration
        yylhs.value.build< MethodDeclaration* > ();
        break;

      case 48: // MethodDeclarationList
        yylhs.value.build< MethodDeclarationList* > ();
        break;

      case 54: // Statement
        yylhs.value.build< Statement* > ();
        break;

      case 52: // StatementList
        yylhs.value.build< StatementList* > ();
        break;

      case 47: // Type
        yylhs.value.build< Type* > ();
        break;

      case 46: // VariableDeclaration
        yylhs.value.build< VariableDeclaration* > ();
        break;

      case 53: // VariableDeclarationStatement
        yylhs.value.build< VariableDeclarationStatement* > ();
        break;

      case 45: // VariableDeclarationStatementList
        yylhs.value.build< VariableDeclarationStatementList* > ();
        break;

      case 37: // BOOL_VALUE
        yylhs.value.build< bool > ();
        break;

      case 38: // INTEGER
        yylhs.value.build< int > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 121 "parser.bison" // lalr1.cc:859
    { program = new Program(yystack_[1].value.as< MainClass* > (), yystack_[0].value.as< ClassDeclarationList* > ()); }
#line 696 "Parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 133 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< MainClass* > () = new MainClass(yystack_[5].value.as< Identifier > (), yystack_[2].value.as< Statement* > ()); }
#line 702 "Parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 137 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ClassDeclarationList* > () = nullptr; }
#line 708 "Parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 139 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ClassDeclarationList* > () = new ClassDeclarationList(yystack_[0].value.as< ClassDeclaration* > (), yystack_[1].value.as< ClassDeclarationList* > ()); }
#line 714 "Parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 146 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ClassDeclaration* > () = new ClassDeclaration(yystack_[4].value.as< Identifier > (), yystack_[2].value.as< VariableDeclarationStatementList* > (), yystack_[1].value.as< MethodDeclarationList* > ()); }
#line 720 "Parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 151 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ClassDeclaration* > () = new ClassDeclaration(yystack_[6].value.as< Identifier > (), yystack_[4].value.as< Identifier > (), yystack_[2].value.as< VariableDeclarationStatementList* > (), yystack_[1].value.as< MethodDeclarationList* > ()); }
#line 726 "Parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 155 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< VariableDeclarationStatementList* > () = nullptr; }
#line 732 "Parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 157 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< VariableDeclarationStatementList* > () = new VariableDeclarationStatementList(yystack_[0].value.as< VariableDeclarationStatement* > (), yystack_[1].value.as< VariableDeclarationStatementList* > ()); }
#line 738 "Parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 161 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< VariableDeclaration* > () = new VariableDeclaration(yystack_[1].value.as< Type* > (), yystack_[0].value.as< Identifier > ()); }
#line 744 "Parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 165 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Type* > () = new Type(TT_Array); }
#line 750 "Parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 167 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Type* > () = new Type(TT_Bool); }
#line 756 "Parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 169 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Type* > () = new Type(TT_Int); }
#line 762 "Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 171 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Type* > () = new Type(TT_Object, yystack_[0].value.as< Identifier > ()); }
#line 768 "Parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 175 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< MethodDeclarationList* > () = nullptr; }
#line 774 "Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 177 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< MethodDeclarationList* > () = new MethodDeclarationList(yystack_[0].value.as< MethodDeclaration* > (), yystack_[1].value.as< MethodDeclarationList* > ()); }
#line 780 "Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 185 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< MethodDeclaration* > () = new MethodDeclaration(yystack_[6].value.as< Identifier > (), yystack_[7].value.as< Type* > (), yystack_[4].value.as< ArgumentDeclarationList* > (), yystack_[1].value.as< StatementList* > ()); }
#line 786 "Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 192 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< MethodDeclaration* > () = new MethodDeclaration(yystack_[9].value.as< Identifier > (), yystack_[10].value.as< Type* > (), yystack_[2].value.as< Expression* > (), yystack_[7].value.as< ArgumentDeclarationList* > (), yystack_[4].value.as< StatementList* > ()); }
#line 792 "Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 196 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentDeclarationList* > () = nullptr; }
#line 798 "Parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 198 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentDeclarationList* > () = yystack_[0].value.as< ArgumentDeclarationList* > (); }
#line 804 "Parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 202 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentDeclarationList* > () = new ArgumentDeclarationList(yystack_[0].value.as< VariableDeclaration* > ()); }
#line 810 "Parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 204 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentDeclarationList* > () = new ArgumentDeclarationList(yystack_[2].value.as< VariableDeclaration* > (), yystack_[0].value.as< ArgumentDeclarationList* > ()); }
#line 816 "Parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 208 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< StatementList* > () = nullptr; }
#line 822 "Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 210 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< StatementList* > () = new StatementList(yystack_[0].value.as< Statement* > (), yystack_[1].value.as< StatementList* > ()); }
#line 828 "Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 212 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< StatementList* > () = new StatementList(yystack_[0].value.as< VariableDeclarationStatement* > (), yystack_[1].value.as< StatementList* > ()); }
#line 834 "Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 216 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< VariableDeclarationStatement* > () = new VariableDeclarationStatement(yystack_[1].value.as< VariableDeclaration* > ()); }
#line 840 "Parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 222 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Statement* > () = new NestedStatement(yystack_[1].value.as< StatementList* > ()); }
#line 846 "Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 227 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Statement* > () = new IfStatement(yystack_[4].value.as< Expression* > (), yystack_[2].value.as< Statement* > (), yystack_[0].value.as< Statement* > ()); }
#line 852 "Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 229 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Statement* > () = new WhileStatement(yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Statement* > ()); }
#line 858 "Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 231 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Statement* > () = new PrintStatement(yystack_[2].value.as< Expression* > ()); }
#line 864 "Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 233 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Statement* > () = new AssignStatement(yystack_[3].value.as< Identifier > (), yystack_[1].value.as< Expression* > ()); }
#line 870 "Parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 235 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Statement* > () = new ArrayAssignStatement(yystack_[6].value.as< Identifier > (), yystack_[4].value.as< Expression* > (), yystack_[1].value.as< Expression* > ()); }
#line 876 "Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 240 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentsList* > () = nullptr; }
#line 882 "Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 242 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentsList* > () = yystack_[0].value.as< ArgumentsList* > (); }
#line 888 "Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 246 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentsList* > () = new ArgumentsList(yystack_[0].value.as< Expression* > ()); }
#line 894 "Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 248 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentsList* > () = new ArgumentsList(yystack_[0].value.as< Expression* > (), yystack_[2].value.as< ArgumentsList* > ()); }
#line 900 "Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 251 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BinopExpression( yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Expression* > (), BOT_Plus ); }
#line 906 "Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 252 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BinopExpression( yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Expression* > (), BOT_Minus ); }
#line 912 "Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 253 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BinopExpression( yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Expression* > (), BOT_Multiply ); }
#line 918 "Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 254 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BinopExpression( yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Expression* > (), BOT_And ); }
#line 924 "Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 255 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BinopExpression( yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Expression* > (), BOT_Equal ); }
#line 930 "Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 256 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BinopExpression( yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Expression* > (), BOT_Less ); }
#line 936 "Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 258 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new ArrayItemExpression( yystack_[3].value.as< Expression* > (), yystack_[1].value.as< Expression* > () ); }
#line 942 "Parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 259 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new ArrayLengthExpression( yystack_[2].value.as< Expression* > () ); }
#line 948 "Parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 260 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new CallExpression( yystack_[5].value.as< Expression* > (), yystack_[3].value.as< Identifier > (), yystack_[1].value.as< ArgumentsList* > () ); }
#line 954 "Parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 261 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new ConstExpression( yystack_[0].value.as< int > () ); }
#line 960 "Parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 262 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BoolExpression( yystack_[0].value.as< bool > () ); }
#line 966 "Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 263 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new IdExpression( yystack_[0].value.as< Identifier > () ); }
#line 972 "Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 264 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new IdExpression( "this" ); }
#line 978 "Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 265 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new NewArrayExpression( yystack_[3].value.as< Type* > (), yystack_[1].value.as< Expression* > () ); }
#line 984 "Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 266 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new NewObjectExpression( yystack_[2].value.as< Identifier > () ); }
#line 990 "Parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 267 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new NotExpression( yystack_[0].value.as< Expression* > () ); }
#line 996 "Parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 268 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = yystack_[1].value.as< Expression* > (); }
#line 1002 "Parser.cpp" // lalr1.cc:859
    break;


#line 1006 "Parser.cpp" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
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

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
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
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
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
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

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
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type, const symbol_type&) const
  {
    return YY_("syntax error");
  }


  const signed char Parser::yypact_ninf_ = -63;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      -2,   -25,    18,   -63,    16,   -63,    39,    40,    19,   -63,
      52,    14,    46,   -63,    33,    57,    10,    81,   105,   -63,
      91,   -63,   100,    87,     5,   -63,   -63,   101,   123,   -63,
     -63,   -63,    10,   -63,    10,   126,   -63,    93,    54,   129,
     130,   -63,    95,    10,   134,   132,   140,   -63,   141,    10,
     177,    48,   -63,   -63,   -63,   142,   180,   181,     3,   131,
       1,    45,     6,     6,     6,     6,     6,   182,   -63,     6,
       3,   -63,   -63,   -63,     6,    41,   -63,     6,   -63,   -63,
     -63,    75,    83,    89,   121,   127,   -63,   133,   139,   186,
     184,   -63,     6,    48,     8,     6,     6,     6,     6,     6,
       6,    48,   183,   156,   -63,   189,   -63,   187,     6,   171,
     178,   -63,   202,   146,    69,    64,   188,   188,   -63,   -63,
     -63,     6,   -63,   -63,   179,   -63,    48,     6,   185,   -63,
     -63,    73,   -63,   196,   -63,   -63,     6,   196
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     4,     0,     1,     2,     0,     0,     5,
       0,     0,     0,     8,     0,     0,    15,     0,     0,    12,
      13,    14,     0,     0,     0,     9,     8,     0,     0,    26,
      10,     6,     0,    16,    15,     0,    11,     0,     0,     0,
       0,     7,     0,    19,     0,    21,     0,    20,     0,     0,
       0,     0,    22,    23,    23,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    17,     0,
      14,    25,    24,    27,     0,     0,    49,     0,    47,    46,
      48,     0,     0,     0,     0,     0,     3,     0,     0,    14,
       0,    52,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    31,     0,    53,     0,     0,     0,
       0,    44,     0,    41,    42,    40,    37,    38,    39,    29,
      30,     0,    18,    51,     0,    43,     0,    33,     0,    50,
      28,     0,    34,    35,    32,    45,     0,    36
  };

  const short int
  Parser::yypgoto_[] =
  {
     -63,   -63,   -63,   -63,   -63,   194,    28,   -27,   190,   -63,
     -63,   172,   169,    30,   -51,   -63,   -63,   -62
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,     6,     9,    16,    22,    23,    24,    33,
      46,    47,    60,    25,    72,   131,   132,    81
  };

  const unsigned char
  Parser::yytable_[] =
  {
      59,    82,    83,    84,    85,    37,    65,    87,    54,    68,
       1,    74,    88,    31,     4,    91,    19,    20,     5,    32,
      55,    13,    56,     7,    69,    19,    20,    14,    75,    57,
     109,    76,   111,   113,   114,   115,   116,   117,   118,    66,
      70,    77,   110,    78,    79,    80,   124,   112,    90,    21,
     119,     8,    54,    73,    10,    54,    19,    20,    11,   128,
      19,    20,    41,    15,    55,   133,    56,    55,    32,    56,
      12,    45,    17,    57,   137,   130,    57,    45,    92,   135,
      89,    93,   136,    18,    70,    94,    92,    58,    26,   101,
      71,    71,    92,    94,    28,   102,    98,    99,   100,    94,
      97,    98,    99,   100,    95,    96,    97,    98,    99,   100,
      27,    29,    95,    96,    97,    98,    99,   100,    95,    96,
      97,    98,    99,   100,    92,   103,    30,    36,    35,    39,
      92,    94,    40,    42,    44,    43,    92,    94,   104,    67,
      48,    49,    92,    94,   105,   106,    50,    62,    51,    94,
      95,    96,    97,    98,    99,   100,    95,    96,    97,    98,
      99,   100,    95,    96,    97,    98,    99,   100,    95,    96,
      97,    98,    99,   100,    92,   125,    96,    97,    98,    99,
     100,    94,    92,   129,    53,    63,    64,   108,    92,    94,
      86,   107,   121,   123,   120,    94,   134,   122,   126,    92,
      95,    96,    97,    98,    99,   100,    94,   127,    95,    96,
      97,    98,    99,   100,    95,    96,    97,    98,    99,   100,
      34,    52,   100,    61,    38,    95,    96,    97,    98,    99,
     100
  };

  const unsigned char
  Parser::yycheck_[] =
  {
      51,    63,    64,    65,    66,    32,     3,    69,     7,     8,
      12,     5,    74,     8,    39,    77,    15,    16,     0,    14,
      19,     7,    21,     7,    23,    15,    16,    13,    22,    28,
      92,    25,    24,    95,    96,    97,    98,    99,   100,    36,
      39,    35,    93,    37,    38,    39,   108,    39,    75,    39,
     101,    12,     7,     8,    14,     7,    15,    16,    39,   121,
      15,    16,     8,    17,    19,   127,    21,    19,    14,    21,
      18,    43,    39,    28,   136,   126,    28,    49,     3,     6,
      39,     6,     9,    26,    39,    10,     3,    39,     7,     6,
      60,    61,     3,    10,     3,     6,    32,    33,    34,    10,
      31,    32,    33,    34,    29,    30,    31,    32,    33,    34,
       5,    11,    29,    30,    31,    32,    33,    34,    29,    30,
      31,    32,    33,    34,     3,     4,    39,     4,    27,     3,
       3,    10,    39,     4,    39,     5,     3,    10,    11,     8,
       6,     9,     3,    10,    11,     6,     6,     5,     7,    10,
      29,    30,    31,    32,    33,    34,    29,    30,    31,    32,
      33,    34,    29,    30,    31,    32,    33,    34,    29,    30,
      31,    32,    33,    34,     3,     4,    30,    31,    32,    33,
      34,    10,     3,     4,     7,     5,     5,     3,     3,    10,
       8,     5,    36,     6,    11,    10,    11,     8,    20,     3,
      29,    30,    31,    32,    33,    34,    10,     5,    29,    30,
      31,    32,    33,    34,    29,    30,    31,    32,    33,    34,
      26,    49,    34,    54,    34,    29,    30,    31,    32,    33,
      34
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    12,    41,    42,    39,     0,    43,     7,    12,    44,
      14,    39,    18,     7,    13,    17,    45,    39,    26,    15,
      16,    39,    46,    47,    48,    53,     7,     5,     3,    11,
      39,     8,    14,    49,    45,    27,     4,    47,    48,     3,
      39,     8,     4,     5,    39,    46,    50,    51,     6,     9,
       6,     7,    51,     7,     7,    19,    21,    28,    39,    54,
      52,    52,     5,     5,     5,     3,    36,     8,     8,    23,
      39,    53,    54,     8,     5,    22,    25,    35,    37,    38,
      39,    57,    57,    57,    57,    57,     8,    57,    57,    39,
      47,    57,     3,     6,    10,    29,    30,    31,    32,    33,
      34,     6,     6,     4,    11,    11,     6,     5,     3,    57,
      54,    24,    39,    57,    57,    57,    57,    57,    57,    54,
      11,    36,     8,     6,    57,     4,    20,     5,    57,     4,
      54,    55,    56,    57,    11,     6,     9,    57
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    40,    41,    42,    43,    43,    44,    44,    45,    45,
      46,    47,    47,    47,    47,    48,    48,    49,    49,    50,
      50,    51,    51,    52,    52,    52,    53,    54,    54,    54,
      54,    54,    54,    55,    55,    56,    56,    57,    57,    57,
      57,    57,    57,    57,    57,    57,    57,    57,    57,    57,
      57,    57,    57,    57
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,    17,     0,     2,     6,     8,     0,     2,
       2,     3,     1,     1,     1,     0,     2,     9,    12,     0,
       1,     1,     3,     0,     2,     2,     2,     3,     7,     5,
       5,     4,     7,     0,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     4,     3,     6,     1,     1,     1,     1,
       5,     4,     2,     3
  };


#if YYDEBUG
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "END", "error", "$undefined", "\"[\"", "\"]\"", "\"(\"", "\")\"",
  "\"{\"", "\"}\"", "\",\"", "\".\"", "\";\"", "CLASS", "EXTENDS",
  "PUBLIC", "BOOLEAN", "INT", "VOID", "STATIC", "IF", "ELSE", "WHILE",
  "NEW", "RETURN", "LENGTH", "THIS", "MAIN", "STRING", "PRINT", "EQUAL",
  "LESS", "AND", "PLUS", "MINUS", "MULT", "NOT", "ASSIGN", "BOOL_VALUE",
  "INTEGER", "ID", "$accept", "Goal", "MainClass", "ClassDeclarationList",
  "ClassDeclaration", "VariableDeclarationStatementList",
  "VariableDeclaration", "Type", "MethodDeclarationList",
  "MethodDeclaration", "ArgumentDeclarationList",
  "NonEmptyArgumentDeclarationList", "StatementList",
  "VariableDeclarationStatement", "Statement", "ArgumentsList",
  "NonEmptyArgumentsList", "Expression", YY_NULLPTR
  };


  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   121,   121,   125,   137,   139,   143,   148,   155,   157,
     161,   165,   167,   169,   171,   175,   177,   181,   187,   196,
     198,   202,   204,   208,   210,   212,   216,   220,   224,   229,
     231,   233,   235,   240,   242,   246,   248,   251,   252,   253,
     254,   255,   256,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268
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
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 5 "parser.bison" // lalr1.cc:1167
} // Grammar
#line 1392 "Parser.cpp" // lalr1.cc:1167
#line 272 "parser.bison" // lalr1.cc:1168


void
Grammar::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
