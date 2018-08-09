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

%type<std::shared_ptr<MainClass>> MainClass;
%type<std::shared_ptr<ClassDeclarationList>> ClassDeclarationList;
%type<std::shared_ptr<ClassDeclaration>> ClassDeclaration;
%type<std::shared_ptr<Type>> Type;
%type<std::shared_ptr<Type>> Void;
%type<std::shared_ptr<MethodDeclarationList>> MethodDeclarationList;
%type<std::shared_ptr<MethodDeclaration>> MethodDeclaration;
%type<std::shared_ptr<IStatement>> Statement;
%type<std::shared_ptr<CStatementList>> StatementList;
%type<std::shared_ptr<VariableDeclarationStatement>> VariableDeclarationStatement;
%type<std::shared_ptr<VariableDeclarationStatementList>> VariableDeclarationStatementList;
%type<std::shared_ptr<VariableDeclaration>> VariableDeclaration;
%type<std::shared_ptr<ArgumentDeclarationList>> ArgumentDeclarationList;
%type<std::shared_ptr<ArgumentDeclarationList>> NonEmptyArgumentDeclarationList;
%type<std::shared_ptr<ArgumentsList>> ArgumentsList;
%type<std::shared_ptr<ArgumentsList>> NonEmptyArgumentsList;
%type<std::shared_ptr<IExpression>> Expression;
//%type<Identifier*> Identifier

%token<std::string> ID

%%

Goal:
    MainClass ClassDeclarationList {
        program = Program($1, $2, LOCATION(@$));
    };

MainClass:
    CLASS ID[mainClass] LBRACE
        PUBLIC STATIC VOID MAIN LPAREN
            STRING LBRACKET RBRACKET
            ID[id]
        RPAREN
        LBRACE
            Statement[s]
        RBRACE
    RBRACE {
        $$ = std::make_shared<MainClass>(
            MainClass(
                std::make_shared<Identifier>(Identifier($mainClass)),
                std::make_shared<Identifier>(Identifier($id)),
                $s,
                LOCATION(@$)
            )
         );
    };

ClassDeclarationList:
    %empty {
        $$ = std::make_shared<ClassDeclarationList>(
            ClassDeclarationList(LOCATION(@$))
        );
    }
    |
    ClassDeclarationList ClassDeclaration {
        $1->nodes.emplace_back($2);
        $$ = $1;
    };

ClassDeclaration:
    CLASS ID[id] LBRACE
        VariableDeclarationStatementList[v]
        MethodDeclarationList[m]
    RBRACE {
        $$ = std::make_shared<ClassDeclaration>(
            ClassDeclaration(
                std::make_shared<Identifier>(Identifier($id)), $v, $m, LOCATION(@$)
            )
        );
    }
    |
    CLASS ID[id] EXTENDS ID[b] LBRACE
        VariableDeclarationStatementList[v]
        MethodDeclarationList[m]
    RBRACE {
        $$ = std::make_shared<ClassDeclaration>(
            ClassDeclaration(
                std::make_shared<Identifier>(Identifier($id)),
                std::make_shared<Identifier>(Identifier($b)),
                $v, $m,
                LOCATION(@$)
            )
        );
    };

VariableDeclarationStatementList:
    %empty {
        $$ = std::make_shared<VariableDeclarationStatementList>(
            VariableDeclarationStatementList(LOCATION(@$))
        );
    }
    |
    VariableDeclarationStatementList[l] VariableDeclarationStatement[v] {
             $1->nodes.emplace_back($2);
             $$ = $1;
    };

VariableDeclaration:
    Type ID[y] {
        $$ = std::make_shared<VariableDeclaration>(
            VariableDeclaration(
                $1,
                std::make_shared<Identifier>(Identifier($y)),
                LOCATION(@$)
            )
        );
    };

