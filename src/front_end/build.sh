#!/bin/sh
cd yacc && bison -d parser.yy && g++ -c parser.tab.cc
cd ../lex && flex++ lex.l && g++ -c lex.yy.cc
cd ..
g++ lex/lex.yy.o yacc/parser.tab.o -o front_end.out
