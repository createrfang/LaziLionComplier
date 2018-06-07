## Lex Analysis

### Compliation Steps
```
lex lex.l
gcc lex.yy.c -ll
./a.out [filename]
```

### Run Test
```
cd ./test
./test.sh
```

### Test Case
``` C
int main(void)
{
    int i=1;
    while(i<5){
        printf("hello!");
        i++;//this is a note
    }
    /* this is a comment */
    int j=i+10;
}
```

### Analysis Result
```
INT NAME (VOID) { 
    INT NAME ASSIGN NUM;
    WHILE (NAME LT NUM){
        NAME (STRING);
        NAME INC; NOTE
    }
    COMMENT
    INT NAME ASSIGN NAME PLUS NUM;
}
```
