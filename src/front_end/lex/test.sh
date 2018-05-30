rm lex.yy.c sbfront
flex regularize.l
gcc -o sbfront lex.yy.c -ll
./sbfront<../../../test/testcode/cal.c