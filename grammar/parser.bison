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

#define LOCATION(l) \
    Location{l.begin.line, l.begin.column, l.end.line, l.end.column}
}

%parse-param { Scanner& scanner }
%parse-param { Program& program }

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
%type<IStatement*> Statement;
%type<CStatementList*> StatementList;
%type<VariableDeclarationStatement*> VariableDeclarationStatement;
%type<VariableDeclarationStatementList*> VariableDeclarationStatementList;
%type<VariableDeclaration*> VariableDeclaration;
%type<ArgumentDeclarationList*> ArgumentDeclarationList;
%type<ArgumentDeclarationList*> NonEmptyArgumentDeclarationList;
%type<ArgumentsList*> ArgumentsList;
%type<ArgumentsList*> NonEmptyArgumentsList;
%type<IExpression*> Expression;

%token<Identifier> ID

%%

Goal:
    MainClass ClassDeclarationList { program = Program($1, $2, LOCATION(@$)); }
    ;

MainClass:
    CLASS ID[mainClass] LBRACE
        PUBLIC STATIC VOID MAIN LPAREN
            STRING LBRACKET RBRACKET
            ID[id]
        RPAREN
        LBRACE
            Statement[s]
        RBRACE
    RBRACE { $$ = new MainClass($mainClass, $id, $s, LOCATION(@$)); }
    ;

ClassDeclarationList:
    %empty { $$ = new ClassDeclarationList(); }
    |
    ClassDeclarationList ClassDeclaration {
        $1->nodes.emplace_back($2);
        $$ = $1;
    }
    ;

ClassDeclaration:
    CLASS ID[id] LBRACE
        VariableDeclarationStatementList[v]
        MethodDeclarationList[m]
    RBRACE { $$ = new ClassDeclaration($id, $v, $m, LOCATION(@$)); }
    |
    CLASS ID[id] EXTENDS ID[b] LBRACE
        VariableDeclarationStatementList[v]
        MethodDeclarationList[m]
    RBRACE { $$ = new ClassDeclaration($id, $b, $v, $m, LOCATION(@$)); }
    ;

VariableDeclarationStatementList:
    %empty { $$ = new VariableDeclarationStatementList(); }
    |
    VariableDeclarationStatementList[l] VariableDeclarationStatement[v] {
             $1->nodes.emplace_back($2);
             $$ = $1;
    }
    ;

VariableDeclaration:
    Type ID[y] { $$ = new VariableDeclaration($1, $2, LOCATION(@$)); }
    ;

Type:
    INT LBRACKET RBRACKET { $$ = new Type(TT_Array, LOCATION(@$)); }
    |
    BOOLEAN { $$ = new Type(TT_Bool, LOCATION(@$)); }
    |
    INT { $$ = new Type(TT_Int, LOCATION(@$)); }
    |
    ID { $$ = new Type(TT_Object, $1, LOCATION(@$)); }
   ;

MethodDeclarationList:
    %empty { $$ = new MethodDeclarationList(); }
    |
    MethodDeclarationList[l] MethodDeclaration[m] {
            $1->nodes.emplace_back($2);
            $$ = $1;
    }
    ;

MethodDeclaration:
    PUBLIC Type[rt] ID[id] LPAREN
        ArgumentDeclarationList[a]
    RPAREN LBRACE
        StatementList[s]
    RBRACE { $$ = new MethodDeclaration($id, $rt, $a, $s, LOCATION(@$)); }
    |
    PUBLIC Type[rt] ID[id] LPAREN
        ArgumentDeclarationList[a]
    RPAREN LBRACE
        StatementList[s]
        RETURN Expression[e] SEMICOLON
    RBRACE { $$ = new MethodDeclaration($id, $rt, $e, $a, $s, LOCATION(@$)); }
    ;

ArgumentDeclarationList:
    %empty { $$ = new ArgumentDeclarationList(); }
    |
    NonEmptyArgumentDeclarationList { $$ = $1; }
    ;

NonEmptyArgumentDeclarationList:
    VariableDeclaration { $$ = new ArgumentDeclarationList($1); }
    |
    VariableDeclaration COMMA NonEmptyArgumentDeclarationList {
        $3->nodes.emplace_back($1);
        $$ = $3;
    }
    ;

