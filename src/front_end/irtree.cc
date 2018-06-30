#include "irtree.h"

Ir *IrTrue = new IrConst(1);
Ir *IrFalse = new IrConst(0);
Ir *IrZero = IrFalse;

std::string newLabel() {
    static int labelCount = 0;
    return "label" + std::to_string(++labelCount);
}

////////////////////////////////////////
// Methods that show a ir tree

void IrConst::display() {
    print("Const: " + std::to_string(value));
}

void IrName::display() {
    print("Name: " + name);
}

void IrTemp::display() {
    print("Temp: " + name);
}

void IrBinOp::display() {
    print("BinOp: " + tokenMap[op]);
    printSon(left);
    printLastSon(right);
}

void IrMem::display() {
    // TODO: support array type
    print("Mem[" + std::to_string(address) + "]");
}

void IrCall::display() {
    print("Call function:"+functionName);
    printLastSon(argList);
}

void IrEseq::display() {
    print("Eseq");
    printSon(stmt);
    printLastSon(exp);
}

void IrMove::display() {
    print("Move");
    printSon(lhs);
    printLastSon(rhs);
}

void IrExp::display() {
    print("Exp");
    printLastSon(exp);
}

void IrJump::display() {
    print("Jump");
    printSon(exp);
    printLastSon(label);
}

void IrCjump::display() {
    print("Cjump, Operator: " + tokenMap[op]);
    printSon(exp1);
    printSon(exp2);
    printSon(trueLabel);
    printLastSon(falseLabel);
}

void IrSeq::display() {
    print("Seq");
    printSon(s1);
    printLastSon(s2);
}

void IrLabel::display() {
    print("Label: " + label);
}

