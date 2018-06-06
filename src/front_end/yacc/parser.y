%{
#include "../ast.h"
#include "../lex/token.h"
int yylex();
void yyerror(char *s);
%}

%token CHAR DOUBLE ENUM FLOAT INT LONG SHORT STRUCT UNION UNSIGNED VOID
%token FOR DO WHILE IF ELSE BREAK CONTINUE GOTO SWITCH CASE DEFAULT RETURN
%token AUTO EXTERN REGISTER STATIC
%token CONST SIZEOF TYPEDEF VOLATILE
%token NUM STRING CHARACTER NAME
%token ASSIGN MUL DIV PLUS MINUS MODULO INC DEC
%token EQ NEQ GT LT GE LE
%token LNOT LAND LOR
%token NOT AND OR XOR LSHFT RSHFT
%token ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN ANDASSIGN ORASSIGN XORASSIGN LSHASSIGN RSHASSIGN
%token DEREF

%%
function_def: data_type name LPAREN RPAREN fun_body
fun_body: LCURLYBRACKET stmts RCURLYBRACKET
body: fun_body
    | stmt
stmts: 
    | stmt SEMICOLON stmts
stmt: assign_stmt
    | for_stmt
    | if_else
    | var_def
if_else: IF LPAREN exp RPAREN body
       | IF LPAREN exp RPAREN body ELSE body
for_stmt: FOR LPAREN stmts SEMICOLON exp SEMICOLON stmts RPAREN body
assign_stmt: name ASSIGN exp
var_def: data_type name
data_type: INT
         | LONG
         | FLOAT
name: NAME
exp: logical_or_exp
logical_or_exp: logical_and_exp
              | logical_or_exp LOR logical_and_exp
logical_and_exp: relation_exp
               | relation_exp LAND relation_exp
relation_exp: add_exp 
            | add_exp ralation_op add_exp
relation_op: EQ
           | NEQ
           | GT
           | LT
           | GE
           | LE
add_exp: mul_exp
       | mul_exp add_op mul_exp
add_op: PLUS
      | MINUS
mul_exp: exp_element
       | exp_element mul_op exp_element
mul_op: MUL
      | DIV
      | MODULO
exp_element: NUM
           | NAME
           | LPAREN exp RPAREN

%%

