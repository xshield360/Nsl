#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>

int hash(char* key)
{
	int temp = 0;
	int i =0;
	while(key[i] != '\0')
	{
		temp = ((temp<<SHIFT) + key[i]) %SIZE;
		++i;
	}
	return temp;
}
void symbol_init(symbol_t *symbol)
{
	int i;
	for (i = 0; i < SIZE; i ++) {
		symbol->IncludeListHash[i] = NULL;
		symbol->ListHash[i] = NULL;
		symbol->DeclListHash[i] = NULL;
		symbol->FunctionListHash[i] = NULL;
		symbol->StateListHash[i] = NULL;
	}
}
void IncludeList_insert(symbol_t *symbol,char *name)
{
	IncludeList *pname;
	pname = (IncludeList *)malloc(sizeof(IncludeList));
	pname->name = name;
	int h = hash(name);
	symbol->IncludeListHash[h] = pname;
}
void IncludeList_delete(symbol_t *symbol,char *name)
{
	int h = hash(name);
	IncludeList *pname;
	pname = symbol->IncludeListHash[h];
	if (pname != NULL) free(pname);
	symbol->IncludeListHash[h] = NULL;
}

char *IncludeList_find(symbol_t *symbol,char *name)
{
	int h = hash(name);
	IncludeList *l;
	l = symbol->IncludeListHash[h];
	return l->name;
}
void DeclList_insert(symbol_t *symbol,char *name,int type)
{
	DeclList *plist;
	plist = (DeclList *)malloc(sizeof(DeclList));
	plist->name = name;
	plist->type = type;
	int h = hash(name);
	symbol->DeclListHash[h] = plist; 
}
void DeclList_delete(symbol_t *symbol,char *name)
{
	int h = hash(name);
	DeclList *plist;
	plist = symbol->DeclListHash[h];
	if (plist != NULL) free(plist);
	symbol->DeclListHash[h] = NULL;
}
void DeclList_find(symbol_t *symbol,char *name,DeclList *list)
{
	int h = hash(name);
	DeclList *plist = symbol->DeclListHash[h];
	list = plist;
}
/*
void List_insert()
{
}

void List_delete()
{
	int h = hash(name);
	ListHash[h] = NULL;
}
void List_find()
{
	List *l;
	l = 
}

void FunctionList_insert()
{
}
void FunctionList_delete()
{
}
void FunctionList_find()
{
}

void StateList_insert()
{
	
}
void StateList_delete()
{
	int h = hash(state_name);
	StateListHash[h] = NULL;
}
void StateList_find(char *state_name)
{
	int h;
	h = hash(state_name);
	StateList *l;
	l = StateListHash[h];
	return l->memloc;
}
*/
