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
        value.move< ArgumentDeclarationList* > (that.value);
        break;

      case 54: // ArgumentsList
        value.move< ArgumentsList* > (that.value);
        break;

      case 44: // ClassDeclaration
        value.move< ClassDeclaration* > (that.value);
        break;

      case 43: // ClassDeclarationList
        value.move< ClassDeclarationList* > (that.value);
        break;

      case 55: // Expression
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

      case 53: // Statement
        value.move< Statement* > (that.value);
        break;

      case 51: // StatementList
        value.move< StatementList* > (that.value);
        break;

      case 47: // Type
        value.move< Type* > (that.value);
        break;

      case 46: // VariableDeclaration
        value.move< VariableDeclaration* > (that.value);
        break;

      case 52: // VariableDeclarationStatement
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
        value.copy< ArgumentDeclarationList* > (that.value);
        break;

      case 54: // ArgumentsList
        value.copy< ArgumentsList* > (that.value);
        break;

      case 44: // ClassDeclaration
        value.copy< ClassDeclaration* > (that.value);
        break;

      case 43: // ClassDeclarationList
        value.copy< ClassDeclarationList* > (that.value);
        break;

      case 55: // Expression
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

      case 53: // Statement
        value.copy< Statement* > (that.value);
        break;

      case 51: // StatementList
        value.copy< StatementList* > (that.value);
        break;

      case 47: // Type
        value.copy< Type* > (that.value);
        break;

      case 46: // VariableDeclaration
        value.copy< VariableDeclaration* > (that.value);
        break;

      case 52: // VariableDeclarationStatement
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
        yylhs.value.build< ArgumentDeclarationList* > ();
        break;

      case 54: // ArgumentsList
        yylhs.value.build< ArgumentsList* > ();
        break;

      case 44: // ClassDeclaration
        yylhs.value.build< ClassDeclaration* > ();
        break;

      case 43: // ClassDeclarationList
        yylhs.value.build< ClassDeclarationList* > ();
        break;

      case 55: // Expression
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

      case 53: // Statement
        yylhs.value.build< Statement* > ();
        break;

      case 51: // StatementList
        yylhs.value.build< StatementList* > ();
        break;

      case 47: // Type
        yylhs.value.build< Type* > ();
        break;

      case 46: // VariableDeclaration
        yylhs.value.build< VariableDeclaration* > ();
        break;

      case 52: // VariableDeclarationStatement
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
#line 119 "parser.bison" // lalr1.cc:859
    { program = new Program(yystack_[1].value.as< MainClass* > (), yystack_[0].value.as< ClassDeclarationList* > ()); }
