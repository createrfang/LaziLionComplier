#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <assert.h>

/* represent inter code node structure */
typedef struct irnode{
	int argsN;
	char args[6][30];
	struct irnode* pre;
	struct irnode* next;
}IrCode;

/**
 * generate a new label
 * add the label counter;
 */
void generateLabel(char* name);

/**
 * generate a new temp
 * add the temp counter;
 */
void generateTemp(char* name);

/**
 * insert ir code
 */
void insertNode(int argsN, ...);

/**
 * delete a node from ircode link
 */
void deleteNode(IrCode* p);

/**
 * output the inter code
 * print the link list, from irHead
 */
void printIrCode();

/**
 * translate the ast expression
 * ast type:
 *   ctFuncDef,
 *   ctStmtList,
 *   ctStmt,
 *   ctCompoundStmt,
 *   ctIfElse,
 *   ctForStmt,
 *   ctAssignStmt,
 *   ctVarDef,
 *   ctName,
 *   ctExp,
 *   ctUnaExp,
 *   ctBinExp,
 *   ctExpElement,
 *   ctNum
 */
void translateAst(AstClass* ast);

/**
 * translate the exprssion into intercode
 */
void translateExp(AstClass* p, char* place, int option);

/**
 * translate the condition expression into intercode
 */
void translateCond(AstClass* p, char* labelT, char* labelF);

/**
 * get the required memory space
 * return the memory space 
 */
int getMemoerySpace(Type* type);