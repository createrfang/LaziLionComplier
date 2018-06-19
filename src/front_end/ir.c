#include "ir.h"
#include "ast.h"
#include "symbol.h"

/* label & temp counter */
int label_counter = 0;
int temp_counter = 0;

/* inter code head */
IrCode* irHead = NULL;

Function* cFunc = NULL;

void generateLabel(char* name){
	strcpy(name, "label");
	char temp[20];
	itoa(label_counter, temp, 10);
	label_counter++;
	strcat(name, temp);
}

void generateTemp(char* name){
	strcpy(name, "_t");
	char temp[20];
	itoa(temp_counter, temp, 10);
	temp_counter++;
	strcat(name, temp);
}

void insertNode(int argsN, ...){
	IrCode* p = (IrCode*)malloc(sizeof(struct irnode));
	p->argsN = argsN;

	/* deal with the args */
	va_list args_list;
	va_start(args_list, argsN);

	int i = 0;
	for(i = 0; i < argsN; i++){
		strcpy(p->args[i], va_arg(args_list, char *));
	}
	if(irHead == NULL){
		p->next = p->pre = p;
		irHead = p;
	}
	/* ir head is not null */
	else{
		/* link the later field */
		p->pre = irHead->pre;
		irHead->pre->next = p;

		/* link the front field */
		irHead->pre = p;
		p->next = irHead;
	}
}

void deleteNode(IrCode* p){
	if(p->next == p){
		free(p);
		p = NULL;
		irHead = NULL;
	}else{
		IrCode* temp = p;
		/* drop temp link */
		p = p->pre;
		p->next = temp->next;
		p->next->pre = p;
		free(temp);
	}
}

void printIrCode(){
	if(irHead == NULL)
		return;
	IrCode* p = irHead;
	while(p != irHead){
		int i;
		for(i = 0; i < p->argsN; i++)
			printf("%s ", p->args[i]);
		printf("\n");
		p = p->next;
	}
}

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
void translateAst(AstClass* ast){
	if(ast == NULL)
		return;
	switch(ast->type)
	{
		case ctFuncDef:
		{
			Symbol s = findSymbol(ast->name, cFunc);
			cFunc = s->type->func;
			insertNode(3, "FUNCTION", ast->name, ":");
			Fieldlist* pars = cFunc->pars;
			int parsN = cFunc->parsN;
			int i = 0;
			while(i < parsN){
				int pos = namepool.names + pars->posPool;
				insertNode(2, "PARAM", namepool.names, pos);
				pars = pars->next;
			}
			break;
		}

		case ctVarDef:
		{
			Symbol s = findSymbol(ast->name, cFunc);
			AstClass* temp = ast->name;
			if(s->type->kind == S_STRUCT){
				char size[8];
				itoa(getMemorySpace(s->type), size, 10);
				insertNode(3, "DEC", (namePool.names+(s->posPool)), size);
			}
			if(ast->name->type == ctExp)
				translateExp(temp, (namePool.names+(s->posPool)), 1);
			break;
		}

		case ctStmtList:
		{
			if(ast->stmt == NULL)
				return;
			/* recgonize the first label */
			switch(ast->stmt->type){
				case ctExp:
				{
					translateExp(ast->stmt, NULL, 0);
					break;
				}
				case ctCompoundStmt:
				{
					translateAst(ast->stmt);
					break;
				}
				case ctIfElse:
				{
					char labelT[30], labelF[30];
					generateLabel(labelT);
					generateLabel(labelF);
					/* move to condition part to translate */
					translateCond(ast->stmt->cond, labelT, labelF);
					insertNode(3, "LABEL", labelT, ":");
					insertNode(3, "LABEL", labelF, ":");
					break;
				}
				case ctForStmt:
				{
					char label_init[30], label_cond[30], label_do[30], label_iter[30];
					generateLabel(label_init);
					generateLabel(label_cond);
					generateLabel(label_do);
					generateLabel(label_iter);

					insertNode(3, "LABEL", label_init, ":");
					translateAst(ast->stmt->initStmt);
					insertNode(3, "LABEL", label_cond, ":");
					translateCond(ast->stmt->exitCond);
					insertNode(3, "LABEL", label_iter, ":");
					translateCond(ast->stmt->iter);

					insertNode(3, "LABEL", label_do, ":");
					translateAst(ast->stmt->nextStmt);
					insertNode(2, "GOTO", label_iter);
					insertNode(2, "GOTO", label_cond);
					break;
				}
			}
			break;
		}
		default:{
			translateAst(ast);
		}
	} // switch
}

