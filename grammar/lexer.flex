%{
/* C++ string header, for string ops below */
#include <string>
#include <iostream>

/* Implementation of yyFlexScanner */
#include "Scanner.h"
#undef  YY_DECL
#define YY_DECL Grammar::Parser::symbol_type Grammar::Scanner::Lex()

// Work around an incompatibility in flex (at least versions
// 2.5.31 through 2.5.33): it generates code that does
// not conform to C89.  See Debian bug 333231
// <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.
# undef yywrap
# define yywrap() 1

// The location of the current token.
static Grammar::location loc;

#define PROCESS_VALUE_TOKEN(TOKEN, VALUE) { \
    std::cout << #TOKEN << " " << VALUE  << std::endl; \
    return Parser::make_##TOKEN(VALUE, loc); \
}

#define PROCESS_TOKEN(TOKEN) { \
    std::cout << #TOKEN << " " << loc << std::endl; \
    return Parser::make_##TOKEN(loc); \
}


/* typedef to make the returns for the tokens shorter */
using token = Grammar::Parser::token;

/* define yyterminate as this instead of NULL */
#define yyterminate() return( token::END )


// Code run each time a pattern is matched.
# define YY_USER_ACTION  loc.columns (yyleng);


#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wpragmas"

%}

%option debug
%option nodefault
%option yyclass="Grammar::Scanner"
%option noyywrap
%option c++
%option outfile="Scanner.cpp"


SPACE       [ \t]+
NEWLINE     [\n]+

BOOL_VALUE  (true|false)

DIGIT       [0-9]
INTEGER     ([1-9]{DIGIT}*|0)
ID          [a-zA-Z_][_a-zA-Z0-9]*

COMMENT     "//".*\n

%%
%{
  // Code run each time yylex is called.
  loc.step ();
%}

{SPACE}    {
    std::cout << " ";
    loc.step();
}

{NEWLINE}   {
    std::cout << std::endl;
    loc.lines(yyleng);
    loc.step();
}

{COMMENT}       {
    std::cout << std::endl;
    loc.lines(std::count(yytext, yytext + yyleng, '\n'));
    loc.step();
}

class         { PROCESS_TOKEN(CLASS) }
extends       { PROCESS_TOKEN(EXTENDS) }
public        { PROCESS_TOKEN(PUBLIC) }

boolean       { PROCESS_TOKEN(BOOLEAN) }
int           { PROCESS_TOKEN(INT) }
void          { PROCESS_TOKEN(VOID) }

"+"             { PROCESS_TOKEN(PLUS) }
"-"             { PROCESS_TOKEN(MINUS) }
"*"             { PROCESS_TOKEN(MULT) }
"&&"            { PROCESS_TOKEN(AND) }
"<"             { PROCESS_TOKEN(LESS) }
"=="            { PROCESS_TOKEN(EQUAL) }
"="             { PROCESS_TOKEN(ASSIGN) }
"!"             { PROCESS_TOKEN(NOT) }

"["             { PROCESS_TOKEN(LBRACKET) }
"]"             { PROCESS_TOKEN(RBRACKET) }
"("             { PROCESS_TOKEN(LPAREN) }
")"             { PROCESS_TOKEN(RPAREN) }
"{"             { PROCESS_TOKEN(LBRACE) }
"}"             { PROCESS_TOKEN(RBRACE) }
","             { PROCESS_TOKEN(COMMA) }
"."             { PROCESS_TOKEN(DOT) }
";"             { PROCESS_TOKEN(SEMICOLON) }

static        { PROCESS_TOKEN(STATIC) }
if            { PROCESS_TOKEN(IF) }
else          { PROCESS_TOKEN(ELSE) }
while         { PROCESS_TOKEN(WHILE) }
new           { PROCESS_TOKEN(NEW) }
return        { PROCESS_TOKEN(RETURN) }
length        { PROCESS_TOKEN(LENGTH) }

this          { PROCESS_TOKEN(THIS) }
main          { PROCESS_TOKEN(MAIN) }
String        { PROCESS_TOKEN(STRING) }
System.out.println { PROCESS_TOKEN(PRINT) }


{ID}            { PROCESS_VALUE_TOKEN(ID, yytext ) }
{BOOL_VALUE}    { PROCESS_VALUE_TOKEN(BOOL_VALUE, strcmp(yytext, "false")) }
{INTEGER}       { PROCESS_VALUE_TOKEN(INTEGER, std::stoi(yytext)) }

<<EOF>>         { PROCESS_TOKEN(END) }
.               ;
%%