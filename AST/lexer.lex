%{
#include <stdio.h>
void yyerror(const char* s){
    fprintf(stderr, "lex error [%s] ", s); 
}
#include "y.tab.h"

#define mkstr(s)#s 
%}

SPACE       [ \t\n]+

LCURLY      \{
RCURLY      \}
LROUND      \(
RROUND      \)
LSQUARE     \[
RSQUARE     \]

BOOL_VALUE  true|false

INT_ARRAY   int{SPACE}{LSQUARE}{RSQUARE}
INT         int
BOOLEAN     boolean

NEW         new

LENGTH      length

SEMICOLON   ;

DOT         \.
COMMA       ,
NOT         \!
AND         &&
LESS        \<
PLUS        \+
MINUS       -
MULTIPLY    \*
ASSIGN      \=

THIS        this

IF          if
ELSE        else
WHILE       while
PRINT       System.out.println

RETURN      return
PUBLIC      public
CLASS       class
EXTENDS     extends
STRING_ARG  String{SPACE}?{LSQUARE}{SPACE}?{RSQUARE}
MAIN        public{SPACE}static{SPACE}void{SPACE}main

INTEGER     ([1-9][0-9]*)|0 
ID          [a-zA-Z_][_a-zA-Z0-9]*

%%

{CLASS}         printf("%s ", "CLASS");
{EXTENDS}       printf("%s ", "EXTENDS");
{INT_ARRAY}     printf("%s ", "INT_ARRAY");
{INT}           printf("%s ", "INT");
{BOOLEAN}       printf("%s ", "BOOLEAN");

{STRING_ARG}    printf("%s ", "STRING_ARG");
{MAIN}          printf("%s ", "MAIN");
{PUBLIC}        printf("%s ", "PUBLIC");

{LCURLY}        printf("%s ", "LCURLY");
{RCURLY}        printf("%s ", "RCURLY");
{LROUND}        printf("%s ", "LROUND");
{RROUND}        printf("%s ", "RROUND");
{LSQUARE}       printf("%s ", "LSQUARE");
{RSQUARE}       printf("%s ", "RSQUARE");

{NEW}           printf("%s ", "NEW");
{LENGTH}        printf("%s ", "LENGTH");
{SEMICOLON}     printf("%s ", "SEMICOLON");
{DOT}           printf("%s ", "DOT");
{COMMA}         printf("%s ", "COMMA");
{NOT}           printf("%s ", "NOT");
{AND}           printf("%s ", "AND");
{LESS}          printf("%s ", "LESS");
{PLUS}          printf("%s ", "PLUS");
{MINUS}         printf("%s ", "MINUS");
{MULTIPLY}      printf("%s ", "MULTIPLY");
{ASSIGN}        printf("%s ", "ASSIGN");
{THIS}          printf("%s ", "THIS");
{PRINT}         printf("%s ", "PRINT");
{WHILE}         printf("%s ", "WHILE");
{IF}            printf("%s ", "IF");
{ELSE}          printf("%s ", "ELSE");
{RETURN}        printf("%s ", "RETURN");
{BOOL_VALUE}    printf("%s %s ", "BOOL_VALUE", yytext);
{ID}            printf("%s %s ", "ID", yytext); 
{INTEGER}       printf("%s %d ", "INTEGER", atoi(yytext)); 
[\n]            printf("\n"); /* ignore whitespaces*/
[ \t]           ;
"//".*          ;
.               yyerror(yytext);
%%       

int yywrap(void) {
    return 1;
}

int main(int argc, char* argv[]) {
    yyin = fopen(argv[1], "r");
    yylex();
    fclose(yyin);
}