StatementList:
    %empty { $$ =  new CStatementList(); }
    |
    StatementList[sl] Statement[s] {
        $1->nodes.emplace_back($2);
        $$ = $1;
    }
    |
    StatementList[ls] VariableDeclarationStatement[s] {
        $1->nodes.emplace_back($2);
        $$ = $1;
    }
    ;

VariableDeclarationStatement:
    VariableDeclaration SEMICOLON { $$ = new VariableDeclarationStatement($1, LOCATION(@$)); }
    ;

Statement:
    LBRACE
        StatementList[l]
    RBRACE { $$ = new NestedStatement($l, LOCATION(@$)); }
    |
    IF LPAREN Expression[e] RPAREN
        Statement[is]
    ELSE
        Statement[es] { $$ = new IfStatement($e, $is, $es, LOCATION(@$)); }
    |
    WHILE LPAREN Expression[e] RPAREN Statement[s] { $$ = new WhileStatement($e, $s, LOCATION(@$)); }
    |
    PRINT LPAREN Expression[e] RPAREN SEMICOLON { $$ = new PrintStatement($e, LOCATION(@$)); }
    |
    ID[id] ASSIGN Expression[e] SEMICOLON { $$ = new AssignStatement($id, $e, LOCATION(@$)); }
    |
    ID[id] LBRACKET Expression[ae] RBRACKET ASSIGN Expression[e] SEMICOLON { $$ = new ArrayAssignStatement($id, $ae, $e, LOCATION(@$)); }
    ;


ArgumentsList:
    %empty { $$ = new ArgumentsList(); }
    |
    NonEmptyArgumentsList { $$ = $1; }
    ;

NonEmptyArgumentsList:
    Expression[e] { $$ = new ArgumentsList($e); }
    |
    ArgumentsList[l] COMMA Expression[e] {
        $1->nodes.emplace_back($3);
        $$ = $1;
    }
    ;

Expression:
	Expression[L] PLUS Expression[R] { $$ = new BinopExpression( $L, $R, BOT_Plus, LOCATION(@$)); }
	| Expression[L] MINUS Expression[R] { $$ = new BinopExpression( $L, $R, BOT_Minus, LOCATION(@$)); }
	| Expression[L] MULT Expression[R] { $$ = new BinopExpression( $L, $R, BOT_Multiply, LOCATION(@$)); }
	| Expression[L] AND Expression[R] { $$ = new BinopExpression( $L, $R, BOT_And, LOCATION(@$)); }
	| Expression[L] EQUAL Expression[R] { $$ = new BinopExpression( $L, $R, BOT_Equal, LOCATION(@$)); }
	| Expression[L] LESS Expression[R] { $$ = new BinopExpression( $L, $R, BOT_Less, LOCATION(@$)); }

	| Expression[A] LBRACKET Expression[N] RBRACKET{ $$ = new ArrayItemExpression( $A, $N, LOCATION(@$)); }
	| Expression[A] DOT LENGTH { $$ = new ArrayLengthExpression( $A, LOCATION(@$)); }
	| Expression[O] DOT ID[M] LPAREN ArgumentsList[A] RPAREN { $$ = new CallExpression( $O, $M, $A, LOCATION(@$)); }
	| INTEGER { $$ = new ConstExpression( $1, LOCATION(@$)); }
	| BOOL_VALUE { $$ = new BoolExpression( $1, LOCATION(@$)); }
	| ID { $$ = new IdExpression( $1, LOCATION(@$)); }
	| THIS { $$ = new IdExpression( "this", LOCATION(@$)); }
	| NEW INT[T] LBRACKET Expression[L] RBRACKET { $$ = new NewArrayExpression( $L, LOCATION(@$)); }
	| NEW ID[T] LPAREN RPAREN { $$ = new NewObjectExpression( $T, LOCATION(@$)); }
	| NOT Expression[E] { $$ = new NotExpression( $E, LOCATION(@$)); }
	| LPAREN Expression[E] RPAREN { $$ = $E; }
;


%%

void
Grammar::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}