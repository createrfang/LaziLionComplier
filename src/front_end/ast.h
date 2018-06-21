#ifndef __AST_H__
#define __AST_H__

#include <stdio.h>
#include <string>
#include "yacc/parser.tab.hh"
#include "irtree.h"

const int formatSpaceStep = 3;

#define rep(x) for (int i = 0; i < (x); ++i)
#define printSpace(offset) rep(offset)printf(" ");
#define printFormat(offset) printSpace(offset)printf("|--");
#define displayNode(x, off) if (x) x->display(off); else {printFormat(off); printf("NULL\n");}

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
struct AstBinExp;
struct AstExpElement;
struct AstNum;

enum AstClassType {
    ctFuncDef = 0,
    ctStmtList = 1,
    ctStmt = 2,
    ctCompoundStmt = 3,
    ctIfElse = 4,
    ctForStmt = 5,
    ctAssignStmt = 6,
    ctVarDef = 7,
    ctName = 8,
    ctExp = 9,
    ctUnaExp = 10,
    ctBinExp = 11,
    ctExpElement = 12,
    ctNum = 13,
    ctWhileStmt = 14,
};

struct AstClass {
    AstClassType type;

    AstClass(AstClassType a) : type(a) {
        printCreateInfo();
    }

    void printCreateInfo() {
        printf("Create Node %d\n", (int) type);
    }

    virtual void display(int offset) = 0;

    virtual Ir *translateToIr() = 0;
};

struct AstFuncDef : public AstClass {
    yytokentype dataType;
    AstClass *name;
    AstClass *body;

    AstFuncDef(yytokentype a1, AstClass *a2, AstClass *a3) : dataType(a1), name(a2), body(a3),
                                                             AstClass(ctFuncDef) {}

    void display(int offset);

    Ir *translateToIr();
};

struct AstStmtList : public AstClass {
    AstClass *stmtList;
    AstClass *stmt;

    AstStmtList(AstClass *a1, AstClass *a2 = NULL) : stmtList(a2), stmt(a1), AstClass(ctStmtList) {}

    void display(int offset);

    Ir *translateToIr();
};

struct AstIfElse : public AstClass {
    AstClass *cond;
    AstClass *trueStmt;
    AstClass *falseStmt;

    AstIfElse(AstClass *a1, AstClass *a2, AstClass *a3 = NULL) : cond(a1), trueStmt(a2), falseStmt(a3),
                                                                 AstClass(ctIfElse) {}

    void display(int offset);

    Ir *translateToIr();
};

struct AstForStmt : public AstClass {
    AstClass *initStmt;
    AstClass *exitCond;
    AstClass *nextStmt;
    AstClass *iter;

    AstForStmt(AstClass *a1, AstClass *a2, AstClass *a3, AstClass *a4) : initStmt(a1), exitCond(a2), nextStmt(a3),
                                                                         iter(a4), AstClass(ctForStmt) {}

    void display(int offset);

    Ir *translateToIr();
};

struct AstAssignStmt : public AstClass {
    AstClass *lhs;
    AstClass *rhs;

    AstAssignStmt(AstClass *a1, AstClass *a2) : lhs(a1), rhs(a2), AstClass(ctAssignStmt) {}

    void display(int offset);

    Ir *translateToIr();
};

struct AstVarDef : public AstClass {
    yytokentype dataType;
    AstClass *name;

    AstVarDef(yytokentype a1, AstClass *a2) : dataType(a1), name(a2), AstClass(ctVarDef) {}

    void display(int offset);

    Ir *translateToIr();
};

struct AstName : public AstClass {
    std::string name;

    AstName(std::string s) : name(s), AstClass(ctName) {}

    void display(int offset);

    Ir *translateToIr();
};

struct AstExp : public AstClass {
    AstClass *exp;

    AstExp(AstClass *a) : exp(a), AstClass(ctExp) {}

    void display(int offset);

    Ir *translateToIr();
};

struct AstUnaExp : public AstClass {
    AstClass *exp;

    AstUnaExp(AstClass *a) : exp(a), AstClass(ctUnaExp) {}

    void display(int offset);

    Ir *translateToIr();
};

struct AstBinExp : public AstClass {
    AstClass *lfac;
    yytokentype op;
    AstClass *rfac;

    AstBinExp(AstClass *a1, yytokentype a2, AstClass *a3) : lfac(a1), op(a2), rfac(a3), AstClass(ctBinExp) {}

    void display(int offset);

    Ir *translateToIr();
};

struct AstExpElement : public AstClass {
    AstClass *ele;

    AstExpElement(AstClass *a) : ele(a), AstClass(ctExpElement) {}

    void display(int offset);

    Ir *translateToIr();
};

struct AstNum : public AstClass {
    int num;

    AstNum(int a) : num(a), AstClass(ctNum) {}

    void display(int offset);

    Ir *translateToIr();
};

struct AstWhileStmt : public AstClass {
    AstClass *testCond;
    AstClass *iter;

    AstWhileStmt(AstClass *a1, AstClass *a2) : AstClass(ctWhileStmt), testCond(a1), iter(a2) {}

    void display(int offset);

    Ir *translateToIr();
};

extern AstClass *root;

#endif