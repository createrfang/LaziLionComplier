#!/bin/sh
cd yacc && bison -d parser.yy && gcc -c parser.tab.cc
# cd ../lex && flex++ lex.l && g++ -c lex.yy.cc
cd ../lex && lex lex.l && g++ -c lex.yy.c
cd ..
g++ lex/lex.yy.o yacc/parser.tab.o -o front_end.out
