%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"
%}

digit		[0-9]
letter		[a-zA-Z]
numi        [1-9]+[0-9]*|0
numf 		{numi}\.[0-9]+

num			{numi}|{numf}
string		\".*\"
character	\'.\'
name		{letter}([0-9]|{letter}|_)*

blank 		[\t\n\x0B\f\r\x20]+
comment 	\/\*(.*\n)*.*\*\/
note 		\/\/.*


%%
 /* TYPE DEFINATION */
char       		{printf("CHAR ");}
double 			{printf("DOUBLE ");}
enum			{printf("ENUM ");}
float			{printf("FLOAT ");}
int				{printf("INT ");}
long			{printf("LONG ");}
short			{printf("SHORT ");}
struct			{printf("STRUCT ");}
union			{printf("UNION ");}
unsigned		{printf("UNSIGNED ");}
void 			{printf("VOID ");}

 /* CONTROL KEYS */
for 			{printf("FOR ");}
do 				{printf("DO ");}
while			{printf("WHILE ");}
if				{printf("IF ");}
else			{printf("ELSE ");}
break			{printf("BREAK ");}
continue		{printf("CONTINUE ");}
goto			{printf("GOTO ");}
switch			{printf("SWITCH ");}
case 			{printf("CASE ");}
default			{printf("DEFAULT ");}
return 			{printf("RETURN ");}

 /* SCORE KEYS */
auto 			{printf("AUTO ");}
extern 			{printf("EXTERN ");}
register		{printf("REGISTER ");}
static			{printf("STATIC ");}

 /* other */
const 			{printf("CONST ");}
sizeof			{printf("SIZEOF ");}
typedef			{printf("TYPEDEF ");}
volatile		{printf("VOLATILE ");}

 /* BASIC TYPE */
{num}			{printf("NUM ");}
{string}		{printf("STRING ");}
{character}		{printf("CHARACTER ");}
{name}			{printf("NAME ");}

 /* Arithmetic Operators */
[=]				{printf("ASSIGN ");}
[*]				{printf("MUL ");}
[/]				{printf("DIV ");}
[+]				{printf("PLUS ");}
[-]				{printf("MINUS ");}
[%]				{printf("MODULO ");}
[+][+]			{printf("INC ");}
[-][-]			{printf("DEC ");}

 /* Comparison Operators */
[=][=]			{printf("EQ ");}
[!][=]			{printf("NEQ ");}
[>]				{printf("GT ");}
[<]				{printf("LT ");}
[>][=]			{printf("GE ");}
[<][=]			{printf("LE ");}

 /* Logical Operators */
[!]				{printf("LNOT ");}
[&][&]			{printf("LAND");}
[|][|]			{printf("LOR ");}

 /* Bitwise Operators */
[~]				{printf("NOT ");}
[&]				{printf("AND ");}
[|]				{printf("OR ");}
[\^]			{printf("XOR ");}
[<][<]			{printf("LSHFT ");}
[>][>]			{printf("RSHFT ");}

 /* Compount Operators */
[+][=]			{printf("ADDASSIGN ");}
[-][=]			{printf("SUBASSIGN ");}
[*][=]			{printf("MULASSIGN ");}
[/][=]			{printf("DIVASSIGN ");}
[%][=]			{printf("MODASSIGN ");}
[&][=]			{printf("ANDASSIGN ");}
[|][|][=]		{printf("ORASSIGN ");}
[\^][=]			{printf("XORASSIGN ");}
[<][<][=]		{printf("LSHASSIGN ");}
[>][>][=]		{printf("RSHASSIGN ");}

 /* Member and pointer */
[-][>]			{printf("DEREF ");}

{blank}			{printf(" "); /* do nothing */}
{comment}		{printf("COMMENT "); /* do nothing */}
{note}			{printf("NOTE "); /* do nothing */}

.				{ 
					printf("%c", yytext[0]); 
				}

%%
void main(void)
{
	yylex();
	printf("\n");
}

int yywarp(){
	return 1;
}
