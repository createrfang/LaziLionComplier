#include "ast.h"

////////////////////////////////////////
// Methods that show ast tree
AstClass *root;

void AstFuncDef::display(int offset) {
    printFormat(offset);
    printf("FuncDef\n");
    printFormat(offset);
    printf("DataType: %d\n", (int) dataType);

    offset += formatSpaceStep;
    displayNode(name, offset)
    displayNode(body, offset);
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
    offset += formatSpaceStep;
    displayNode(testCond, offset);
    displayNode(iter, offset);
}

////////////////////////////////////////
// Methods that translate Ast to Ir

Ir *AstFuncDef::translateToIr() {
    // TODO: add function scope
    return body->translateToIr();
}

Ir *AstStmtList::translateToIr() {
    if (stmtList) {
        return new IrSeq(stmtList->translateToIr(),
                         stmt->translateToIr());
    }
    return stmt->translateToIr();
}

Ir *AstIfElse::translateToIr() {
    Ir *trueLabel = new IrLabel(newLabel());
    Ir *falseLabel = new IrLabel(newLabel());
    Ir *trueTree = new IrSeq(trueLabel, trueStmt->translateToIr());
    Ir *falseTree = new IrSeq(falseLabel, falseStmt->translateToIr());
    Ir *irCond = cond->translateToIr();
    // TODO: use shortcut introduced in the book
    return new IrSeq(
            new IrCjump(NEQ, irCond, IrZero, trueLabel, falseLabel),
            new IrSeq(trueTree, falseTree)
    );
}

Ir *AstForStmt::translateToIr() {
    // TODO: fix `for` parse
    return NULL;
}

Ir *AstAssignStmt::translateToIr() {
    Ir *l = lhs->translateToIr();
    if (l->type == IrMem) {
        Ir *tmp = newIrTemp();
        return IrMove(tmp, rhs->translateToIr());
    }
    if (l->type == IrTemp) {
        return
    }
    // TODO: handle error
    printf("Value cannot be on left side\n");
    return IrEseq(NULL, CONST(0));
}

Ir *AstVarDef::translateToIr() {
    // TODO: add var in table
    return NULL;
}

Ir *AstName::translateToIr() {
    // TODO: check name in table
    return new IrTemp(name);
}

Ir *AstExp::translateToIr() {
    return exp->translateToIr();
}

Ir *AstUnaExp::translateToIr() {
    return exp->translateToIr();
}

Ir *AstBinExp::translateToIr() {
    return IrBinOp(op, lfac->translateToIr(), rfac->translateToIr());
}

Ir *AstExpElement::translateToIr() {
    return ele->translateToIr();
}

Ir *AstNum::translateToIr() {
    return IrConst(num);
}

Ir *AstWhileStmt::translateToIr() {
    return NULL;
}
