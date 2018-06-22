#include "environment.h"

std::map<std::string, Symbol *> Environment::env;
std::vector<AstClass *> Environment::scopeStack;

void Environment::addSymbol(Symbol *s) {
    auto it = env.find(s->name);
    s->scope = getTopScope();
    if (it != env.end()) s->externValue = it->second;
    env[s->name] = s;
}

const Symbol *Environment::getSymbol(std::string s) {
    auto it = env.find(s);
    return it == env.end() ? NULL : it->second;
}

void Environment::deleteScope(AstClass *scope) {
    if (scopeStack.size() <= 0 && scope != scopeStack[scopeStack.size() - 1]) {
        // TODO: Error Handling
        printf("Error: Cannot Delete Scope\n");
    } else {
        scopeStack.pop_back();
    }
    for (auto it = env.begin(); it != env.end(); ++it) {
        if (it->second->scope == scope) {
            it->second = it->second->externValue;
        }
    }
}

void Environment::printEnv() {
    for (auto it = env.begin(); it != env.end(); ++it) {
        it->second->print();
    }
}

void Environment::newScope(AstClass *scope) {
    scopeStack.push_back(scope);
}

void Environment::clear() {
    scopeStack.clear();
    env.clear();
}

AstClass *Environment::getTopScope() {
    return scopeStack.size() > 0 ? scopeStack[scopeStack.size() - 1] : NULL;
}