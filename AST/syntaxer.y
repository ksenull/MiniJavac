%{
#include <stdio.h>

int yylex(void);

void yyerror(char* str) {
    fprintf(stderr, "Error: %s\n", str);
}
%}

%token LROUND RROUND LCURLY RCURLY LSQUARE RSQUARE INT_ARRAY INT BOOLEAN NEW LENGTH SEMICOLON DOT COMMA NOT AND LESS PLUS MINUS MULTIPLY ASSIGN THIS PRINT WHILE IF ELSE RETURN PUBLIC CLASS EXTENDS STRING_ARG MAIN

%union {
    int number;
    char* string;
}

%token <string> BOOL_VALUE
%token <number> INTEGER
%token <string> ID

%%

goal:
    mainClass (classDeclaration)* '\0'
    |
    ;

mainClass:
    CLASS identifier LCURLY MAIN LROUND STRING_ARG identifier RROUND LCURLY statement RCURLY RCURLY
    ;

classDefinition:
    CLASS identifier (EXTENDS idenifier)? LCURLY (varDeclaration)* (methodDeclaration)* RCURLY
    ;

varDeclaration:
    type identifier SEMICOLON
    ;

methodDeclaration:
    PUBLIC type identifier LROUND (type identifier (COMMA type identifier)*)? RROUND LCURLY (varDeclaration)* (statement)*  RETURN expression SEMICOLON
    ;

type:
    INT_ARRAY
    | BOOLEAN
    | INT
    ;

statement:
    LCURLY (statement)* RCURLY
    | IF LROUND expression RROUND statement (ELSE statement)?
    | WHILE LROUND expression RROUND statement
    | identifier ASSIGN expression SEMICOLON
    | identifier LSQUARE expression RSQUARE ASSIGN expression SEMICOLON
    ;

expression:
    expression (AND | LESS | PLUS | MINUS | MULTIPLY) expression
    | expression LSQUARE expression RSQUARE
    | expression DOT LENGTH
    | expression DOT identifier LROUND (exression (COMMA expression)* )? RROUND
    | INTEGER
    | BOOL_VALUE
    | identifier
    | THIS
    | NEW INT LSQUARE expression RSQUARE
    | NEW identifier LROUND RROUND
    | NOT (expression | (LROUND expression RROUND))
    ;

identifier:
    ID { $$ = $1; printf("ID %s\n", $1); }
    ;

%%

int main(void) {
    yyparse();
    return 0;
}

