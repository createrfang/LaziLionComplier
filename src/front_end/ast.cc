#include "ast.h"

////////////////////////////////////////
// Methods that show ast tree
AstClass *astRoot;

void AstFuncDef::display() {
    print("FuncDef returnType:" + tokenMap[dataType] + " name: " + (name ? name->name : "NULL"));
    printSon(varDefList);
    printLastSon(body);
}

void AstStmtList::display() {
    print("StmtList");
    printSon(stmtList);
    printLastSon(stmt);
}

void AstIfElse::display() {
    print("IfElse");
    printSon(cond);
    printSon(trueStmt);
    printLastSon(falseStmt);
}

void AstForStmt::display() {
    print("For");
    printSon(initStmt);
    printSon(exitCond);
    printSon(nextStmt);
    printLastSon(iter);
}

void AstAssignStmt::display() {
    print("Assign");
    printSon(lhs);
    printLastSon(rhs);
}

void AstVarDef::display() {
    print("VarDef: dataType:" + tokenMap[dataType] + " name: " + (name ? name->name : "NULL"));
}

void AstName::display() {
    print("Name:" + name);
}

void AstExp::display() {
    print("Exp");
    printLastSon(exp);
}

void AstUnaExp::display() {
    print("UnaryExp");
    printLastSon(exp);
}

void AstBinExp::display() {
    print("BinaryExp Operator:" + tokenMap[op]);
    printSon(lfac);
    printLastSon(rfac);
}

void AstExpElement::display() {
    print("ExpElement");
    printLastSon(ele);
}

void AstNum::display() {
    print("Num:" + std::to_string(num));
}

void AstWhileStmt::display() {
    print("While");
    printSon(testCond);
    printLastSon(iter);
}

void AstCompoundStmt::display() {
    print("CompoundStmt");
    printLastSon(stmtList);
}

void AstFuncList::display() {
    print("FuncList");
    printSon(funcList);
    printLastSon(funcDef);
}

void AstVarDefList::display() {
    print("VarDefList");
    printSon(list);
    printLastSon(varDef);
}

void AstExpList::display() {
    print("ExpList");
    printSon(list);
    printLastSon(exp);
}

void AstFunctionCall::display() {
    print("FunctionCall, Name:" + name->name);
    printLastSon(expList);
}

////////////////////////////////////////
// Methods that translate Ast to Ir

Ir *AstFuncDef::translateToIr() {
    // TODO: add function check
    Environment::newScope(this);
    // add arguments to table only
    if (varDefList) varDefList->translateToIr();

    Ir *funcLabel = new IrLabel("function-" + newLabel());
    Ir *funcBody = body ? body->translateToIr() : NULL;
    Environment::deleteScope(this);
    return new IrSeq(funcLabel, funcBody);
}

Ir *AstStmtList::translateToIr() {
    Ir *s1 = NULL, *s2 = NULL;
    if (stmtList) s1 = stmtList->translateToIr();
    if (stmt) s2 = stmt->translateToIr();
    if (s1 && s2) {
        return new IrSeq(s1, s2);
    }
    if (!s1) s1 = s2;
    return s1 ? s1 : NULL;
}

Ir *AstIfElse::translateToIr() {
    Ir *trueLabel = new IrLabel(newLabel());
    Ir *falseLabel = new IrLabel(newLabel());
    Ir *trueTree = trueStmt
                   ? new IrSeq(trueLabel, trueStmt->translateToIr())
                   : trueLabel;
    Ir *falseTree = falseStmt
                    ? new IrSeq(falseLabel, falseStmt->translateToIr())
                    : falseLabel;
    Ir *irCond = cond->translateToIr();
    // Actually, trueTree and falseTree must be non-null.
    // Below is just for safe.
    if (!trueTree && !falseTree) {
        // if (cond) do nothing else do nothing
        // do cond only
        // Actually, here is unreachable.
        return irCond;
    }
    yytokentype op = trueTree ? NEQ : EQ;
    if (!trueTree) {
        // if (cond) do nothing else false tree
        std::swap(trueTree, falseTree);
    }

    // TODO: use shortcut introduced in the book
    return new IrSeq(
            new IrCjump(op, irCond, IrFalse, trueLabel, falseLabel),
            new IrSeq(falseTree, trueTree)
    );
}