#line 690 "Parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 131 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< MainClass* > () = new MainClass(yystack_[5].value.as< Identifier > (), yystack_[2].value.as< Statement* > ()); }
#line 696 "Parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 135 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ClassDeclarationList* > () = nullptr; }
#line 702 "Parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 137 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ClassDeclarationList* > () = new ClassDeclarationList(yystack_[0].value.as< ClassDeclaration* > (), yystack_[1].value.as< ClassDeclarationList* > ()); }
#line 708 "Parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 144 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ClassDeclaration* > () = new ClassDeclaration(yystack_[4].value.as< Identifier > (), yystack_[2].value.as< VariableDeclarationStatementList* > (), yystack_[1].value.as< MethodDeclarationList* > ()); }
#line 714 "Parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 149 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ClassDeclaration* > () = new ClassDeclaration(yystack_[6].value.as< Identifier > (), yystack_[4].value.as< Identifier > (), yystack_[2].value.as< VariableDeclarationStatementList* > (), yystack_[1].value.as< MethodDeclarationList* > ()); }
#line 720 "Parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 153 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< VariableDeclarationStatementList* > () = nullptr; }
#line 726 "Parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 155 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< VariableDeclarationStatementList* > () = new VariableDeclarationStatementList(yystack_[1].value.as< VariableDeclarationStatement* > (), yystack_[0].value.as< VariableDeclarationStatementList* > ()); }
#line 732 "Parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 159 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< VariableDeclaration* > () = new VariableDeclaration(yystack_[1].value.as< Type* > (), yystack_[0].value.as< Identifier > ()); }
#line 738 "Parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 163 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Type* > () = new Type(TT_Array); }
#line 744 "Parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 165 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Type* > () = new Type(TT_Bool); }
#line 750 "Parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 167 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Type* > () = new Type(TT_Int); }
#line 756 "Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 169 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Type* > () = new Type(TT_Object, yystack_[0].value.as< Identifier > ()); }
#line 762 "Parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 173 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< MethodDeclarationList* > () = nullptr; }
#line 768 "Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 175 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< MethodDeclarationList* > () = new MethodDeclarationList(yystack_[1].value.as< MethodDeclaration* > (), yystack_[0].value.as< MethodDeclarationList* > ()); }
#line 774 "Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 183 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< MethodDeclaration* > () = new MethodDeclaration(yystack_[6].value.as< Identifier > (), yystack_[7].value.as< Type* > (), yystack_[4].value.as< ArgumentDeclarationList* > (), yystack_[1].value.as< StatementList* > ()); }
#line 780 "Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 190 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< MethodDeclaration* > () = new MethodDeclaration(yystack_[9].value.as< Identifier > (), yystack_[10].value.as< Type* > (), yystack_[2].value.as< Expression* > (), yystack_[7].value.as< ArgumentDeclarationList* > (), yystack_[4].value.as< StatementList* > ()); }
#line 786 "Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 194 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentDeclarationList* > () = nullptr; }
#line 792 "Parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 196 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentDeclarationList* > () = new ArgumentDeclarationList(yystack_[0].value.as< VariableDeclaration* > ()); }
#line 798 "Parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 198 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentDeclarationList* > () = new ArgumentDeclarationList(yystack_[2].value.as< VariableDeclaration* > (), yystack_[0].value.as< ArgumentDeclarationList* > ()); }
#line 804 "Parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 202 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< StatementList* > () = nullptr; }
#line 810 "Parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 204 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< StatementList* > () = new StatementList(yystack_[1].value.as< Statement* > (), yystack_[0].value.as< StatementList* > ()); }
#line 816 "Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 206 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< StatementList* > () = new StatementList(yystack_[1].value.as< VariableDeclarationStatement* > (), yystack_[0].value.as< StatementList* > ()); }
#line 822 "Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 210 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< VariableDeclarationStatement* > () = new VariableDeclarationStatement(yystack_[1].value.as< VariableDeclaration* > ()); }
#line 828 "Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 216 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Statement* > () = new NestedStatement(yystack_[1].value.as< StatementList* > ()); }
#line 834 "Parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 221 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Statement* > () = new IfStatement(yystack_[4].value.as< Expression* > (), yystack_[2].value.as< Statement* > (), yystack_[0].value.as< Statement* > ()); }
#line 840 "Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 223 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Statement* > () = new WhileStatement(yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Statement* > ()); }
#line 846 "Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 225 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Statement* > () = new PrintStatement(yystack_[2].value.as< Expression* > ()); }
#line 852 "Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 227 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Statement* > () = new AssignStatement(yystack_[3].value.as< Identifier > (), yystack_[1].value.as< Expression* > ()); }
#line 858 "Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 229 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Statement* > () = new ArrayAssignStatement(yystack_[6].value.as< Identifier > (), yystack_[4].value.as< Expression* > (), yystack_[1].value.as< Expression* > ()); }
#line 864 "Parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 234 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentsList* > () = nullptr; }
#line 870 "Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 236 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentsList* > () = new ArgumentsList(yystack_[0].value.as< Expression* > ()); }
#line 876 "Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 238 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< ArgumentsList* > () = new ArgumentsList(yystack_[2].value.as< Expression* > (), yystack_[0].value.as< ArgumentsList* > ()); }
#line 882 "Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 242 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BinopExpression( yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Expression* > (), BOT_Plus ); }
#line 888 "Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 243 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BinopExpression( yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Expression* > (), BOT_Minus ); }
#line 894 "Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 244 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BinopExpression( yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Expression* > (), BOT_Multiply ); }
#line 900 "Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 245 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BinopExpression( yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Expression* > (), BOT_And ); }
#line 906 "Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 246 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BinopExpression( yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Expression* > (), BOT_Equal ); }
#line 912 "Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 247 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BinopExpression( yystack_[2].value.as< Expression* > (), yystack_[0].value.as< Expression* > (), BOT_Less ); }
#line 918 "Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 249 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new ArrayItemExpression( yystack_[3].value.as< Expression* > (), yystack_[1].value.as< Expression* > () ); }
#line 924 "Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 250 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new ArrayLengthExpression( yystack_[2].value.as< Expression* > () ); }
#line 930 "Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 251 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new CallExpression( yystack_[5].value.as< Expression* > (), yystack_[3].value.as< Identifier > (), yystack_[1].value.as< ArgumentsList* > () ); }
#line 936 "Parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 252 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new ConstExpression( yystack_[0].value.as< int > () ); }
#line 942 "Parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 253 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new BoolExpression( yystack_[0].value.as< bool > () ); }
#line 948 "Parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 254 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new IdExpression( yystack_[0].value.as< Identifier > () ); }
#line 954 "Parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 255 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new IdExpression( "this" ); }
#line 960 "Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 256 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new NewArrayExpression( yystack_[3].value.as< Type* > (), yystack_[1].value.as< Expression* > () ); }
#line 966 "Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 257 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new NewObjectExpression( yystack_[2].value.as< Identifier > () ); }
#line 972 "Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 258 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = new NotExpression( yystack_[0].value.as< Expression* > () ); }
#line 978 "Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 259 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< Expression* > () = yystack_[1].value.as< Expression* > (); }
#line 984 "Parser.cpp" // lalr1.cc:859
    break;


