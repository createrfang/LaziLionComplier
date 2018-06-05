%{
#include "../ast.h"
#include "../lex/token.h"
int yylex();
void yyerror(char *s);
%}

%token TEMP

%%
function_def: data_type name LPAREN arglist RPAREN fun_body
fun_body: LCURLYBRACKET stmts RCURLYBRACKET
body: fun_body
    | stmt
stmts: 
    | stmt stmts
stmt: assign_stmt
    | for_stmt
    | if_else
if_else: IF LPAREN exp RPAREN ELSE body
for_stmt: FOR LPAREN stmts SEMICOLON exp SEMICOLON stmts RPAREN body
assign_stmt: name ASSIGN exp


%%

