%{
#include <string.h>
#include <string>
#include "../ast.h"
int yylex();
void yyerror(char *s);

%}

%union{
    yytokentype token;
    int intVal;
    char *stringVal;
    struct AstClass *node;
};

%token <token> LCURLYBRACKET RCURLYBRACKET LPAREN RPAREN SEMICOLON
%token <token> CHAR DOUBLE ENUM FLOAT INT LONG SHORT STRUCT UNION UNSIGNED VOID
%token <token> FOR DO WHILE IF ELSE BREAK CONTINUE GOTO SWITCH CASE DEFAULT RETURN
%token <token> AUTO EXTERN REGISTER STATIC
%token <token> CONST SIZEOF TYPEDEF VOLATILE
%token <intVal> NUM CHARACTER
%token <stringVal> STRING NAME
%token <token> ASSIGN MUL DIV PLUS MINUS MODULO INC DEC
%token <token> EQ NEQ GT LT GE LE
%token <token> LNOT LAND LOR
%token <token> NOT AND OR XOR LSHFT RSHFT
%token <token> ADDASSIGN SUBASSIGN MULASSIGN DIVASSIGN MODASSIGN ANDASSIGN ORASSIGN XORASSIGN LSHASSIGN RSHASSIGN
%token <token> DEREF

%type <node> function_def stmt_list stmt compound_stmt if_else
%type <node> for_stmt assign_stmt var_def name exp
%type <node> logical_or_exp logical_and_exp relation_exp
%type <node> add_exp mul_exp exp_element num
%type <token> relation_op add_op mul_op data_type

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
compound_stmt: '{' stmt_list '}' { $$ = $2; }
if_else: IF LPAREN exp RPAREN stmt { $$ = new AstIfElse($3, $5); }
       | IF LPAREN exp RPAREN stmt ELSE stmt { $$ = new AstIfElse($3, $5, $7); }
for_stmt: FOR LPAREN stmt SEMICOLON exp SEMICOLON stmt RPAREN stmt { $$ = new AstForStmt($3, $5, $7, $9); }
assign_stmt: name ASSIGN exp { $$ = new AstAssignStmt($1, $3); }
var_def: data_type name { $$ = new AstVarDef($1, $2); }
data_type: INT { $$ = INT; }
         | LONG { $$ = LONG; }
         | FLOAT { $$ = FLOAT; }
name: NAME { $$ = new AstName($1); }
exp: logical_or_exp { $$ = new AstExp($1); }
logical_or_exp: logical_and_exp { $$ = new AstUnaExp($1); }
              | logical_or_exp LOR logical_and_exp { $$ = new AstBinExp($3, LOR, $1); }
logical_and_exp: relation_exp { $$ = new AstUnaExp($1); }
               | relation_exp LAND relation_exp { $$ = new AstBinExp($3, LAND, $1); }
relation_exp: add_exp { $$ = new AstUnaExp($1); } 
            | add_exp relation_op add_exp { $$ = new AstBinExp($1, $2, $3); }
relation_op: EQ { $$ = EQ; }
           | NEQ { $$ = NEQ; }
           | GT { $$ = GT; }
           | LT { $$ = LT; }
           | GE { $$ = GE; }
           | LE { $$ = LE; }
add_exp: mul_exp { $$ = new AstUnaExp($1); }
       | mul_exp add_op mul_exp { $$ = new AstBinExp($1, $2, $3); }
add_op: PLUS { $$ = PLUS; }
      | MINUS { $$ = MINUS; }
mul_exp: exp_element { $$ = new AstUnaExp($1); }
       | exp_element mul_op exp_element { $$ = new AstBinExp($1, $2, $3); }
mul_op: MUL { $$ = MUL; }
      | DIV { $$ = DIV; }
      | MODULO { $$ = MODULO; }
exp_element: num { $$ = new AstExpElement($1); }
           | name { $$ = new AstExpElement($1); }
           | LPAREN exp RPAREN { $$ = new AstExpElement($2); }
num: NUM { $$ = new AstNum($1); }
%%

void yyerror(const char *s){
    
}
int yylex(){
    return 0;
}
