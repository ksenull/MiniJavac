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
#line 36 "parser.bison" // lalr1.cc:413

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
  Parser::Parser (Scanner& scanner_yyarg, Program& program_yyarg)
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
      case 37: // BOOL_VALUE
        value.move< bool > (that.value);
        break;

      case 38: // INTEGER
        value.move< int > (that.value);
        break;

      case 51: // ArgumentDeclarationList
      case 52: // NonEmptyArgumentDeclarationList
        value.move< std::shared_ptr<ArgumentDeclarationList> > (that.value);
        break;

      case 56: // ArgumentsList
      case 57: // NonEmptyArgumentsList
        value.move< std::shared_ptr<ArgumentsList> > (that.value);
        break;

      case 53: // StatementList
        value.move< std::shared_ptr<CStatementList> > (that.value);
        break;

      case 44: // ClassDeclaration
        value.move< std::shared_ptr<ClassDeclaration> > (that.value);
        break;

      case 43: // ClassDeclarationList
        value.move< std::shared_ptr<ClassDeclarationList> > (that.value);
        break;

      case 58: // Expression
        value.move< std::shared_ptr<IExpression> > (that.value);
        break;

      case 55: // Statement
        value.move< std::shared_ptr<IStatement> > (that.value);
        break;

      case 42: // MainClass
        value.move< std::shared_ptr<MainClass> > (that.value);
        break;

      case 50: // MethodDeclaration
        value.move< std::shared_ptr<MethodDeclaration> > (that.value);
        break;

      case 49: // MethodDeclarationList
        value.move< std::shared_ptr<MethodDeclarationList> > (that.value);
        break;

      case 47: // Type
      case 48: // Void
        value.move< std::shared_ptr<Type> > (that.value);
        break;

      case 46: // VariableDeclaration
        value.move< std::shared_ptr<VariableDeclaration> > (that.value);
        break;

      case 54: // VariableDeclarationStatement
        value.move< std::shared_ptr<VariableDeclarationStatement> > (that.value);
        break;

      case 45: // VariableDeclarationStatementList
        value.move< std::shared_ptr<VariableDeclarationStatementList> > (that.value);
        break;

      case 39: // ID
        value.move< std::string > (that.value);
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
      case 37: // BOOL_VALUE
        value.copy< bool > (that.value);
        break;

      case 38: // INTEGER
        value.copy< int > (that.value);
        break;

      case 51: // ArgumentDeclarationList
      case 52: // NonEmptyArgumentDeclarationList
        value.copy< std::shared_ptr<ArgumentDeclarationList> > (that.value);
        break;

      case 56: // ArgumentsList
      case 57: // NonEmptyArgumentsList
        value.copy< std::shared_ptr<ArgumentsList> > (that.value);
        break;

      case 53: // StatementList
        value.copy< std::shared_ptr<CStatementList> > (that.value);
        break;

      case 44: // ClassDeclaration
        value.copy< std::shared_ptr<ClassDeclaration> > (that.value);
        break;

      case 43: // ClassDeclarationList
        value.copy< std::shared_ptr<ClassDeclarationList> > (that.value);
        break;

      case 58: // Expression
        value.copy< std::shared_ptr<IExpression> > (that.value);
        break;

      case 55: // Statement
        value.copy< std::shared_ptr<IStatement> > (that.value);
        break;

      case 42: // MainClass
        value.copy< std::shared_ptr<MainClass> > (that.value);
        break;

      case 50: // MethodDeclaration
        value.copy< std::shared_ptr<MethodDeclaration> > (that.value);
        break;

      case 49: // MethodDeclarationList
        value.copy< std::shared_ptr<MethodDeclarationList> > (that.value);
        break;

      case 47: // Type
      case 48: // Void
        value.copy< std::shared_ptr<Type> > (that.value);
        break;

      case 46: // VariableDeclaration
        value.copy< std::shared_ptr<VariableDeclaration> > (that.value);
        break;

      case 54: // VariableDeclarationStatement
        value.copy< std::shared_ptr<VariableDeclarationStatement> > (that.value);
        break;

      case 45: // VariableDeclarationStatementList
        value.copy< std::shared_ptr<VariableDeclarationStatementList> > (that.value);
        break;

      case 39: // ID
        value.copy< std::string > (that.value);
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
      case 37: // BOOL_VALUE
        yylhs.value.build< bool > ();
        break;

      case 38: // INTEGER
        yylhs.value.build< int > ();
        break;

      case 51: // ArgumentDeclarationList
      case 52: // NonEmptyArgumentDeclarationList
        yylhs.value.build< std::shared_ptr<ArgumentDeclarationList> > ();
        break;

      case 56: // ArgumentsList
      case 57: // NonEmptyArgumentsList
        yylhs.value.build< std::shared_ptr<ArgumentsList> > ();
        break;

      case 53: // StatementList
        yylhs.value.build< std::shared_ptr<CStatementList> > ();
        break;

      case 44: // ClassDeclaration
        yylhs.value.build< std::shared_ptr<ClassDeclaration> > ();
        break;

      case 43: // ClassDeclarationList
        yylhs.value.build< std::shared_ptr<ClassDeclarationList> > ();
        break;

      case 58: // Expression
        yylhs.value.build< std::shared_ptr<IExpression> > ();
        break;

      case 55: // Statement
        yylhs.value.build< std::shared_ptr<IStatement> > ();
        break;

      case 42: // MainClass
        yylhs.value.build< std::shared_ptr<MainClass> > ();
        break;

      case 50: // MethodDeclaration
        yylhs.value.build< std::shared_ptr<MethodDeclaration> > ();
        break;

      case 49: // MethodDeclarationList
        yylhs.value.build< std::shared_ptr<MethodDeclarationList> > ();
        break;

      case 47: // Type
      case 48: // Void
        yylhs.value.build< std::shared_ptr<Type> > ();
        break;

      case 46: // VariableDeclaration
        yylhs.value.build< std::shared_ptr<VariableDeclaration> > ();
        break;

      case 54: // VariableDeclarationStatement
        yylhs.value.build< std::shared_ptr<VariableDeclarationStatement> > ();
        break;

      case 45: // VariableDeclarationStatementList
        yylhs.value.build< std::shared_ptr<VariableDeclarationStatementList> > ();
        break;

      case 39: // ID
        yylhs.value.build< std::string > ();
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
#line 125 "parser.bison" // lalr1.cc:859
    {
        program = Program(yystack_[1].value.as< std::shared_ptr<MainClass> > (), yystack_[0].value.as< std::shared_ptr<ClassDeclarationList> > (), LOCATION(yylhs.location));
    }
