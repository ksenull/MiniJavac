yacc --verbose --debug -d syntaxer.y -o syntaxParser.cc
lex lexer.lex 
gcc -c lex.yy.c -o lex.yy.o -ll
g++ lex.yy.o syntaxParser.cc -o example