#line 988 "Parser.cpp" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -66;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      -2,   -21,    52,   -66,    61,   -66,    60,   112,    27,   -66,
      56,    14,   110,     9,    98,   119,   -66,   143,   -66,   134,
     138,   111,     9,   147,   150,   152,     9,   154,   134,   -66,
     -66,   -66,     9,   130,   -66,   124,   -66,   -66,   134,   155,
     159,   158,   161,     9,   -66,   129,   175,   179,   186,     9,
     187,   195,   -66,     1,    32,     1,   188,   199,   200,    11,
      41,     1,     1,    11,   201,   202,     6,     6,     6,     6,
       6,   -66,     6,   -66,   -66,   203,   -66,     6,    40,   -66,
       6,   -66,   -66,   -66,    51,    59,    67,    99,    84,   109,
     -66,   141,   207,   210,   -66,     6,    32,    39,     6,     6,
       6,     6,     6,     6,    32,   192,   170,   -66,   206,   -66,
     209,     6,   149,   196,   -66,   212,    91,    74,   102,   184,
     184,   -66,   -66,   -66,     6,   -66,   -66,   157,   -66,    32,
       6,   166,   -66,   -66,   213,   198,   -66,   -66,     6,   -66
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     4,     0,     1,     2,     0,     0,     5,
       0,     0,     0,     8,     0,     0,    12,    13,    14,    15,
       0,     0,     8,     0,     0,     0,     0,     0,    15,    25,
      10,     9,     8,     0,    11,     0,     6,    16,    15,     0,
       0,     0,     0,    19,     7,     0,    20,     0,     0,    19,
       0,     0,    21,    22,     0,    22,     0,     0,     0,    14,
       0,    22,    22,     0,     0,     0,     0,     0,     0,     0,
       0,    17,     0,    24,    23,     0,    26,     0,     0,    47,
       0,    45,    44,    46,     0,     0,     0,     0,     0,     0,
       3,     0,    14,     0,    50,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    30,     0,    51,
       0,     0,     0,     0,    42,     0,    39,    40,    38,    35,
      36,    37,    28,    29,     0,    18,    49,     0,    41,     0,
      32,     0,    48,    27,     0,    33,    31,    43,    32,    34
  };

  const short int
  Parser::yypgoto_[] =
  {
     -66,   -66,   -66,   -66,   -66,   -13,   -17,   -20,   -15,   -66,
     171,    49,    54,   -54,    83,   -65
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,     6,     9,    19,    20,    21,    27,    28,
      47,    60,    61,    62,   134,   135
  };

  const unsigned char
  Parser::yytable_[] =
  {
      64,    84,    85,    86,    87,    88,    35,    89,    55,    31,
       1,    77,    91,    37,    69,    94,    16,    17,     4,    38,
      56,    13,    57,    41,    16,    17,    46,    14,    78,    58,
     112,    79,    46,   116,   117,   118,   119,   120,   121,    55,
      59,    80,   113,    81,    82,    83,   127,    70,    18,    71,
     122,    56,     5,    57,    95,    16,    17,    96,    93,   131,
      58,    97,    95,   114,    72,   104,    11,    22,     7,    97,
      95,    63,     8,   105,    12,   133,    22,    97,   115,    92,
      98,    99,   100,   101,   102,   103,    22,    95,    98,    99,
     100,   101,   102,   103,    97,   107,    98,    99,   100,   101,
     102,   103,    95,   106,    65,   100,   101,   102,   103,    97,
      73,    74,    95,    98,    99,   100,   101,   102,   103,    97,
     108,    99,   100,   101,   102,   103,    10,    15,    98,    99,
     100,   101,   102,   103,   101,   102,   103,    23,    98,    99,
     100,   101,   102,   103,    95,    24,    25,   109,    26,    29,
      30,    97,    95,   128,    32,    33,    34,    39,    42,    97,
      95,   132,    36,    40,    43,    45,    44,    97,    48,    95,
      98,    99,   100,   101,   102,   103,    97,   136,    98,    99,
     100,   101,   102,   103,    49,    50,    98,    99,   100,   101,
     102,   103,    51,    66,    53,    98,    99,   100,   101,   102,
     103,    95,    54,   123,    67,    68,   124,   138,    97,    75,
      76,    90,   110,   111,   125,   126,   129,   130,   103,   137,
      52,   139,     0,     0,     0,     0,     0,    98,    99,   100,
     101,   102,   103
  };

  const short int
  Parser::yycheck_[] =
  {
      54,    66,    67,    68,    69,    70,    26,    72,     7,    22,
      12,     5,    77,    28,     3,    80,    15,    16,    39,    32,
      19,     7,    21,    38,    15,    16,    43,    13,    22,    28,
      95,    25,    49,    98,    99,   100,   101,   102,   103,     7,
      39,    35,    96,    37,    38,    39,   111,    36,    39,     8,
     104,    19,     0,    21,     3,    15,    16,     6,    78,   124,
      28,    10,     3,    24,    23,     6,    39,    13,     7,    10,
       3,    39,    12,     6,    18,   129,    22,    10,    39,    39,
      29,    30,    31,    32,    33,    34,    32,     3,    29,    30,
      31,    32,    33,    34,    10,    11,    29,    30,    31,    32,
      33,    34,     3,     4,    55,    31,    32,    33,    34,    10,
      61,    62,     3,    29,    30,    31,    32,    33,    34,    10,
      11,    30,    31,    32,    33,    34,    14,    17,    29,    30,
      31,    32,    33,    34,    32,    33,    34,    39,    29,    30,
      31,    32,    33,    34,     3,    26,     3,     6,    14,    11,
      39,    10,     3,     4,     7,     5,     4,    27,     3,    10,
       3,     4,     8,    39,     5,     4,     8,    10,    39,     3,
      29,    30,    31,    32,    33,    34,    10,    11,    29,    30,
      31,    32,    33,    34,     9,     6,    29,    30,    31,    32,
      33,    34,     6,     5,     7,    29,    30,    31,    32,    33,
      34,     3,     7,    11,     5,     5,    36,     9,    10,     8,
       8,     8,     5,     3,     8,     6,    20,     5,    34,     6,
      49,   138,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
      32,    33,    34
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    12,    41,    42,    39,     0,    43,     7,    12,    44,
      14,    39,    18,     7,    13,    17,    15,    16,    39,    45,
      46,    47,    52,    39,    26,     3,    14,    48,    49,    11,
      39,    45,     7,     5,     4,    47,     8,    48,    45,    27,
      39,    48,     3,     5,     8,     4,    46,    50,    39,     9,
       6,     6,    50,     7,     7,     7,    19,    21,    28,    39,
      51,    52,    53,    39,    53,    51,     5,     5,     5,     3,
      36,     8,    23,    51,    51,     8,     8,     5,    22,    25,
      35,    37,    38,    39,    55,    55,    55,    55,    55,    55,
       8,    55,    39,    47,    55,     3,     6,    10,    29,    30,
      31,    32,    33,    34,     6,     6,     4,    11,    11,     6,
       5,     3,    55,    53,    24,    39,    55,    55,    55,    55,
      55,    55,    53,    11,    36,     8,     6,    55,     4,    20,
       5,    55,     4,    53,    54,    55,    11,     6,     9,    54
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    40,    41,    42,    43,    43,    44,    44,    45,    45,
      46,    47,    47,    47,    47,    48,    48,    49,    49,    50,
      50,    50,    51,    51,    51,    52,    53,    53,    53,    53,
      53,    53,    54,    54,    54,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,    17,     0,     2,     6,     8,     0,     2,
       2,     3,     1,     1,     1,     0,     2,     9,    12,     0,
       1,     3,     0,     2,     2,     2,     3,     7,     5,     5,
       4,     7,     0,     1,     3,     3,     3,     3,     3,     3,
       3,     4,     3,     6,     1,     1,     1,     1,     5,     4,
       2,     3
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
  "MethodDeclaration", "ArgumentDeclarationList", "StatementList",
  "VariableDeclarationStatement", "Statement", "ArgumentsList",
  "Expression", YY_NULLPTR
  };


  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   119,   119,   123,   135,   137,   141,   146,   153,   155,
     159,   163,   165,   167,   169,   173,   175,   179,   185,   194,
     196,   198,   202,   204,   206,   210,   214,   218,   223,   225,
     227,   229,   234,   236,   238,   242,   243,   244,   245,   246,
     247,   249,   250,   251,   252,   253,   254,   255,   256,   257,
     258,   259
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
#line 1373 "Parser.cpp" // lalr1.cc:1167
#line 263 "parser.bison" // lalr1.cc:1168


void
Grammar::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
