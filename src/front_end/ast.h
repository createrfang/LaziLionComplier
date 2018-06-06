#include <string>

struct AstClass;
struct AstVar;
struct AstExp;
struct AstStmt; 
struct AstStmts;
struct AstFor;
struct AstIfElse;
struct AstAssign;

struct AstVar: struct AstClass{
    std::string name;
    AstVar(std::string s): name(s) {}
};

struct AstStmts: struct AstClass{
}
struct AstStmt: struct AstClass{
    AstClass *son;
}

struct AstIfElse{
    AstExp * condition;
    AstStmt * trueStmt;
    AstStmt * falseStmt;
}

struct AstStmt{

}

