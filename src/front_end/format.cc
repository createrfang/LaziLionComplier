#include "format.h"

std::map <yytokentype, std::string> TreePrinter::tokenMap;
std::vector<char> TreePrinter::stack;
char TreePrinter::c;

void TreePrinter::print(std::string s) {
//    printf("%d\n", stack.size());
    for (int i = 0; i + 1 < stack.size(); ++i) {
//        printf("i %d %d\n", i, stack.size() - 1);
        printf("%c  ", stack[i]);
    }
    printf("%c--%s\n", c, s.c_str());
}

void TreePrinter::printSon(TreePrinter *s) {
    stack.push_back('|');
    c = '|';
    if (s) {
        s->display();
    } else {
        print("NULL");
    }
    printOver();
}

// must use this if last son
void TreePrinter::printLastSon(TreePrinter *s) {
    stack.push_back(' ');
    c = '+';
    if (s) {
        s->display();
    } else {
        print("NULL");
    }
    printOver();
}

// if no last son, must use this
void TreePrinter::printOver() { stack.pop_back(); }

void TreePrinter::init() {
    stack.clear();
    stack.push_back(' ');
    static int firstCall = 1;
    if (firstCall) {
        tokenMap[INT] = "INT";
        tokenMap[MUL] = "MUL";
        tokenMap[DIV] = "DIV";
        tokenMap[PLUS] = "PLUS";
        tokenMap[MINUS] = "MINUS";
        tokenMap[MODULO] = "MODULO";
        tokenMap[INC] = "INC";
        tokenMap[DEC] = "DEC";
        tokenMap[EQ] = "EQ";
        tokenMap[NEQ] = "NEQ";
        tokenMap[GT] = "GT";
        tokenMap[LT] = "LT";
        tokenMap[GE] = "GE";
        tokenMap[LE] = "LE";
        tokenMap[LNOT] = "LNOT";
        tokenMap[LAND] = "LAND";
        tokenMap[LOR] = "LOR";
        tokenMap[NOT] = "NOT";
        tokenMap[AND] = "AND";
        tokenMap[OR] = "OR";
        tokenMap[XOR] = "XOR";
        tokenMap[LSHFT] = "LSHFT";
        tokenMap[RSHFT] = "RSHFT";
        firstCall = 0;
    }
}