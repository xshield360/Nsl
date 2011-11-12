#ifndef __NSL_SYMBOL_H__
#define __NSL_SYMBOL_H__

#define SIZE 211
#define SHIFT 4

typedef struct _INCLUDE{
	char *name;
	IncludeList *next;
}IncludeList,*pIncludeList;

//常量，变量，指针
typedef struct _LIST{
	char *name; //名称
	int type; //类型
	int scope;//标识符作用域信息
	int memloc;//内存中的位置
	int flag; //常量，变量，指针
	List *next;
}List,*pList;

//sub function
typedef struct _FUNCTIONLIST{
	char *name;//
	long memloc; //地址
	FunctionList *next;//
}FunctionList,*pFunctionList;

//the action in the state 
typedef struct _ACTIONLIST{
	char *regex;
	ActionList *next;
}ActionList,*pActionList;

//state define
typedef struct _STATELIST{
	char *name;//
	ActionList *actionId;
	StateList *next;
}StateList,*pStateList;

IncludeList IncludeListHash[SIZE];
List ListHash[SIZE];
FunctionList FunctionListHash[SIZE];
StateList StateListHash[SIZE];


int hash(char* key);
void IncludeList_insert();
void IncludeList_delete();
void IncludeList_find();

void List_insert();
void List_delete();
void List_find();

void FunctionList_insert();
void FunctionList_delete();
void FunctionList_find();

void StateList_insert();
void StateList_delete();
void StateList_find();


#endif
