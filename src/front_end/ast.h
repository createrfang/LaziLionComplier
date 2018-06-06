#include <string>

struct AstClass;
struct AstVar;
struct AstExp;
struct AstStmt;
struct AstStmtList;
struct AstFor;
struct AstIfElse;
struct AstAssign;

struct AstClass{

};
struct AstVar: public AstClass{
    std::string name;
    AstVar(std::string s): name(s) {}
};

struct AstStmt: public AstClass{
    AstClass *son;
};

struct AstIfElse: public AstClass{
    AstExp * condition;
    AstStmt * trueStmt;
    AstStmt * falseStmt;
};

struct AstFor: public AstClass{

};