#line 701 "Parser.cpp" // lalr1.cc:859
    break;

  case 3:
#line 138 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<MainClass> > () = std::make_shared<MainClass>(
            MainClass(
                std::make_shared<Identifier>(Identifier(yystack_[15].value.as< std::string > ())),
                std::make_shared<Identifier>(Identifier(yystack_[5].value.as< std::string > ())),
                yystack_[2].value.as< std::shared_ptr<IStatement> > (),
                LOCATION(yylhs.location)
            )
         );
    }
#line 716 "Parser.cpp" // lalr1.cc:859
    break;

  case 4:
#line 150 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<ClassDeclarationList> > () = std::make_shared<ClassDeclarationList>(
            ClassDeclarationList(LOCATION(yylhs.location))
        );
    }
#line 726 "Parser.cpp" // lalr1.cc:859
    break;

  case 5:
#line 156 "parser.bison" // lalr1.cc:859
    {
        yystack_[1].value.as< std::shared_ptr<ClassDeclarationList> > ()->nodes.emplace_back(yystack_[0].value.as< std::shared_ptr<ClassDeclaration> > ());
        yylhs.value.as< std::shared_ptr<ClassDeclarationList> > () = yystack_[1].value.as< std::shared_ptr<ClassDeclarationList> > ();
    }
#line 735 "Parser.cpp" // lalr1.cc:859
    break;

  case 6:
#line 165 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<ClassDeclaration> > () = std::make_shared<ClassDeclaration>(
            ClassDeclaration(
                std::make_shared<Identifier>(Identifier(yystack_[4].value.as< std::string > ())), yystack_[2].value.as< std::shared_ptr<VariableDeclarationStatementList> > (), yystack_[1].value.as< std::shared_ptr<MethodDeclarationList> > (), LOCATION(yylhs.location)
            )
        );
    }
#line 747 "Parser.cpp" // lalr1.cc:859
    break;

  case 7:
#line 176 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<ClassDeclaration> > () = std::make_shared<ClassDeclaration>(
            ClassDeclaration(
                std::make_shared<Identifier>(Identifier(yystack_[6].value.as< std::string > ())),
                std::make_shared<Identifier>(Identifier(yystack_[4].value.as< std::string > ())),
                yystack_[2].value.as< std::shared_ptr<VariableDeclarationStatementList> > (), yystack_[1].value.as< std::shared_ptr<MethodDeclarationList> > (),
                LOCATION(yylhs.location)
            )
        );
    }
