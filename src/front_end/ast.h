#include <string>

struct AstVar;
struct AstExp;
struct AstStmt; 
struct AstFor;
struct AstIfElse;
struct AstAssign;

struct AstVar{
    std::string name;
    AstVar(std::string s): name(s) {}
};

struct AstStmt{
    void *son;
}

struct AstIfElse{
    AstExp * condition;
    AstStmt * trueStmt;
    AstStmt * falseStmt;
}

struct AstStmt{
}

