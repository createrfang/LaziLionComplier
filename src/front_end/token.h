enum {

/* 
 *  punctuations
 */
    APOSTROPHE,     /* ' */
    LCURLYBRACKET,  /* { */
    RCURLYBRACKET,
    LPAREN,
    RPAREN,
    LSQRBRACKET,
    RSQRBRACKET,
    COLON,
    COMMA,
    POINT,          /* . */
    DASH,           /* _ */    
    QUASTION,       /* ? */
    QUOTATION,      /* ' */
    CITATION,       /* " */
    SEMICOLON,      /* ; */
    SLASH,          /* / */

/*
 *  TYPE DEFINATION
 *
 */
    CHAR,
    DOUBLE,
    ENUM,
    FLOAT,
    INT,
    LONG,
    SHORT,
    STRUCT,
    UNION,
    UNSIGNED,
    VOID,

/*
 *  LITERAL TYPE
 */
    NUM,            /* [0-9]*[.][0-9]* */
    STRING,         /* "" */
    CHARACTER,      /* '' */ 

/*
 *  CONTROL KEYS
 *  
 */
    FOR,
    DO,
    WHILE,
    BREAK,
    CONTINUE,
    IF,
    ELSE,
    GOTO,
    SWITCH,
    CASE,
    DEFAULT,
    RETURN,

/* 
 *  SCORE KEYS
 */
    AUTO,
    EXTERN,
    REGISTER,
    STATIC,

/*
 *  OTHER
 */
    CONST,
    SIZEOF,
    TYPEDEF,
    VOLATILE,

/*
 *  Arithmetic Operators
 *  From wiki: Operators in C and C++
 */
    ASSIGN,     /* = */
    MUL,      
    DIV,
    PLUS,       /* + */
    MINUS,      /* - */
    MODULO,
    INC,        /* ++ */
    DEC,        /* -- */

/*
 * Comparison Operators
 */
    EQ,         /* == */
    NEQ,        /* != */
    GT,         /* > */
    LT,         /* < */
    GE,         /* >= */
    LE,         /* <= */

/*
 *  Logical Operators
 */
    LNOT,       /* ! */
    LAND,       /* && */
    LOR,        /* || */

/*
 *  Bitwise Operators
 */
    NOT,       /* ~ */
    AND,       /* & */
    OR,        /* | */
    XOR,        /* ^ */
    LSHFT,      /* << */
    RSHFT,      /* >> */

/*
 *  Compount Operators
 */
    ADDASSIGN,   /* += */
    SUBASSIGN,
    MULASSIGN,
    DIVASSIGN,
    MODASSIGN,
    ANDASSIGN,
    ORASSIGN,
    XORASSIGN,
    LSHASSIGN,  /* <<= */
    RSHASSIGN,  /* >>= */

/*
 * Member and pointer
 * Notice: *=MUL, &=AND, .=POINT
 */
    DEREF,          /* -> */


} token;
