#include <stdio.h>
#include <map>
#include "ast.h"
#include "yacc/parser.tab.hh"

int main() {
    if (yyparse()) {
        goto parseFailed;
    }
    if (astRoot) {
        printf("ast root\n");
        astRoot->init();
        astRoot->display();
        Ir *irRoot = astRoot->translateToIr();
        if (irRoot) {
            printf("ir root\n");
            irRoot->init();
            irRoot->display();
        } else {
            printf("ir root null\n");
        }
    } else {
        printf("ast root null\n");
    }

    return 0;

    parseFailed:
    printf("Parse failed.\n");
    return 1;
}