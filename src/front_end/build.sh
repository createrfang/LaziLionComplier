#!/bin/sh
BUILD_DIR="../../build/"
cd yacc && bison -d parser.yy && g++ -c parser.tab.cc -o parser.tab.o
# cd ../lex && flex++ lex.l && g++ -c lex.yy.cc
cd ../lex && lex lex.l && g++ -c lex.yy.c -o lex.yy.o && cd ..
g++ -c ast.cc -o ${BUILD_DIR}ast.o
g++ -c visualize.cc -o ${BUILD_DIR}visualize.o
g++ -c irtree.cc -o ${BUILD_DIR}irtree.o
g++ -c format.cc -o ${BUILD_DIR}format.o
g++ -c environment.cc -o ${BUILD_DIR}environment.o
mv lex/lex.yy.o ${BUILD_DIR}lex/lex.yy.o
mv yacc/parser.tab.o ${BUILD_DIR}yacc/parser.tab.o
cd ${BUILD_DIR} && g++ lex/lex.yy.o yacc/parser.tab.o environment.o format.o irtree.o ast.o visualize.o -o visualize.out