Ir *AstForStmt::translateToIr() {
    // TODO: fix `for` parse
    return NULL;
}

Ir *AstAssignStmt::translateToIr() {
    if (!lhs || !rhs) {
        // TODO: handle error
        printf("Invalid AstAssignStmt\n");
        return new IrEseq(NULL, IrZero);
    }
    Ir *l = lhs->translateToIr();
    Ir *r = rhs->translateToIr();
    if (l->type == irMem) {
        // if lhs is memory, it should be stored
        // to temp and then return the temp
        Ir *tmp = new IrTemp(newLabel());
        return new IrEseq(
                new IrSeq(
                        new IrMove(tmp, r),
                        new IrMove(l, tmp)
                ),
                tmp);
    }
    if (l->type == irTemp) {
        // if lhs is temp, return it directly
        return new IrEseq(new IrMove(l, r), l);
    }
    // TODO: handle error
    printf("Value cannot be on left side\n");
    return new IrEseq(NULL, IrZero);
}

Ir *AstVarDef::translateToIr() {
    // TODO(DONE): add var in table
    Environment::addSymbol(new Symbol(name->name, dataType));
    // TODO: support initialization when defining
    return NULL;
}

Ir *AstName::translateToIr() {
    // TODO(DONE): check name in table
    const Symbol *s = Environment::getSymbol(name);
    // TODO: Error handling
    if (s == NULL) {
        printf("Error: Cannot find variable %s\n", name.c_str());
    }
    return new IrTemp(name);
}

Ir *AstExp::translateToIr() {
    return exp ? exp->translateToIr() : NULL;
}

Ir *AstUnaExp::translateToIr() {
    return exp ? exp->translateToIr() : NULL;
}

Ir *AstBinExp::translateToIr() {
    Ir *l = lfac ? lfac->translateToIr() : NULL;
    Ir *r = rfac ? rfac->translateToIr() : NULL;
    Ir *res = new IrBinOp(op, l, r);
//    if (l && l->type == irTemp && r && r->type == irTemp) {
//        Symbol *ls = Environment::getSymbol(l->name);
//        Symbol *rs = Environment::getSymbol(r->name);
//        if (ls && rs && ls->type != rs->type) {
//            // TODO: Handle Error
//            printf("%s and %s are not the same type\n", l->name.c_str(), r->name.c_str());
//        }
//    }
    return res;
}

Ir *AstExpElement::translateToIr() {
    return ele ? ele->translateToIr() : NULL;
}

Ir *AstNum::translateToIr() {
    return new IrConst(num);
}

Ir *AstWhileStmt::translateToIr() {
    Ir *testLabel = new IrLabel(newLabel());
    Ir *doneLabel = new IrLabel(newLabel());
    return new IrSeq(
            new IrSeq(
                    testLabel,
                    new IrCjump(
                            EQ,
                            testCond->translateToIr(),
                            IrFalse,
                            doneLabel,
                            NULL)
            ),
            iter ? new IrSeq(
                    iter->translateToIr(),
                    doneLabel)
                 : doneLabel
    );
}

Ir *AstCompoundStmt::translateToIr() {
    Ir *res = stmtList ? stmtList->translateToIr() : NULL;
    return res;
}

Ir *AstFuncList::translateToIr() {
    Ir *s1 = funcList ? funcList->translateToIr() : NULL;
    Ir *s2 = funcDef ? funcDef->translateToIr() : NULL;
    if (s1 && s2) {
        return new IrSeq(s1, s2);
    }
    if (!s1) s1 = s2;
    return new IrSeq(s1, s2);
}

Ir *AstVarDefList::translateToIr() {
    if (list) list->translateToIr();
    if (varDef) varDef->translateToIr();
    return NULL;
}

Ir *AstExpList::translateToIr() {
    Ir *e1 = list ? list->translateToIr() : NULL;
    Ir *e2 = exp ? exp->translateToIr() : NULL;
    if (e1 && e2) {
        return new IrEseq(e1, e2);
    }
    if (!e1) {
        e1 = e2;
    }
    return e1 ? new IrExp(e1) : NULL;
}

Ir *AstFunctionCall::translateToIr() {
    return new IrCall(name->name, expList->translateToIr());
}
