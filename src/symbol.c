#include "symbol.h"


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

void IncludeList_insert(char *name,...)
{

}
void IncludeList_delete(char *name)
{
	int h = hash(name);
	IncludeListHash[h] = NULL;
}

void IncludeList_find(char *name)
{
	int h = hash(name);
	IncludeList *l;
	l = IncludeListHash[h];
	return l->memloc;
}

void List_insert()
{
}

void List_delete()
{
}
void List_find()
{

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

}
void StateList_find()
{

}
