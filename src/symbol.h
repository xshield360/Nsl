#ifndef __NSL_SYMBOL_H__
#define __NSL_SYMBOL_H__

#define SIZE 211
#define SHIFT 4

typedef struct _INCLUDE{
	char *name;
	//	IncludeList *next;
}IncludeList,*pIncludeList;

typedef struct _DECL{
	char *name;
	int type;//8,16,32
}DeclList,*pDeclList;

typedef struct EnumList{
	char *name;
	int value;
	int type; // type = 1,the enum name,type=2,the members.
	struct EnumList *next; 
}EnumList,*pEnumList;

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
	EnumList *EnumListHash[SIZE];
	DeclList *DeclListHash[SIZE];
	FunctionList* FunctionListHash[SIZE];
	StateList* StateListHash[SIZE];
}symbol_t;
void symbol_init(symbol_t *symbol);
int hash(char* key);
void IncludeList_insert(symbol_t *symbol,char *name);
void IncludeList_delete(symbol_t *symbol,char *name);
char *IncludeList_find(symbol_t *symbol,char *name);

void DeclList_insert(symbol_t *symbol,char *name,int type);
void DeclList_delete(symbol_t *symbol,char *name);
void DeclList_find(symbol_t *symbol,char *name, DeclList *list);

void EnumListHash_insert(symbol_t *symbol,char *name,int value,int type);
void EnumListHash_delete(symbol_t *symbol,char *name);
void EnumListHash_find(symbol_t *symbol,char *name,EnumList *list);

void EnumList_add(EnumList *list,char *name,int value,int type); //add the list node to the end of list.


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
