%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define api.namespace {Grammar}
%define parser_class_name {Parser}


%code requires {
namespace Grammar {
    class Scanner;
}
#include "../nodes.h"
using namespace ast;

// The following definitions is missing when %locations isn't used
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

}

%parse-param { Scanner& scanner }
%parse-param { Program* program }

%output "Parser.cpp"
%defines "Parser.h"

%code{
   #include <iostream>

   #include "Scanner.h"

#undef yylex
#define yylex scanner.Lex
}

%locations
%define api.value.type variant
%define api.token.constructor
%define parse.assert

%token
    END 0
    LBRACKET "["
    RBRACKET "]"
    LPAREN "("
    RPAREN ")"
    LBRACE "{"
    RBRACE "}"
    COMMA ","
    DOT "."
    SEMICOLON ";"

    CLASS
    EXTENDS
    PUBLIC

    BOOLEAN
    INT
    VOID

    STATIC
    IF
    ELSE
    WHILE
    NEW
    RETURN
    LENGTH

    THIS
    MAIN
    STRING
    PRINT
;

%left COMMA
%left DOT
%left LBRACKET
%left EQUAL
%left LESS
%left AND
%left PLUS MINUS
%left MULT

%right NOT
%right ASSIGN

%nonassoc ELSE

%token<bool> BOOL_VALUE
%token<int> INTEGER

%type<MainClass*> MainClass;
%token<std::string> ID

%%

Goal:
    MainClass /*ClassDeclarationList */{ program = new Program($1/*, $2*/); }
    ;

MainClass:
    CLASS /*ID*/ LBRACE

    RBRACE { $$ = new MainClass(); }
    ;

%%

void
Grammar::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}