#line 762 "Parser.cpp" // lalr1.cc:859
    break;

  case 8:
#line 188 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<VariableDeclarationStatementList> > () = std::make_shared<VariableDeclarationStatementList>(
            VariableDeclarationStatementList(LOCATION(yylhs.location))
        );
    }
#line 772 "Parser.cpp" // lalr1.cc:859
    break;

  case 9:
#line 194 "parser.bison" // lalr1.cc:859
    {
             yystack_[1].value.as< std::shared_ptr<VariableDeclarationStatementList> > ()->nodes.emplace_back(yystack_[0].value.as< std::shared_ptr<VariableDeclarationStatement> > ());
             yylhs.value.as< std::shared_ptr<VariableDeclarationStatementList> > () = yystack_[1].value.as< std::shared_ptr<VariableDeclarationStatementList> > ();
    }
#line 781 "Parser.cpp" // lalr1.cc:859
    break;

  case 10:
#line 200 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<VariableDeclaration> > () = std::make_shared<VariableDeclaration>(
            VariableDeclaration(
                yystack_[1].value.as< std::shared_ptr<Type> > (),
                std::make_shared<Identifier>(Identifier(yystack_[0].value.as< std::string > ())),
                LOCATION(yylhs.location)
            )
        );
    }
#line 795 "Parser.cpp" // lalr1.cc:859
    break;

  case 11:
#line 211 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<Type> > () = std::make_shared<Type>(
            Type(TT_Array, LOCATION(yylhs.location))
        );
    }
#line 805 "Parser.cpp" // lalr1.cc:859
    break;

  case 12:
#line 217 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<Type> > () = std::make_shared<Type>(
            Type(TT_Bool, LOCATION(yylhs.location))
        );
    }
#line 815 "Parser.cpp" // lalr1.cc:859
    break;

  case 13:
#line 223 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<Type> > () = std::make_shared<Type>(
            Type(TT_Int, LOCATION(yylhs.location))
        );
    }
#line 825 "Parser.cpp" // lalr1.cc:859
    break;

  case 14:
#line 229 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<Type> > () = std::make_shared<Type>(
            Type(
                TT_Object,
                std::make_shared<Identifier>(Identifier(yystack_[0].value.as< std::string > ())),
                LOCATION(yylhs.location)
            )
        );
    }
#line 839 "Parser.cpp" // lalr1.cc:859
    break;

  case 15:
#line 240 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<Type> > () = std::make_shared<Type>(
            Type(TT_Void, LOCATION(yylhs.location))
        );
    }
#line 849 "Parser.cpp" // lalr1.cc:859
    break;

  case 16:
#line 247 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<MethodDeclarationList> > () = std::make_shared<MethodDeclarationList>(
            MethodDeclarationList(LOCATION(yylhs.location))
        );
    }
#line 859 "Parser.cpp" // lalr1.cc:859
    break;

  case 17:
#line 253 "parser.bison" // lalr1.cc:859
    {
            yystack_[1].value.as< std::shared_ptr<MethodDeclarationList> > ()->nodes.emplace_back(yystack_[0].value.as< std::shared_ptr<MethodDeclaration> > ());
            yylhs.value.as< std::shared_ptr<MethodDeclarationList> > () = yystack_[1].value.as< std::shared_ptr<MethodDeclarationList> > ();
    }
#line 868 "Parser.cpp" // lalr1.cc:859
    break;

  case 18:
#line 263 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<MethodDeclaration> > () = std::make_shared<MethodDeclaration>(
            MethodDeclaration(
                std::make_shared<Identifier>(Identifier(yystack_[6].value.as< std::string > ())),
                yystack_[7].value.as< std::shared_ptr<Type> > (), yystack_[4].value.as< std::shared_ptr<ArgumentDeclarationList> > (), yystack_[1].value.as< std::shared_ptr<CStatementList> > (),
                LOCATION(yylhs.location)
            )
         );
    }
#line 882 "Parser.cpp" // lalr1.cc:859
    break;

  case 19:
#line 277 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<MethodDeclaration> > () = std::make_shared<MethodDeclaration>(
            MethodDeclaration(
                std::make_shared<Identifier>(Identifier(yystack_[6].value.as< std::string > ())),
                yystack_[7].value.as< std::shared_ptr<Type> > (), yystack_[4].value.as< std::shared_ptr<ArgumentDeclarationList> > (), yystack_[1].value.as< std::shared_ptr<CStatementList> > (),
                LOCATION(yylhs.location)
            )
        );
    }
