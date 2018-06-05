%{
#include "../ast.h"
#include "../lex/token.h"
int yylex();
void yyerror(char *s);
%}

%token TEMP

%%
body: { stmts } 
    | stmt
stmts: 
     | stmt stmts
stmt:

%%

