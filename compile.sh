lex tokenizer.lex 
yacc --verbose --debug -d syntaxParser.y -o syntaxParser.cc
gcc -c lex.yy.c -o lex.yy.o -ll
g++ lex.yy.o syntaxParser.cc -o example

