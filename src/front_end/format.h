#ifndef LAZILIONCOMPLIER_FORMAT_H
#define LAZILIONCOMPLIER_FORMAT_H

#include <vector>
#include <string>
#include <map>
#include "yacc/parser.tab.hh"

struct TreePrinter {
    static std::vector<char> stack;
    static std::map <yytokentype, std::string> tokenMap;
    static char c;

    void print(std::string s);

    void printSon(TreePrinter *s);

    // must use this if last son
    void printLastSon(TreePrinter *s);

    // if no last son, use this
    void printOver();

    void init();

    // TODO: modify it to virtual
    virtual void display() = 0;

    void display(int offset) {};
};

#endif //LAZILIONCOMPLIER_FORMAT_H