#line 896 "Parser.cpp" // lalr1.cc:859
    break;

  case 20:
#line 292 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<MethodDeclaration> > () = std::make_shared<MethodDeclaration>(
            MethodDeclaration(
                std::make_shared<Identifier>(Identifier(yystack_[9].value.as< std::string > ())),
                yystack_[10].value.as< std::shared_ptr<Type> > (), yystack_[2].value.as< std::shared_ptr<IExpression> > (), yystack_[7].value.as< std::shared_ptr<ArgumentDeclarationList> > (), yystack_[4].value.as< std::shared_ptr<CStatementList> > (),
                LOCATION(yylhs.location)
            )
        );
    }
#line 910 "Parser.cpp" // lalr1.cc:859
    break;

  case 21:
#line 303 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<ArgumentDeclarationList> > () = std::make_shared<ArgumentDeclarationList>(
            ArgumentDeclarationList(LOCATION(yylhs.location))
        );
    }
#line 920 "Parser.cpp" // lalr1.cc:859
    break;

  case 22:
#line 309 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<ArgumentDeclarationList> > () = yystack_[0].value.as< std::shared_ptr<ArgumentDeclarationList> > ();
    }
#line 928 "Parser.cpp" // lalr1.cc:859
    break;

  case 23:
#line 314 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<ArgumentDeclarationList> > () = std::make_shared<ArgumentDeclarationList>(
            ArgumentDeclarationList(yystack_[0].value.as< std::shared_ptr<VariableDeclaration> > (), LOCATION(yylhs.location))
        );
    }
#line 938 "Parser.cpp" // lalr1.cc:859
    break;

  case 24:
#line 320 "parser.bison" // lalr1.cc:859
    {
        yystack_[0].value.as< std::shared_ptr<ArgumentDeclarationList> > ()->nodes.emplace_back(yystack_[2].value.as< std::shared_ptr<VariableDeclaration> > ());
        yylhs.value.as< std::shared_ptr<ArgumentDeclarationList> > () = yystack_[0].value.as< std::shared_ptr<ArgumentDeclarationList> > ();
    }
#line 947 "Parser.cpp" // lalr1.cc:859
    break;

  case 25:
#line 326 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<CStatementList> > () =  std::make_shared<CStatementList>(
            CStatementList(LOCATION(yylhs.location))
        );
    }
#line 957 "Parser.cpp" // lalr1.cc:859
    break;

  case 26:
#line 332 "parser.bison" // lalr1.cc:859
    {
        yystack_[1].value.as< std::shared_ptr<CStatementList> > ()->nodes.emplace_back(yystack_[0].value.as< std::shared_ptr<IStatement> > ());
        yylhs.value.as< std::shared_ptr<CStatementList> > () = yystack_[1].value.as< std::shared_ptr<CStatementList> > ();
    }
#line 966 "Parser.cpp" // lalr1.cc:859
    break;

  case 27:
#line 337 "parser.bison" // lalr1.cc:859
    {
        yystack_[1].value.as< std::shared_ptr<CStatementList> > ()->nodes.emplace_back(yystack_[0].value.as< std::shared_ptr<VariableDeclarationStatement> > ());
        yylhs.value.as< std::shared_ptr<CStatementList> > () = yystack_[1].value.as< std::shared_ptr<CStatementList> > ();
    }
#line 975 "Parser.cpp" // lalr1.cc:859
    break;

  case 28:
#line 343 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<VariableDeclarationStatement> > () = std::make_shared<VariableDeclarationStatement>(
            VariableDeclarationStatement(yystack_[1].value.as< std::shared_ptr<VariableDeclaration> > (), LOCATION(yylhs.location))
        );
    }
#line 985 "Parser.cpp" // lalr1.cc:859
    break;

  case 29:
#line 352 "parser.bison" // lalr1.cc:859
    {
        yylhs.value.as< std::shared_ptr<IStatement> > () = std::make_shared<NestedStatement>(
            NestedStatement(yystack_[1].value.as< std::shared_ptr<CStatementList> > (), LOCATION(yylhs.location))
        );
    }
#line 995 "Parser.cpp" // lalr1.cc:859
    break;

  case 30:
