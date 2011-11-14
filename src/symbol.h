#ifndef __NSL_SYMBOL_H__
#define __NSL_SYMBOL_H__

#define SIZE 211
#define SHIFT 4

typedef struct _INCLUDE{
	char *name;
	//	IncludeList *next;
}IncludeList,*pIncludeList;

//常量，变量，指针
typedef struct List{
	char *name; //名称
	int type; //类型
	int scope;//标识符作用域信息
	int memloc;//内存中的位置
	int flag; //常量，变量，指针
	struct List *next;
}List,*pList;

//sub function
typedef struct FunctionList{
	char *name;//
	long memloc; //地址
	struct FunctionList *next;//
}FunctionList,*pFunctionList;

//the action in the state 
typedef struct ActionList{
	char *regex;
	struct ActionList *next;
}ActionList,*pActionList;

//state define
typedef struct StateList{
	char *name;//
	ActionList *actionId;
	struct StateList *next;
}StateList,*pStateList;

typedef struct {
	IncludeList* IncludeListHash[SIZE];
	List* ListHash[SIZE];
	FunctionList* FunctionListHash[SIZE];
	StateList* StateListHash[SIZE];
}symbol_t;
void symbol_init(symbol_t *symbol);
int hash(char* key);
void IncludeList_insert(symbol_t *symbol,char *name);
void IncludeList_delete(symbol_t *symbol,char *name);
char *IncludeList_find(symbol_t *symbol,char *name);
/*
void List_insert();
void List_delete();
void List_find();

void FunctionList_insert();
void FunctionList_delete();
void FunctionList_find();

void StateList_insert();
void StateList_delete();
void StateList_find();
*/

#endif
