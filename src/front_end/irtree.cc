#include "irtree.h"

Ir *IrTrue = new IrConst(1);
Ir *IrFalse = new IrConst(0);
Ir *IrZero = IrFalse;

extern std::string newLabel() {
    static int labelCount = 0;
    return "label" + std::to_string(++labelCount);
}