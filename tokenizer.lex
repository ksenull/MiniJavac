%{
#include <stdio.h>
//#include "syntaxParser.tab.h"
// нужно передавать самплы

#define YYSTYPE

extern YYSTYPE yylval;
%}

DIGIT       [0-9]
LETTER      [a-zA-Z]
SPACE       (" "|\t|\n)*

EOL         ;

TYPE        (int|boolean|int\[\])

LCURLY      \{
RCURLY      \}
LROUND      \(
RROUND      \)
LSQUARE     \[
RSQUARE     \]

BOOL        (true|false)
INT         [1-9]{DIGIT}*|0

ID          {LETTER}(_|{DIGIT}|{LETTER})*

BINOP       (&&|<|\+|-|\*)
NOT         \!
FIELD       \.

ASSIGN      =

IF          if
ELSE        else
WHILE       while
PRINT       System.out.println

MAIN        public{SPACE}+static{SPACE}+void{SPACE}+main
MAINARG     String({SPACE})?{LSQUARE}{RSQUARE}{SPACE}ID

CLASS       class
EXTENDS     extends

PUBLIC      public
RETURN      return

%%
{LCURLY}    printf("LCURLY");
{RCURLY}    printf("RCURLY");
{RETURN}    printf("RETURN");
{PUBLIC}    printf("PUBLIC");
{EXTENDS}   printf("EXTENDS");
{CLASS}     printf("CLASS");
{MAIN}      printf("MAIN");
{MAINARG}   printf("MAINARG");
{PRINT}     printf("PRINT");
{WHILE}     printf("WHILE");
{IF}        printf("IF");
{ELSE}      printf("ELSE");
{ASSIGN}    printf("ASSIGN");
{FIELD}     printf("FIELD");
{NOT}       printf("NOT");
{BINOP}     printf("BINOP (%s)", yytext);
{BOOL}      printf("BOOL(%s)", yytext);
{INT}       printf("INT (%s)", yytext);
{TYPE}      printf("TYPE (%s)", yytext);
{LROUND}    printf("LROUND");
{RROUND}    printf("RROUND");
{LSQUARE}   printf("LSQUARE");
{RSQUARE}   printf("RSQUARE");
{ID}        printf("ID %s", yytext);//yylval=yytext; return ID;
.           printf("lexer error"); abort();
%%