Type:
    INT LBRACKET RBRACKET {
        $$ = std::make_shared<Type>(
            Type(TT_Array, LOCATION(@$))
        );
    }
    |
    BOOLEAN {
        $$ = std::make_shared<Type>(
            Type(TT_Bool, LOCATION(@$))
        );
    }
    |
    INT {
        $$ = std::make_shared<Type>(
            Type(TT_Int, LOCATION(@$))
        );
    }
    |
    ID {
        $$ = std::make_shared<Type>(
            Type(
                TT_Object,
                std::make_shared<Identifier>(Identifier($1)),
                LOCATION(@$)
            )
        );
    };

Void:
    VOID {
        $$ = std::make_shared<Type>(
            Type(TT_Void, LOCATION(@$))
        );
    };

MethodDeclarationList:
    %empty {
        $$ = std::make_shared<MethodDeclarationList>(
            MethodDeclarationList(LOCATION(@$))
        );
    }
    |
    MethodDeclarationList[l] MethodDeclaration[m] {
            $1->nodes.emplace_back($2);
            $$ = $1;
    };

MethodDeclaration:
    PUBLIC Type[rt] ID[id] LPAREN
        ArgumentDeclarationList[a]
    RPAREN LBRACE
        StatementList[s]
    RBRACE {
        $$ = std::make_shared<MethodDeclaration>(
            MethodDeclaration(
                std::make_shared<Identifier>(Identifier($id)),
                $rt, $a, $s,
                LOCATION(@$)
            )
         );
    }
    |
    PUBLIC Void[rt] ID[id] LPAREN
        ArgumentDeclarationList[a]
    RPAREN LBRACE
        StatementList[s]
    RBRACE {
        $$ = std::make_shared<MethodDeclaration>(
            MethodDeclaration(
                std::make_shared<Identifier>(Identifier($id)),
                $rt, $a, $s,
                LOCATION(@$)
            )
        );
    }
    |
    PUBLIC Type[rt] ID[id] LPAREN
        ArgumentDeclarationList[a]
    RPAREN LBRACE
        StatementList[s]
        RETURN Expression[e] SEMICOLON
    RBRACE {
        $$ = std::make_shared<MethodDeclaration>(
            MethodDeclaration(
                std::make_shared<Identifier>(Identifier($id)),
                $rt, $e, $a, $s,
                LOCATION(@$)
            )
        );
    };

ArgumentDeclarationList:
    %empty {
        $$ = std::make_shared<ArgumentDeclarationList>(
            ArgumentDeclarationList(LOCATION(@$))
        );
    }
    |
    NonEmptyArgumentDeclarationList {
        $$ = $1;
    };

NonEmptyArgumentDeclarationList:
    VariableDeclaration {
        $$ = std::make_shared<ArgumentDeclarationList>(
            ArgumentDeclarationList($1, LOCATION(@$))
        );
    }
    |
    VariableDeclaration COMMA NonEmptyArgumentDeclarationList {
        $3->nodes.emplace_back($1);
        $$ = $3;
    };

StatementList:
    %empty {
        $$ =  std::make_shared<CStatementList>(
            CStatementList(LOCATION(@$))
        );
    }
    |
    StatementList[sl] Statement[s] {
        $1->nodes.emplace_back($2);
        $$ = $1;
    }
    |
    StatementList[ls] VariableDeclarationStatement[s] {
        $1->nodes.emplace_back($2);
        $$ = $1;
    };

VariableDeclarationStatement:
    VariableDeclaration SEMICOLON {
        $$ = std::make_shared<VariableDeclarationStatement>(
            VariableDeclarationStatement($1, LOCATION(@$))
        );
    };

Statement:
    LBRACE
        StatementList[l]
    RBRACE {
        $$ = std::make_shared<NestedStatement>(
            NestedStatement($l, LOCATION(@$))
        );
    }
    |
    IF LPAREN Expression[e] RPAREN
        Statement[is]
    ELSE
        Statement[es] { $$ = std::make_shared<IfStatement>(IfStatement($e, $is, $es, LOCATION(@$))); }
    |
    WHILE LPAREN Expression[e] RPAREN Statement[s] { $$ = std::make_shared<WhileStatement>(WhileStatement($e, $s, LOCATION(@$))); }
    |
    PRINT LPAREN Expression[e] RPAREN SEMICOLON { $$ = std::make_shared<PrintStatement>(PrintStatement($e, LOCATION(@$))); }
    |
    ID[id] ASSIGN Expression[e] SEMICOLON { $$ = std::make_shared<AssignStatement>(AssignStatement(
        std::make_shared<Identifier>(Identifier($id)), $e, LOCATION(@$))
    ); }
    |
    ID[id] LBRACKET Expression[ae] RBRACKET ASSIGN Expression[e] SEMICOLON { $$ = std::make_shared<ArrayAssignStatement>(
    ArrayAssignStatement(std::make_shared<Identifier>(Identifier($id)), $ae, $e, LOCATION(@$))); }
    ;


