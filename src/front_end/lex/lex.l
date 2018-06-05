%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

digit		[0-9]
letter		[a-zA-Z]
numi        [1-9]+[0-9]*|0
numf 		{numi}\.[0-9]+

num			{numi}|{numf}
string		\"({letter}|{digit}|[ ])*\"
character	\'.\'
name		{letter}([0-9]|{letter}|_)*

blank 		[\t\n\x0B\f\r\x20]+
comment 	\/\*(.*\n)*.*\*\/
note 		\/\/.*


%%
 /* TYPE DEFINATION */
char       		{return CHAR;}
double 			{return DOUBLE;}
enum			{return ENUM;}
float			{return FLOAT;}
int				{return INT;}
long			{return LONG;}
short			{return SHORT;}
struct			{return STRUCT;}
union			{return UNION;}
unsigned		{return UNSIGNED;}
void 			{return VOID;}

 /* CONTROL KEYS */
for 			{return FOR;}
do 				{return DO;}
while			{return WHILE;}
if				{return IF;}
else			{return ELSE;}
break			{return BREAK;}
continue		{return CONTINUE;}
goto			{return GOTO;}
switch			{return SWITCH;}
case 			{return CASE;}
default			{return DEFAULT;}
return 			{return RETURN;}

 /* SCORE KEYS */
auto 			{return AUTO;}
extern 			{return EXTERN;}
register		{return REGISTER;}
static			{return STATIC;}

 /* other */
const 			{return CONST;}
sizeof			{return SIZEOF;}
typedef			{return TYPEDEF;}
volatile		{return VOLATILE;}

 /* BASIC TYPE */
{num}			{return NUM;}
{string}		{return STRING;}
{character}		{return CHARACTER;}
{name}			{return NAME;}

 /* Arithmetic Operators */
[=]				{return ASSIGN;}
[*]				{return MUL;}
[/]				{return DIV;}
[+]				{return PLUS;}
[-]				{return MINUS;}
[%]				{return MODULO;}
[+][+]			{return INC;}
[-][-]			{return DEC;}

 /* Comparison Operators */
[=][=]			{return EQ;}
[!][=]			{return NEQ;}
[>]				{return GT;}
[<]				{return LT;}
[>][=]			{return GE;}
[<][=]			{return LE;}

 /* Logical Operators */
[!]				{return LNOT;}
[&][&]			{return LAND;}
[|][|]			{return LOR;}

 /* Bitwise Operators */
[~]				{return NOT;}
[&]				{return AND;}
[|]				{return OR;}

[<][<]			{return LSHFT;}
[>][>]			{return RSHFT;}

 /* Compount Operators */
[+][=]			{return ADDASSIGN;}
[-][=]			{return SUBASSIGN;}
[*][=]			{return MULASSIGN;}
[/][=]			{return DIVASSIGN;}
[%][=]			{return MODASSIGN;}
[&][=]			{return ANDASSIGN;}
[|][|][=]		{return ORASSIGN;}
[^][=]			{return XORASSIGN;}
[<][<][=]		{return LSHASSIGN;}
[>][>][=]		{return RSHASSIGN;}

 /* Member and pointer */
[-][>]			{return DEREF;}

{blank}			{/* do nothing */}
{comment}		{/* do nothing */}
{note}			{/* do nothing */}

.				{ 
					printf("Error character %s at line %d, yytext, yylineo); 
					return 0;
				}


%%
int yywarp(){
	return 1;
}
