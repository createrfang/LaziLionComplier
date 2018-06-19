#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

/* used in hash PJW algorithm */
#define CHAR_BIT        8
#define BITS_IN_int     ( sizeof(int) * CHAR_BIT )  
#define THREE_QUARTERS  ((int) ((BITS_IN_int * 3) / 4))  
#define ONE_EIGHTH      ((int) (BITS_IN_int / 8))  
#define HIGH_BITS       ( ~((unsigned int)(~0) >> ONE_EIGHTH ))  

typedef struct namepool{
    char names[1024];
    int curPosition; 
}NamePool;

extern NamePool namepool;

/* define the kind classes */
typedef enum typeclass{
    S_INT, S_FLOAT, S_STRUCT, S_FUNC
}TypeClass;

/* define the symbol type */
typedef struct type Type;

/** 
 * define the symbol filed
 * designed as a link list, pars || struct members
 */
typedef struct fieldList{
    int posPool;
    Type* fieldType;
    struct fieldList* next;
}FieldList;

/* define the function symbol table */
typedef struct funcion{
    Type * resType;
    int parsN;
    FieldList* pars;
}Function;

/* type of symbol */
struct type{
    TypeClass kind;
    FieldList *structure; 
    Function *function;
};

typedef struct symbol{
    int posPool;
    int line;
    int level;
    Type* type;
    struct symbol* next;
}*Symbol;

extern Symbol symTable[16383];
/**
 * hash function using PJW algorithm to get the result
 */
unsigned int hashPJW(const char* name);

/**
 * new a symbol according to the name;
 */
Symbol generateSymbol(const char* name, int level, int line);

/**
 * find a symbol according to name
 * in the namepool
 */
Symbol findSymbol(const char* name, Function* curFunc);

/**
 * find the certain name in a field list
 */
Type* findFieldType(const char* name, FieldList* f);