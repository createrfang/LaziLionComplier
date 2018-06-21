#include "ast.h"

AstClass *root;

void AstFuncDef::display(int offset) {
    printFormat(offset);
    printf("FuncDef\n");
    printFormat(offset);
    printf("DataType: %d\n", (int) dataType);

    offset += formatSpaceStep;
    displayNode(name, offset)
    displayNode(compoundStmt, offset);
}

void AstStmtList::display(int offset) {
    printFormat(offset);
    printf("StmtList\n");

    offset += formatSpaceStep;
    displayNode(stmtList, offset)
    displayNode(stmt, offset);
}

void AstIfElse::display(int offset) {
    printFormat(offset);
    printf("IfElse\n");

    offset += formatSpaceStep;
    displayNode(cond, offset);
    displayNode(trueStmt, offset);
    displayNode(falseStmt, offset);
}

void AstForStmt::display(int offset) {
    printFormat(offset);
    printf("For\n");

    offset += formatSpaceStep;
    displayNode(initStmt, offset);
    displayNode(exitCond, offset);
    displayNode(nextStmt, offset);
    displayNode(iter, offset);
}

void AstAssignStmt::display(int offset) {
    printFormat(offset);
    printf("Assign\n");

    offset += formatSpaceStep;
    displayNode(lhs, offset);
    displayNode(rhs, offset);
}

void AstVarDef::display(int offset) {
    printFormat(offset);
    printf("VarDef\n");
    printFormat(offset);
    printf("dataType: %d\n", (int) dataType);

    offset += formatSpaceStep;
    displayNode(name, offset);
}

void AstName::display(int offset) {
    printFormat(offset);
    printf("Name: %s\n", name.c_str());
}

void AstExp::display(int offset) {
    printFormat(offset);
    printf("Exp\n");

    offset += formatSpaceStep;
    displayNode(exp, offset);
}

void AstUnaExp::display(int offset) {
    printFormat(offset);
    printf("UnaryExp\n");

    offset += formatSpaceStep;
    displayNode(exp, offset);
}

void AstBinExp::display(int offset) {
    printFormat(offset);
    printf("BinaryExp\n");
    printFormat(offset);
    printf("Operator: %d\n", (int) op);

    offset += formatSpaceStep;
    displayNode(lfac, offset);
    displayNode(rfac, offset);
}

void AstExpElement::display(int offset) {
    printFormat(offset);
    printf("ExpElement\n");

    offset += formatSpaceStep;
    displayNode(ele, offset);
}

void AstNum::display(int offset) {
    printFormat(offset);
    printf("Num: %d\n", num);
}

void AstWhileStmt::display(int offset) {
    printFormat(offset);
    printf("While\n");
    offset+=formatSpaceStep;
    displayNode(testCond, offset);
    displayNode(iter, offset);
}