# C-like language BNF
```
program --> stmt* | {stmt*}
stmt --> if-else | dowhile | whiledo |for-stmt| assign
if-else --> if (exp)  stmt  else  stmt 
dowhile  --> do  stmt  while ( exp )
whiledo  --> do  stmt  while ( exp )
for-stmt  --> for ( exp, exp, exp )  stmt 
assign --> id=exp
exp --> [ factor ] op  factor | factor op [factor] | factor 
op --> add | sub | mul | div | equ | grt | less | ge | le | ne
factor --> exp | (exp) |  var | number | function
```