#ifndef LAZILIONCOMPLIER_ENVIRONMENT_H
#define LAZILIONCOMPLIER_ENVIRONMENT_H

#include <string>
#include <map>
#include "yacc/parser.tab.hh"
#include "ast.h"

struct Symbol {
    std::string name;
    yytokentype type;
    // Below two should not be constructed manually,
    // but done by Environment automatically.
    AstClass *scope;
    Symbol *externValue;

    Symbol(std::string name, yytokentype type) : name(name), type(type),
                                                 scope(NULL), externValue(NULL) {}

    void print() {
        printf("Symbol %s: type %s, scope %x, extentValue %x\n", name,
               TreePrinter::tokenMap[type], scope, externValue);
    }
};

struct Environment {
    static std::map<std::string, Symbol *> env;
    static std::vector<AstClass *> scopeStack;

    static void addSymbol(Symbol *s);

    static const Symbol *getSymbol(std::string s);

    static AstClass *getTopScope();

    static void newScope(AstClass *scope);

    static void deleteScope(AstClass *scope);

    static void printEnv();

    static void clear();
};

#endif //LAZILIONCOMPLIER_ENVIRONMENT_H
