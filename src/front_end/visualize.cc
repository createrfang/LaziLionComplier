#include <stdio.h>
#include "ast.h"
#include "yacc/parser.tab.hh"

int main() {
    if (yyparse()) {
        goto parseFailed;
    }
    if (root) {
        printf("root\n");
        root->display(0);
    } else {
        printf("null\n");
    }

    return 0;

    parseFailed:
    printf("Parse failed.\n");
    return 1;
}