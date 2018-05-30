%{
#include "stdio.h"
#include "string.h"
int wcount = 0;
int ccount = 0;
int lcount = 0;
%}
integer [0-9]+
numeric [0-9]*\.[0-9]+
identifier [a-zA-Z][a-zA-Z0-9]*
line    [\n]   
%%
{line}                 {lcount++;ccount+=1;}
{integer}              {wcount++;ccount+=strlen(yytext);}
{numeric}              {wcount++;ccount+=strlen(yytext);}
{identifier}           {wcount++;ccount+=strlen(yytext);}
[\+\-\*\/\%]           {ccount++;}
.                      {ccount++;}
%%

int main()
{
    yylex(); /* start the analysis*/
    printf(" Num of words:%d\n", wcount);
    printf(" Num of lines:%d\n", lcount);
    printf(" Num of chars:%d\n", ccount);
    return 0;
}
int yywrap()
{
    return 1;
}