#line 361 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IStatement> > () = std::make_shared<IfStatement>(IfStatement(yystack_[4].value.as< std::shared_ptr<IExpression> > (), yystack_[2].value.as< std::shared_ptr<IStatement> > (), yystack_[0].value.as< std::shared_ptr<IStatement> > (), LOCATION(yylhs.location))); }
#line 1001 "Parser.cpp" // lalr1.cc:859
    break;

  case 31:
#line 363 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IStatement> > () = std::make_shared<WhileStatement>(WhileStatement(yystack_[2].value.as< std::shared_ptr<IExpression> > (), yystack_[0].value.as< std::shared_ptr<IStatement> > (), LOCATION(yylhs.location))); }
#line 1007 "Parser.cpp" // lalr1.cc:859
    break;

  case 32:
#line 365 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IStatement> > () = std::make_shared<PrintStatement>(PrintStatement(yystack_[2].value.as< std::shared_ptr<IExpression> > (), LOCATION(yylhs.location))); }
#line 1013 "Parser.cpp" // lalr1.cc:859
    break;

  case 33:
#line 367 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IStatement> > () = std::make_shared<AssignStatement>(AssignStatement(
        std::make_shared<Identifier>(Identifier(yystack_[3].value.as< std::string > ())), yystack_[1].value.as< std::shared_ptr<IExpression> > (), LOCATION(yylhs.location))
    ); }
#line 1021 "Parser.cpp" // lalr1.cc:859
    break;

  case 34:
#line 371 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IStatement> > () = std::make_shared<ArrayAssignStatement>(
    ArrayAssignStatement(std::make_shared<Identifier>(Identifier(yystack_[6].value.as< std::string > ())), yystack_[4].value.as< std::shared_ptr<IExpression> > (), yystack_[1].value.as< std::shared_ptr<IExpression> > (), LOCATION(yylhs.location))); }
#line 1028 "Parser.cpp" // lalr1.cc:859
    break;

  case 35:
#line 377 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArgumentsList> > () = std::make_shared<ArgumentsList>(ArgumentsList(LOCATION(yylhs.location))); }
#line 1034 "Parser.cpp" // lalr1.cc:859
    break;

  case 36:
#line 379 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArgumentsList> > () = yystack_[0].value.as< std::shared_ptr<ArgumentsList> > (); }
#line 1040 "Parser.cpp" // lalr1.cc:859
    break;

  case 37:
#line 383 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<ArgumentsList> > () = std::make_shared<ArgumentsList>(ArgumentsList(yystack_[0].value.as< std::shared_ptr<IExpression> > (), LOCATION(yylhs.location))); }
#line 1046 "Parser.cpp" // lalr1.cc:859
    break;

  case 38:
#line 385 "parser.bison" // lalr1.cc:859
    {
        yystack_[2].value.as< std::shared_ptr<ArgumentsList> > ()->nodes.emplace_back(yystack_[0].value.as< std::shared_ptr<IExpression> > ());
        yylhs.value.as< std::shared_ptr<ArgumentsList> > () = yystack_[2].value.as< std::shared_ptr<ArgumentsList> > ();
    }
#line 1055 "Parser.cpp" // lalr1.cc:859
    break;

  case 39:
#line 392 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<NotExpression>( yystack_[0].value.as< std::shared_ptr<IExpression> > (), LOCATION(yylhs.location)); }
#line 1061 "Parser.cpp" // lalr1.cc:859
    break;

  case 40:
#line 393 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<BinopExpression>(BinopExpression(yystack_[2].value.as< std::shared_ptr<IExpression> > (), yystack_[0].value.as< std::shared_ptr<IExpression> > (), BOT_Plus, LOCATION(yylhs.location))); }
#line 1067 "Parser.cpp" // lalr1.cc:859
    break;

  case 41:
#line 394 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<BinopExpression>(BinopExpression(yystack_[2].value.as< std::shared_ptr<IExpression> > (), yystack_[0].value.as< std::shared_ptr<IExpression> > (), BOT_Minus, LOCATION(yylhs.location))); }
#line 1073 "Parser.cpp" // lalr1.cc:859
    break;

  case 42:
#line 395 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<BinopExpression>(BinopExpression(yystack_[2].value.as< std::shared_ptr<IExpression> > (), yystack_[0].value.as< std::shared_ptr<IExpression> > (), BOT_Multiply, LOCATION(yylhs.location))); }
#line 1079 "Parser.cpp" // lalr1.cc:859
    break;

  case 43:
#line 396 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<BinopExpression>(BinopExpression(yystack_[2].value.as< std::shared_ptr<IExpression> > (), yystack_[0].value.as< std::shared_ptr<IExpression> > (), BOT_And, LOCATION(yylhs.location))); }
#line 1085 "Parser.cpp" // lalr1.cc:859
    break;

  case 44:
