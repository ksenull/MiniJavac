yacc -d syntaxer.y
lex lexer.lex
cc lex.yy.c y.tab.c -o testC
