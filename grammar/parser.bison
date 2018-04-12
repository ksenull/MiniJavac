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
#include "../ast/nodes/Nodes.h"
using namespace ast;
using namespace nodes;

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
%type<ClassDeclarationList*> ClassDeclarationList;
%type<ClassDeclaration*> ClassDeclaration;
%type<Type*> Type;
%type<MethodDeclarationList*> MethodDeclarationList;
%type<MethodDeclaration*> MethodDeclaration;
%type<Statement*> Statement;
%type<StatementList*> StatementList;
%type<VariableDeclarationStatement*> VariableDeclarationStatement;
%type<VariableDeclarationStatementList*> VariableDeclarationStatementList;
%type<VariableDeclaration*> VariableDeclaration;
%type<ArgumentDeclarationList*> ArgumentDeclarationList;
%type<ArgumentDeclarationList*> NonEmptyArgumentDeclarationList;
%type<ArgumentsList*> ArgumentsList;
%type<ArgumentsList*> NonEmptyArgumentsList;
%type<Expression*> Expression;

%token<Identifier> ID

%%

Goal:
    MainClass ClassDeclarationList { program = new Program($1, $2); }
    ;

MainClass:
    CLASS ID LBRACE
        PUBLIC STATIC VOID MAIN LPAREN
            STRING LBRACKET RBRACKET
            ID[id]
        RPAREN
        LBRACE
            Statement[s]
        RBRACE
    RBRACE { $$ = new MainClass($id, $s); }
    ;

ClassDeclarationList:
    %empty { $$ = nullptr; }
    |
    ClassDeclarationList ClassDeclaration { $$ = new ClassDeclarationList($2, $1); }
    ;

ClassDeclaration:
    CLASS ID[id] LBRACE
        VariableDeclarationStatementList[v]
        MethodDeclarationList[m]
    RBRACE { $$ = new ClassDeclaration($id, $v, $m); }
    |
    CLASS ID[id] EXTENDS ID[b] LBRACE
        VariableDeclarationStatementList[v]
        MethodDeclarationList[m]
    RBRACE { $$ = new ClassDeclaration($id, $b, $v, $m); }
    ;

VariableDeclarationStatementList:
    %empty { $$ = nullptr; }
    |
    VariableDeclarationStatementList[l] VariableDeclarationStatement[v] { $$ = new VariableDeclarationStatementList($v, $l); }
    ;

VariableDeclaration:
    Type ID[y] { $$ = new VariableDeclaration($1, $2); }
    ;

Type:
    INT LBRACKET RBRACKET { $$ = new Type(TT_Array); }
    |
    BOOLEAN { $$ = new Type(TT_Bool); }
    |
    INT { $$ = new Type(TT_Int); }
    |
    ID { $$ = new Type(TT_Object, $1); }
   ;

MethodDeclarationList:
    %empty { $$ = nullptr; }
    |
    MethodDeclarationList[l] MethodDeclaration[m] { $$ = new MethodDeclarationList($m, $l); }
    ;

MethodDeclaration:
    PUBLIC Type[rt] ID[id] LPAREN
        ArgumentDeclarationList[a]
    RPAREN LBRACE
        StatementList[s]
    RBRACE { $$ = new MethodDeclaration($id, $rt, $a, $s); }
    |
    PUBLIC Type[rt] ID[id] LPAREN
        ArgumentDeclarationList[a]
    RPAREN LBRACE
        StatementList[s]
        RETURN Expression[e] SEMICOLON
    RBRACE { $$ = new MethodDeclaration($id, $rt, $e, $a, $s); }
    ;

ArgumentDeclarationList:
    %empty { $$ = nullptr; }
    |
    NonEmptyArgumentDeclarationList { $$ = $1; }
    ;

NonEmptyArgumentDeclarationList:
    VariableDeclaration { $$ = new ArgumentDeclarationList($1); }
    |
    VariableDeclaration COMMA NonEmptyArgumentDeclarationList { $$ = new ArgumentDeclarationList($1, $3); }
    ;

StatementList:
    %empty { $$ = nullptr; }
    |
    StatementList[sl] Statement[s] { $$ = new StatementList($s, $sl); }
    |
    StatementList[ls] VariableDeclarationStatement[s] { $$ = new StatementList($s, $ls); }
    ;

VariableDeclarationStatement:
    VariableDeclaration SEMICOLON { $$ = new VariableDeclarationStatement($1); }
    ;

Statement:
    LBRACE
        StatementList[l]
    RBRACE { $$ = new NestedStatement($l); }
    |
    IF LPAREN Expression[e] RPAREN
        Statement[is]
    ELSE
        Statement[es] { $$ = new IfStatement($e, $is, $es); }
    |
    WHILE LPAREN Expression[e] RPAREN Statement[s] { $$ = new WhileStatement($e, $s); }
    |
    PRINT LPAREN Expression[e] RPAREN SEMICOLON { $$ = new PrintStatement($e); }
    |
    ID[id] ASSIGN Expression[e] SEMICOLON { $$ = new AssignStatement($id, $e); }
    |
    ID[id] LBRACKET Expression[ae] RBRACKET ASSIGN Expression[e] SEMICOLON { $$ = new ArrayAssignStatement($id, $ae, $e); }
    ;


ArgumentsList:
    %empty { $$ = nullptr; }
    |
    NonEmptyArgumentsList { $$ = $1; }
    ;

NonEmptyArgumentsList:
    Expression[e] { $$ = new ArgumentsList($e); }
    |
    ArgumentsList[l] COMMA Expression[e] { $$ = new ArgumentsList($e, $l); }

Expression:
	Expression[L] PLUS Expression[R] { $$ = new BinopExpression( $L, $R, BOT_Plus ); }
	| Expression[L] MINUS Expression[R] { $$ = new BinopExpression( $L, $R, BOT_Minus ); }
	| Expression[L] MULT Expression[R] { $$ = new BinopExpression( $L, $R, BOT_Multiply ); }
	| Expression[L] AND Expression[R] { $$ = new BinopExpression( $L, $R, BOT_And ); }
	| Expression[L] EQUAL Expression[R] { $$ = new BinopExpression( $L, $R, BOT_Equal ); }
	| Expression[L] LESS Expression[R] { $$ = new BinopExpression( $L, $R, BOT_Less ); }

	| Expression[A] LBRACKET Expression[N] RBRACKET{ $$ = new ArrayItemExpression( $A, $N ); }
	| Expression[A] DOT LENGTH { $$ = new ArrayLengthExpression( $A ); }
	| Expression[O] DOT ID[M] LPAREN ArgumentsList[A] RPAREN { $$ = new CallExpression( $O, $M, $A ); }
	| INTEGER { $$ = new ConstExpression( $1 ); }
	| BOOL_VALUE { $$ = new BoolExpression( $1 ); }
	| ID { $$ = new IdExpression( $1 ); }
	| THIS { $$ = new IdExpression( "this" ); }
	| NEW Type[T] LBRACKET Expression[L] RBRACKET { $$ = new NewArrayExpression( $T, $L ); }
	| NEW ID[T] LPAREN RPAREN { $$ = new NewObjectExpression( $T ); }
	| NOT Expression[E] { $$ = new NotExpression( $E ); }
	| LPAREN Expression[E] RPAREN { $$ = $E; }
;


%%

void
Grammar::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}