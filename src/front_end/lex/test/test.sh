#!/bin/sh
lex lex.l
gcc lex.yy.c -ll
./a.out < test
