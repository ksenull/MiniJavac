%{
#include <stdio.h>
#include <string.h>

//#include "y.tab.h"

void yyerror(const char* s) {
    fprintf(stderr, "lex error [%s] ", s);
}

//extern YYSTYPE yylval

%}

SPACE       [ \t\n]+

LCURLY      "{"
RCURLY      "}"
LROUND      "("
RROUND      ")"
LSQUARE     "["
RSQUARE     "]"

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

{CLASS}         printf("%s ", "CLASS");       //  return CLASS;
{EXTENDS}       printf("%s ", "EXTENDS");     //  return EXTENDS;
{INT_ARRAY}     printf("%s ", "INT_ARRAY");   //  return INT_ARRAY; 
{INT}           printf("%s ", "INT");         //  return INT;
{BOOLEAN}       printf("%s ", "BOOLEAN");     //  return BOOLEAN;

{STRING_ARG}    printf("%s ", "STRING_ARG");  //  return STRING_ARG;
{MAIN}          printf("%s ", "MAIN");        //  return MAIN;
{PUBLIC}        printf("%s ", "PUBLIC");      //  return PUBLIC;

{LCURLY}        printf("%s ", "LCURLY");      //  return LCURLY;
{RCURLY}        printf("%s ", "RCURLY");      //  return RCURLY;
{LROUND}        printf("%s ", "LROUND");      //  return LROUND;
{RROUND}        printf("%s ", "RROUND");      //  return RROUND;
{LSQUARE}       printf("%s ", "LSQUARE");     //  return LSQUARE;
{RSQUARE}       printf("%s ", "RSQUARE");     //  return RSQUARE;

{NEW}           printf("%s ", "NEW");         //  return NEW;
{LENGTH}        printf("%s ", "LENGTH");      //  return LENGTH;
{SEMICOLON}     printf("%s ", "SEMICOLON");   //  return SEMICOLON;
{DOT}           printf("%s ", "DOT");         //  return DOT;
{COMMA}         printf("%s ", "COMMA");       //  return COMMA;
{NOT}           printf("%s ", "NOT");         //  return NOT;
{AND}           printf("%s ", "AND");         //  return AND;
{LESS}          printf("%s ", "LESS");        //  return LESS;
{PLUS}          printf("%s ", "PLUS");        //  return PLUS;
{MINUS}         printf("%s ", "MINUS");       //  return MINUS;
{MULTIPLY}      printf("%s ", "MULTIPLY");    //  return MULTIPLY;
{ASSIGN}        printf("%s ", "ASSIGN");      //  return ASSIGN;
{THIS}          printf("%s ", "THIS");        //  return THIS;
{PRINT}         printf("%s ", "PRINT");       //  return PRINT;
{WHILE}         printf("%s ", "WHILE");       //  return WHILE;
{IF}            printf("%s ", "IF");          //  return IF;
{ELSE}          printf("%s ", "ELSE");        //  return ELSE;
{RETURN}        printf("%s ", "RETURN");      //  return RETURN;
{BOOL_VALUE}    printf("%s %s ", "BOOL_VALUE", yytext);   //  yylval.number = (strcmp(yytext, "true") != 0); return BOOL_VALUE;
{ID}            printf("%s %s ", "ID", yytext);           //  yylval.string = yytext; return ID;
{INTEGER}       printf("%s %d ", "INTEGER", atoi(yytext));//  yylval.number = atoi(yytext); return INTEGER;
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