#line 397 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<BinopExpression>(BinopExpression(yystack_[2].value.as< std::shared_ptr<IExpression> > (), yystack_[0].value.as< std::shared_ptr<IExpression> > (), BOT_Equal, LOCATION(yylhs.location))); }
#line 1091 "Parser.cpp" // lalr1.cc:859
    break;

  case 45:
#line 398 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<BinopExpression>(BinopExpression(yystack_[2].value.as< std::shared_ptr<IExpression> > (), yystack_[0].value.as< std::shared_ptr<IExpression> > (), BOT_Less, LOCATION(yylhs.location))); }
#line 1097 "Parser.cpp" // lalr1.cc:859
    break;

  case 46:
#line 400 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<ArrayItemExpression>(ArrayItemExpression( yystack_[3].value.as< std::shared_ptr<IExpression> > (), yystack_[1].value.as< std::shared_ptr<IExpression> > (), LOCATION(yylhs.location))); }
#line 1103 "Parser.cpp" // lalr1.cc:859
    break;

  case 47:
#line 401 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<ArrayLengthExpression>(ArrayLengthExpression( yystack_[2].value.as< std::shared_ptr<IExpression> > (), LOCATION(yylhs.location))); }
#line 1109 "Parser.cpp" // lalr1.cc:859
    break;

  case 48:
#line 402 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<CallExpression>(CallExpression(
	    yystack_[5].value.as< std::shared_ptr<IExpression> > (), std::make_shared<Identifier>(Identifier(yystack_[3].value.as< std::string > ())), yystack_[1].value.as< std::shared_ptr<ArgumentsList> > (), LOCATION(yylhs.location))); }
#line 1116 "Parser.cpp" // lalr1.cc:859
    break;

  case 49:
#line 404 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<ConstExpression>(ConstExpression( yystack_[0].value.as< int > (), LOCATION(yylhs.location))); }
#line 1122 "Parser.cpp" // lalr1.cc:859
    break;

  case 50:
#line 405 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<BoolExpression>(BoolExpression( yystack_[0].value.as< bool > (), LOCATION(yylhs.location))); }
#line 1128 "Parser.cpp" // lalr1.cc:859
    break;

  case 51:
#line 406 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<IdExpression>(IdExpression( std::make_shared<Identifier>(Identifier(yystack_[0].value.as< std::string > ())), LOCATION(yylhs.location))); }
#line 1134 "Parser.cpp" // lalr1.cc:859
    break;

  case 52:
#line 407 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<IdExpression>(IdExpression( std::make_shared<Identifier>(Identifier("this")), LOCATION(yylhs.location))); }
#line 1140 "Parser.cpp" // lalr1.cc:859
    break;

  case 53:
#line 408 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<NewArrayExpression>(NewArrayExpression( yystack_[1].value.as< std::shared_ptr<IExpression> > (), LOCATION(yylhs.location))); }
#line 1146 "Parser.cpp" // lalr1.cc:859
    break;

  case 54:
#line 409 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = std::make_shared<NewObjectExpression>(NewObjectExpression( std::make_shared<Identifier>(Identifier(yystack_[2].value.as< std::string > ())), LOCATION(yylhs.location))); }
#line 1152 "Parser.cpp" // lalr1.cc:859
    break;

  case 55:
#line 410 "parser.bison" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<IExpression> > () = yystack_[1].value.as< std::shared_ptr<IExpression> > (); }
#line 1158 "Parser.cpp" // lalr1.cc:859
    break;


