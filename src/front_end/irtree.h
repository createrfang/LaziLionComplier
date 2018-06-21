#ifndef LAZILIONCOMPLIER_IRTREE_H
#define LAZILIONCOMPLIER_IRTREE_H

#include <string>

#include "format.h"
#include "yacc/parser.tab.hh"

enum IrType {
    irConst,
    irName,
    irTemp,
    irBinOp,
    irMem,
    irCall,
    irEseq,
    irMove,
    irExp,
    irJump,
    irCjump,
    irSeq,
    irLabel,
};

struct Ir : TreePrinter {
    IrType type;

    Ir(IrType t) : type(t) {}
};

struct IrConst : public Ir {
    int value;

    IrConst(int value) : Ir(irConst), value(value) {}

    void display();
};

struct IrName : public Ir {
    std::string name;

    IrName(std::string name) : Ir(irName), name(name) {}

    void display();
};

struct IrTemp : public Ir {
    std::string name;

    IrTemp(std::string name) : Ir(irTemp), name(name) {}

    void display();
};

struct IrBinOp : public Ir {
    yytokentype op;
    Ir *left;
    Ir *right;

    IrBinOp(yytokentype op, Ir *left, Ir *right) : Ir(irBinOp), op(op), left(left), right(right) {}

    void display();
};

struct IrMem : public Ir {
    int address;

    IrMem(int a) : Ir(irMem), address(a) {}

    void display();
};

struct IrCall : public Ir {
    Ir *function;
    Ir *argList;

    IrCall(Ir *function, Ir *argList) : Ir(irCall), function(function), argList(argList) {}

    void display();
};

struct IrEseq : public Ir {
    Ir *stmt;
    Ir *exp;

    IrEseq(Ir *stmt, Ir *exp) : Ir(irEseq), stmt(stmt), exp(exp) {}

    void display();
};

struct IrMove : public Ir {
    Ir *lhs;
    Ir *rhs;

    // lhs should be temp or mem(e) only.
    // Like many other type constraints, this is check in semantic analysis but no checks in definition here.
    IrMove(Ir *lhs, Ir *rhs) : Ir(irMove), lhs(lhs), rhs(rhs) {}

    void display();
};

struct IrExp : public Ir {
    Ir *exp;

    IrExp(Ir *exp) : Ir(irExp), exp(exp) {}

    void display();
};

struct IrJump : public Ir {
    Ir *exp;
    Ir *label;

    IrJump(Ir *exp, Ir *label) : Ir(irJump), exp(exp), label(label) {}

    void display();
};

struct IrCjump : public Ir {
    yytokentype op; // relation operator
    Ir *exp1;
    Ir *exp2;
    Ir *trueLabel;
    Ir *falseLabel;

    IrCjump(yytokentype op, Ir *exp1, Ir *exp2, Ir *trueLabel, Ir *falseLabel) : Ir(irCjump), op(op), exp1(exp1),
                                                                                 exp2(exp2), trueLabel(trueLabel),
                                                                                 falseLabel(falseLabel) {}

    void display();
};

struct IrSeq : public Ir {
    Ir *s1;
    Ir *s2;

    IrSeq(Ir *s1, Ir *s2) : Ir(irSeq), s1(s1), s2(s2) {}

    void display();
};

struct IrLabel : public Ir {
    std::string label;

    IrLabel(std::string label) : Ir(irLabel), label(label) {}
    void display();
};

extern Ir *IrTrue;
extern Ir *IrFalse;
extern Ir *IrZero;

extern std::string newLabel();

#endif //LAZILIONCOMPLIER_IRTREE_H
