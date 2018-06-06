%{
#include "../ast.h"
int yylex();
void yyerror(char *s);
%}

%token LCURLYBRACKET RCURLYBRACKET LPAREN RPAREN SEMICOLON
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
function_def: data_type name LPAREN RPAREN compound_stmt { $$ = new AstFuncDef($1, $2, $5); }
stmt_list: stmt SEMICOLON { $$ = new AstStmtList($1); }
         | stmt_list SEMICOLON stmt SEMICOLON{ $$ = new AstStmtList($3, $1); }
stmt: assign_stmt { $$ = $1; }
    | for_stmt { $$ = $1; }
    | if_else { $$ = $1; }
    | var_def { $$ = $1; }
    | compound_stmt { $$ = $1; }
    | {$$ = NULL; }
compound_stmt: '{' stmt_list '}' { $$ = new AstCompoundStmt($2); }
if_else: IF LPAREN exp RPAREN stmt { $$ = new AstIfElse($3, $5); }
       | IF LPAREN exp RPAREN stmt ELSE stmt { $$ = new AstIfElse($3, $5, $7); }
for_stmt: FOR LPAREN stmt SEMICOLON exp SEMICOLON stmt RPAREN stmt { $$ = AstForStmt($3, $5, $7, $9); }
assign_stmt: name ASSIGN exp { $$ = AstAssignStmt($1, $3); }
var_def: data_type name { $$ = AstVarDef($1, $2); }
data_type: INT { $$ = $1; }
         | LONG { $$ = $1; }
         | FLOAT { $$ = $1; }
name: NAME { $$ = $1; }
exp: logical_or_exp { $$ = $1; }
logical_or_exp: logical_and_exp { $$ = new AstLogicalOrExp($1); }
              | logical_or_exp LOR logical_and_exp { $$ = new AstLogicalOrExp($3, $1); }
logical_and_exp: relation_exp { $$ = new AstLogicalAndExp($1); }
               | relation_exp LAND relation_exp { $$ = new AstLogicalAndExp($3, $1); }
relation_exp: add_exp 
            | add_exp relation_op add_exp
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

void yyerror(char *s){

}
int yylex(){

}