void translateExp(AstClass* p, char* place, int option){
	if(p->exp->type == ctExp)
		translateExp(p->exp, place, option);
	
	/* assign operator */
	else if(p->exp->type == ctAssignStmt){
		AstClass* temp = p->exp;
		char place_t[30];
		translateExp(temp->lhs, place_t, 0);
		translateExp(temp->rhs, place_t, 1);
		if(place != NULL){
			if(option == 0)
				strcpy(place, place_t);
			else
				insertNode(3, place, ":=", place_t);
		}
	}
	else if(p->exp->type == ctName){
		std::string name = p->exp->name;
		if(place == NULL){
			if(strcmp(name, "read") == 0)
				return;
			char temp[30];
			generateTemp(temp);
			insertNode(4, temp, ":=", "CALL", name);
		}else{
			if(option == 0)
				generateTemp(place);
			if(strcmp(name, "read") == 0)
				insertNode(2, "READ", place);
			else
				insertNode(4, place, ":=", "CALL", name);
		}
	}else if(p->exp->type == ctBinExp){
		char temp1[30], temp2[30];
		translateExp(p->exp, temp1, 0);
		if(p->exp->name == DIV || p->exp->name == MUL)
			insertNode(2, place, ":=");
		translateExp(p->exp, temp2, 0);
		if(p->exp->name == DIV || p->exp->name == MUL)
			insertNode(2, place, ":=");

		translateExp(p->exp->lfac, temp1, 0);
		translateExp(p->exp->rfac, temp2, 0);
		int iL = atoi(&temp1[1]);
		int iR = atoi(&temp2[1]);
		switch(p->exp->op){
			case PLUS:
			{
				char res[30];
				sprintf(res, "%d", iL+iR);
				insertNode(3, place, ":=", res);
				break;
			}
			case MINUS:
			{
				char res[30];
				sprintf(res, "%d", iL-iR);
				insertNode(3, place, ":=", res);
				break;
			}
			case MUL:
			{
				char res[30];
				sprintf(res, "%d", iL*iR);
				insertNode(3, place, ":=", res);
				break;
			}
			case DIV:
			{
				char res[30];
				sprintf(res, "%d", iL/iR);
				insertNode(3, place, ":=", res);
				break;
			}
			default:
			{
				char label1[30], label2[30];
				generateLabel(label1);
				generateLabel(label2);
				insertNode(2, place, ":=");
				translateCond(p->exp, label1, label2);
				break;
			}
		}
	}else{
		char label[30];
		generateLabel(label);
		insertNode(2,"NOT", place);
		translateCond(p->exp, label1, NULL);
	}
}

void translateCond(AstClass* p, char* labelT, char* labelF){
	if(p->type != ctBinExp){
		translateCond(p->exp, labelT, labelF);
		return;
	}
	/* bin exp */
	char left[30], right[30];
	translateExp(p->lfac, left, 0);
	translateExp(p->rfac, right, 0);
	int iL = atoi(&left[1]);
	int iR = atoi(&right[1]);

	switch(p->op){
		case EQ:
		{
			if(iL == iR)
				insertNode(2, "GOTO", labelT);
			else
				insertNode(2, "GOTO", labelF);
			break;
		}
		case GT:
		{
			if(iL > iR)
				insertNode(2, "GOTO", labelT);
			else
				insertNode(2, "GOTO", labelF);
			break;
		}
		case LT:
		{
			if(iL < iR)
				insertNode(2, "GOTO", labelT);
			else
				insertNode(2, "GOTO", labelF);
			break;
		}
		case GE:
		{
			if(iL >= iR)
				insertNode(2, "GOTO", labelT);
			else 
				insertNode(2, "GOTO", labelF);
			break;
		}
		case LE:
		{
			if(iL <= iR)
				insertNode(2, "GOTO", labelT);
			else
				insertNode(2, "GOTO", labelF);
			break;
		}
		case AND:
		{
			char label[30];
			generateLabel(label);
			translateCond(p->lhs, label, labelF);
			insertNode(3, "LABEL", label, ":");
			translateCond(p->rhs, labelT, labelF);
			break;
		}
		case OR:
		{
			char label[30];
			generateLabel(label);
			translateCond(p->lhs, labelT, label);
			insertNode(p->rhs, labelT, labelF);
			break;
		}
		default:
			return;
	} // switch
}

int getMemorySpace(Type* type){
	Fieldlist* p;
	int res = 0;
	p = type->structure;
	while(p != NULL){
		if(p->fieldType->kind != S_STRUCT)
			res += 4;
		else
			res += getMemorySpace(p->fieldType);
		p = p->next;
	}
	return res;
}
