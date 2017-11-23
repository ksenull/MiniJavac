%{
#include <stdio.h>
#include <unistd.h>
//int yylex(void);

%}

%union {
    int number;
    char* string;
}
/*
%token LROUND RROUND LCURLY RCURLY LSQUARE RSQUARE 
%token INT_ARRAY INT BOOLEAN 
%token NEW LENGTH THIS
%token SEMICOLON DOT COMMA NOT AND LESS PLUS MINUS MULTIPLY ASSIGN 
%token PRINT WHILE IF ELSE RETURN 
%token PUBLIC CLASS EXTENDS STRING_ARG MAIN

%token <number> BOOL_VALUE
%token <number> INTEGER
%token <string> ID
*/
//%token END 0

%%
/*
goal:
    mainClass zeroOrMoreClasses
    |
    ;

mainClass:
    CLASS identifier LCURLY MAIN LROUND STRING_ARG identifier RROUND LCURLY statement RCURLY RCURLY
    ;

zeroOrMoreClasses:
    classDeclaration zeroOrMoreClasses
    | 
    ;

classDeclaration:
    CLASS identifier anyExtends LCURLY zeroOrMoreVars zeroOrMoreMethods RCURLY
    ;

anyExtends:
    EXTENDS identifier
    |
    ;

zeroOrMoreVars:
    varDeclaration zeroOrMoreVars
    |
    ;

varDeclaration:
    type identifier SEMICOLON
    ;

zeroOrMoreMethods:
    methodDeclaration zeroOrMoreMethods
    |
    ;

methodDeclaration:
    PUBLIC type identifier LROUND anyMethodArgs RROUND LCURLY zeroOrMoreVars zeroOrMoreStatements  RETURN expression SEMICOLON
    ;

anyMethodArgs:
    type identifier zeroOrMoreMethodArgs
    |
    ;

zeroOrMoreMethodArgs:
    COMMA type identifier zeroOrMoreMethodArgs
    |
    ;

type:
    INT_ARRAY
    | BOOLEAN
    | INT
    ;

zeroOrMoreStatements:
    statement zeroOrMoreStatements
    |
    ;

statement:
    LCURLY zeroOrMoreStatements RCURLY
    | IF LROUND expression RROUND statement anyElse
    | WHILE LROUND expression RROUND statement
    | identifier ASSIGN expression SEMICOLON
    | identifier LSQUARE expression RSQUARE ASSIGN expression SEMICOLON
    ;

anyElse:
    ELSE statement
    |
    ;

anyExpressionSeq:
    expression zeroOrMoreExpressionSeq
    |
    ;

zeroOrMoreExpressionSeq:
    COMMA expression zeroOrMoreExpressionSeq
    |
    ;

expression:
    expression AND expression
    | expression LESS expression
    | expression PLUS expression
    | expression MINUS expression
    | expression MULTIPLY expression
    | expression LSQUARE expression RSQUARE
    | expression DOT LENGTH
    | expression DOT identifier LROUND anyExpressionSeq RROUND
    | INTEGER
    | BOOL_VALUE
    | identifier
    | THIS
    | NEW INT LSQUARE expression RSQUARE
    | NEW identifier LROUND RROUND
    | NOT expression
    | NOT LROUND expression RROUND
    ;

identifier:
    ID { printf("ID %s\n", $1); }
    ;

%%

int main(void) {
    yyparse();
    return 0;
}
*/
