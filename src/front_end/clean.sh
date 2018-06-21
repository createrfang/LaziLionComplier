#!/bin/sh
find . -type f -name '*.o' -delete
find . -type f -name '*.out' -delete
rm lex/lex.yy.c
rm yacc/parser.tab.cc