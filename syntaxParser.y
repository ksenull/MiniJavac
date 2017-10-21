%{
#include <stdio.h>
#include <string.h>

#define YYSTYPE char*

extern "C" {
    int yyparse(void);
    int yylex(void);
    void yyerror(const char* str) {
        fprintf(stderr, "Error: %s\n", str);
    }

    int yywrap() {
        return 1;
    }
}

main() {
    yyparse();
}
%}

%token ID

%%

expression:
    identifier
    ;

identifier:
    ID
    {
        printf("ID %s\n", $1);
    }
    ;
