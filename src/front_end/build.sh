#!/bin/sh
cd yacc && bison -d parser.yy && g++ -c parser.tab.cc -o parser.tab.o
# cd ../lex && flex++ lex.l && g++ -c lex.yy.cc
cd ../lex && lex lex.l && g++ -c lex.yy.c -o lex.yy.o && cd ..
g++ -c ast.cc -o ast.o
g++ -c visualize.cc -o visualize.o
g++ -c irtree.cc -o irtree.o
g++ lex/lex.yy.o yacc/parser.tab.o irtree.o ast.o visualize.o -o visualize.out
