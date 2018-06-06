#include <string>
#include "yacc/parser.tab.hh"

struct AstClass;
struct AstFuncDef;
struct AstStmtList;
struct AstStmt;
struct AstCompoundStmt;
struct AstIfElse;
struct AstForStmt;
struct AstAssignStmt;
struct AstVarDef;
struct AstName;
struct AstExp;
struct AstUnaExp;
struct AstBinExp;
struct AstExpElement;
struct AstNum;

enum AstClassType{
    ctFuncDef,
    ctStmtList,
    ctStmt,
    ctCompoundStmt,
    ctIfElse,
    ctForStmt,
    ctAssignStmt,
    ctVarDef,
    ctName,
    ctExp,
    ctUnaExp,
    ctBinExp,
    ctExpElement,
    ctNum
};

struct AstClass{
    AstClassType type;
    AstClass(AstClassType a): type(a){}
};

struct AstFuncDef: public AstClass{
    yytokentype dataType;
    AstClass *name;
    AstClass *compoundStmt;
    AstFuncDef(yytokentype a1, AstClass *a2, AstClass *a3): dataType(a1), name(a2), compoundStmt(a3), AstClass(ctFuncDef){}
};

struct AstStmtList: public AstClass{
    AstClass *stmtList;
    AstClass *stmt;
    AstStmtList(AstClass *a1, AstClass *a2=NULL): stmtList(a2), stmt(a1), AstClass(ctStmtList){}
};

struct AstIfElse: public AstClass{
    AstClass *cond;
    AstClass *trueStmt;
    AstClass *falseStmt;
    AstIfElse(AstClass *a1, AstClass *a2, AstClass *a3=NULL): cond(a1), trueStmt(a2), falseStmt(a3), AstClass(ctIfElse) {}
};

struct AstForStmt: public AstClass{
    AstClass *initStmt;
    AstClass *exitCond;
    AstClass *nextStmt;
    AstClass *iter;
    AstForStmt(AstClass *a1, AstClass*a2, AstClass *a3, AstClass *a4) : initStmt(a1), exitCond(a2), nextStmt(a3), iter(a4), AstClass(ctForStmt){}
};

struct AstAssignStmt: public AstClass{
    AstClass *lhs;
    AstClass *rhs;
    AstAssignStmt(AstClass *a1, AstClass *a2): lhs(a1), rhs(a2), AstClass(ctAssignStmt){}
};

struct AstVarDef: public AstClass{
    AstClass *dataType;
    AstClass *name;
    AstVarDef(AstClass*a1, AstClass *a2): dataType(a1), name(a2), AstClass(ctVarDef){}
};

struct AstName: public AstClass{
    std::string name;
    AstName(std::string s): name(s), AstClass(ctName){}
};

struct AstExp: public AstClass{
    AstClass *exp;
    AstExp(AstClass *a): exp(a), AstClass(ctExp){}
};

struct AstUnaExp: public AstClass{
    AstClass *exp;
    AstUnaExp(AstClass *a): exp(a), AstClass(ctUnaExp) {}
};

struct AstBinExp: public AstClass{
    AstClass *lfac;
    yytokentype op;
    AstClass *rfac;
    AstBinExp(AstClass *a1, yytokentype a2, AstClass *a3): lfac(a1), op(a2), rfac(a3), AstClass(ctBinExp){}
};

struct AstExpElement: public AstClass{
    AstClass *ele;
    AstExpElement(AstClass *a): ele(a), AstClass(ctExpElement){}
};

struct AstNum: public AstClass{
    int num;
    AstNum(int a): num(a), AstClass(ctNum){}
};