#line 1162 "Parser.cpp" // lalr1.cc:859
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


  const signed char Parser::yypact_ninf_ = -71;

  const signed char Parser::yytable_ninf_ = -1;

  const short int
  Parser::yypact_[] =
  {
      -1,    12,    52,   -71,    57,   -71,    47,    53,    32,   -71,
      54,    49,    62,   -71,    35,    60,   -10,    81,    85,   -71,
      90,   -71,    87,    68,    94,   -71,   -71,    74,   107,   -71,
     -71,   -71,     2,   -71,   -10,   109,   -71,   -71,    89,    91,
     102,   125,   149,   150,   -71,   126,   -10,   -10,   160,   158,
     162,   -71,   163,   164,   -10,   171,   172,    66,   -71,   -71,
     -71,   -71,   165,   175,   176,    11,   181,    42,    61,    76,
       5,     5,     5,     5,     5,   182,   -71,     5,    11,   -71,
     -71,   -71,   -71,     5,    -7,   -71,     5,   -71,   -71,   -71,
      93,   103,   111,   143,   128,   -71,   153,   185,   189,   188,
     -71,     5,    66,     9,     5,     5,     5,     5,     5,     5,
      66,   183,   166,   -71,   190,   -71,     5,   194,   193,   179,
     -71,   196,   118,    -9,    86,   173,   173,   -71,   -71,   -71,
       5,   -71,   201,   -71,   -71,    66,     5,   210,   -71,   -71,
       6,   -71,   226,   -71,   -71,     5,   226
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,     0,     0,     4,     0,     1,     2,     0,     0,     5,
       0,     0,     0,     8,     0,     0,    16,     0,     0,    12,
      13,    14,     0,     0,     0,     9,     8,     0,     0,    28,
      10,     6,     0,    17,    16,     0,    11,    15,     0,     0,
       0,     0,     0,     0,     7,     0,    21,    21,     0,    23,
       0,    22,     0,     0,     0,     0,     0,     0,    24,    25,
      25,    25,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    18,     0,    14,    27,
      26,    19,    29,     0,     0,    52,     0,    50,    49,    51,
       0,     0,     0,     0,     0,     3,     0,     0,     0,     0,
      39,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    33,     0,    55,     0,     0,     0,     0,
      47,     0,    44,    45,    43,    40,    41,    42,    31,    32,
       0,    20,     0,    54,    46,     0,    35,     0,    53,    30,
       0,    36,    37,    34,    48,     0,    38
  };

  const short int
  Parser::yypgoto_[] =
  {
     -71,   -71,   -71,   -71,   -71,   180,   -26,   177,   -71,   174,
     -71,   191,   156,    -6,    -8,   -57,   -71,   -71,   -70
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     2,     3,     6,     9,    16,    22,    23,    39,    24,
      33,    50,    51,    67,    79,    80,   140,   141,    90
  };

  const unsigned char
  Parser::yytable_[] =
  {
      66,    91,    92,    93,    94,    19,    20,    96,    25,    98,
      83,     1,   144,    97,    73,   145,   100,    19,    20,    37,
      49,    49,   106,   107,   108,   109,    25,    84,    49,    21,
      85,   118,    99,   120,   122,   123,   124,   125,   126,   127,
      86,    21,    87,    88,    89,   119,   132,    74,   121,    61,
      76,     4,     5,   128,    68,    69,    13,    19,    20,     8,
     137,    62,    14,    63,     7,    77,   142,    10,    61,    81,
      64,    11,    12,    61,    17,   146,    19,    20,   139,    15,
      62,    78,    63,    61,    82,    62,    18,    63,    26,    64,
      27,    19,    20,    28,    64,    62,   101,    63,    29,   102,
      78,    35,    31,   103,    64,    65,   101,    30,    32,   110,
      44,    36,    41,   103,   101,    78,    32,   111,   107,   108,
     109,   103,   104,   105,   106,   107,   108,   109,    42,    45,
      43,   101,   104,   105,   106,   107,   108,   109,   103,   113,
     104,   105,   106,   107,   108,   109,   101,   112,   105,   106,
     107,   108,   109,   103,    46,    47,   101,   104,   105,   106,
     107,   108,   109,   103,   114,    48,    53,    54,    55,    56,
      70,    57,   104,   105,   106,   107,   108,   109,    59,    60,
      71,    72,   104,   105,   106,   107,   108,   109,   101,    75,
      95,   115,   116,   117,   129,   103,   101,   134,   131,   135,
     133,   136,   130,   103,   101,   138,    34,   109,    40,    38,
      58,   103,     0,   101,   104,   105,   106,   107,   108,   109,
     103,   143,   104,   105,   106,   107,   108,   109,     0,   101,
     104,   105,   106,   107,   108,   109,   103,     0,    52,   104,
     105,   106,   107,   108,   109,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   104,   105,   106,   107,   108,
     109
  };

  const short int
  Parser::yycheck_[] =
  {
      57,    71,    72,    73,    74,    15,    16,    77,    16,    16,
       5,    12,     6,    83,     3,     9,    86,    15,    16,    17,
      46,    47,    31,    32,    33,    34,    34,    22,    54,    39,
      25,   101,    39,    24,   104,   105,   106,   107,   108,   109,
      35,    39,    37,    38,    39,   102,   116,    36,    39,     7,
       8,    39,     0,   110,    60,    61,     7,    15,    16,    12,
     130,    19,    13,    21,     7,    23,   136,    14,     7,     8,
      28,    39,    18,     7,    39,   145,    15,    16,   135,    17,
      19,    39,    21,     7,     8,    19,    26,    21,     7,    28,
       5,    15,    16,     3,    28,    19,     3,    21,    11,     6,
      39,    27,     8,    10,    28,    39,     3,    39,    14,     6,
       8,     4,     3,    10,     3,    39,    14,     6,    32,    33,
      34,    10,    29,    30,    31,    32,    33,    34,    39,     4,
      39,     3,    29,    30,    31,    32,    33,    34,    10,    11,
      29,    30,    31,    32,    33,    34,     3,     4,    30,    31,
      32,    33,    34,    10,     5,     5,     3,    29,    30,    31,
      32,    33,    34,    10,    11,    39,     6,     9,     6,     6,
       5,     7,    29,    30,    31,    32,    33,    34,     7,     7,
       5,     5,    29,    30,    31,    32,    33,    34,     3,     8,
       8,     6,     3,     5,    11,    10,     3,     4,     8,    20,
       6,     5,    36,    10,     3,     4,    26,    34,    34,    32,
      54,    10,    -1,     3,    29,    30,    31,    32,    33,    34,
      10,    11,    29,    30,    31,    32,    33,    34,    -1,     3,
      29,    30,    31,    32,    33,    34,    10,    -1,    47,    29,
      30,    31,    32,    33,    34,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,    33,
      34
  };

  const unsigned char
  Parser::yystos_[] =
  {
       0,    12,    41,    42,    39,     0,    43,     7,    12,    44,
      14,    39,    18,     7,    13,    17,    45,    39,    26,    15,
      16,    39,    46,    47,    49,    54,     7,     5,     3,    11,
      39,     8,    14,    50,    45,    27,     4,    17,    47,    48,
      49,     3,    39,    39,     8,     4,     5,     5,    39,    46,
      51,    52,    51,     6,     9,     6,     6,     7,    52,     7,
       7,     7,    19,    21,    28,    39,    55,    53,    53,    53,
       5,     5,     5,     3,    36,     8,     8,    23,    39,    54,
      55,     8,     8,     5,    22,    25,    35,    37,    38,    39,
      58,    58,    58,    58,    58,     8,    58,    58,    16,    39,
      58,     3,     6,    10,    29,    30,    31,    32,    33,    34,
       6,     6,     4,    11,    11,     6,     3,     5,    58,    55,
      24,    39,    58,    58,    58,    58,    58,    58,    55,    11,
      36,     8,    58,     6,     4,    20,     5,    58,     4,    55,
      56,    57,    58,    11,     6,     9,    58
  };

  const unsigned char
  Parser::yyr1_[] =
  {
       0,    40,    41,    42,    43,    43,    44,    44,    45,    45,
      46,    47,    47,    47,    47,    48,    49,    49,    50,    50,
      50,    51,    51,    52,    52,    53,    53,    53,    54,    55,
      55,    55,    55,    55,    55,    56,    56,    57,    57,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    58,    58
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     2,    17,     0,     2,     6,     8,     0,     2,
       2,     3,     1,     1,     1,     1,     0,     2,     9,     9,
      12,     0,     1,     1,     3,     0,     2,     2,     2,     3,
       7,     5,     5,     4,     7,     0,     1,     1,     3,     2,
       3,     3,     3,     3,     3,     3,     4,     3,     6,     1,
       1,     1,     1,     5,     4,     3
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
  "VariableDeclaration", "Type", "Void", "MethodDeclarationList",
  "MethodDeclaration", "ArgumentDeclarationList",
  "NonEmptyArgumentDeclarationList", "StatementList",
  "VariableDeclarationStatement", "Statement", "ArgumentsList",
  "NonEmptyArgumentsList", "Expression", YY_NULLPTR
  };


  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   125,   125,   130,   150,   156,   162,   173,   188,   194,
     200,   211,   217,   223,   229,   240,   247,   253,   259,   273,
     287,   303,   309,   314,   320,   326,   332,   337,   343,   350,
     358,   363,   365,   367,   371,   377,   379,   383,   385,   392,
     393,   394,   395,   396,   397,   398,   400,   401,   402,   404,
     405,   406,   407,   408,   409,   410
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
#line 1557 "Parser.cpp" // lalr1.cc:1167
#line 414 "parser.bison" // lalr1.cc:1168


void
Grammar::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}
