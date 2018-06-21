#include "symbol.h"

unsigned int hashPJW(const char* name){
	unsigned hash_value, i;
	for(hash_value = 0; *name; ++name){
		hash_value = (hash_value << ONE_EIGHTH) + *name;
		if((i = hash_value & HIGH_BITS) != 0)
			hash_value = (hash_value ^ (i >> THREE_QUARTERS)) & ~HIGH_BITS;
	}
	return hash_value;
}

Symbol generateSymbol(const char* name, int level, int line){
	Symbol symbol = (Symbol)malloc(sizeof(struct symbol));
	int curPos = namepool.curPosition;
	symbol->posPool = curPos;
	symbol->level = level;
	symbol->line = line;
	symbol->type = NULL;
	symbol->next = NULL;

	if(curPos + strlen(name) > 1024)
		return NULL;
	else{
		strcpy((namepool.names+namepool.curPosition), name);
		namepool.curPosition = curPos + strlen(name) + 1;
		return symbol;
	}
}

Symbol findSymbol(const char* name, Function* curFunc){
	int stEmpty = 0;
	int key = (int)hashPJW(name);
	while(symTable[key] != NULL){
		Symbol value = symTable[key];
		char* name_t = namepool.names + value->posPool;
		if(strcmp(name_t, name) == 0)
			return value;
		if(++key == (int)hashPJW(name)){
			stEmpty = 1;
			break;
		}
	}
	/* find in the func field */
	Type* type = findFieldType(name, curFunc->pars);
	/* judge break condition */
	if(stEmpty == 0 || curFunc == NULL || type == NULL)
		return NULL;
	Symbol s = generateSymbol(name, 0, -1);
	s->type = type;
	return s;
}

Type* findFieldType(const char* name, FieldList* f){
	/* scane to search */
	FieldList* head = f;
	while(head != NULL){
		char* name_t = namepool.names + head->posPool;
		if(strcmp(name_t, name) == 0)
			return head->fieldType;
		head = head->next;
	}
	return NULL;
}