ArgumentsList:
    %empty { $$ = std::make_shared<ArgumentsList>(ArgumentsList(LOCATION(@$))); }
    |
    NonEmptyArgumentsList { $$ = $1; }
    ;

NonEmptyArgumentsList:
    Expression[e] { $$ = std::make_shared<ArgumentsList>(ArgumentsList($e, LOCATION(@$))); }
    |
    ArgumentsList[l] COMMA Expression[e] {
        $1->nodes.emplace_back($3);
        $$ = $1;
    }
    ;

Expression:
    NOT Expression[E] { $$ = std::make_shared<NotExpression>( $E, LOCATION(@$)); }
	| Expression[L] PLUS Expression[R] { $$ = std::make_shared<BinopExpression>(BinopExpression($L, $R, BOT_Plus, LOCATION(@$))); }
	| Expression[L] MINUS Expression[R] { $$ = std::make_shared<BinopExpression>(BinopExpression($L, $R, BOT_Minus, LOCATION(@$))); }
	| Expression[L] MULT Expression[R] { $$ = std::make_shared<BinopExpression>(BinopExpression($L, $R, BOT_Multiply, LOCATION(@$))); }
	| Expression[L] AND Expression[R] { $$ = std::make_shared<BinopExpression>(BinopExpression($L, $R, BOT_And, LOCATION(@$))); }
	| Expression[L] EQUAL Expression[R] { $$ = std::make_shared<BinopExpression>(BinopExpression($L, $R, BOT_Equal, LOCATION(@$))); }
	| Expression[L] LESS Expression[R] { $$ = std::make_shared<BinopExpression>(BinopExpression($L, $R, BOT_Less, LOCATION(@$))); }

	| Expression[A] LBRACKET Expression[N] RBRACKET{ $$ = std::make_shared<ArrayItemExpression>(ArrayItemExpression( $A, $N, LOCATION(@$))); }
	| Expression[A] DOT LENGTH { $$ = std::make_shared<ArrayLengthExpression>(ArrayLengthExpression( $A, LOCATION(@$))); }
	| Expression[O] DOT ID[M] LPAREN ArgumentsList[A] RPAREN { $$ = std::make_shared<CallExpression>(CallExpression(
	    $O, std::make_shared<Identifier>(Identifier($M)), $A, LOCATION(@$))); }
	| INTEGER { $$ = std::make_shared<ConstExpression>(ConstExpression( $1, LOCATION(@$))); }
	| BOOL_VALUE { $$ = std::make_shared<BoolExpression>(BoolExpression( $1, LOCATION(@$))); }
	| ID { $$ = std::make_shared<IdExpression>(IdExpression( std::make_shared<Identifier>(Identifier($1)), LOCATION(@$))); }
	| THIS { $$ = std::make_shared<IdExpression>(IdExpression( std::make_shared<Identifier>(Identifier("this")), LOCATION(@$))); }
	| NEW INT[T] LBRACKET Expression[L] RBRACKET { $$ = std::make_shared<NewArrayExpression>(NewArrayExpression( $L, LOCATION(@$))); }
	| NEW ID[T] LPAREN RPAREN { $$ = std::make_shared<NewObjectExpression>(NewObjectExpression( std::make_shared<Identifier>(Identifier($T)), LOCATION(@$))); }
	| LPAREN Expression[E] RPAREN { $$ = $E; }
;


%%

void
Grammar::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}