#ifndef __NSL_NODE_H__
#define __NSL_NODE_H__

#include "scanner.h"

//定义结点的三种类型,一种状态类型，一种类型，一种头部类型，一种代码类型
typedef enum{
	NodeType_State = 1,
	NodeType_Sub, //
	NodeType_Header, //
	NodeType_Stmt, //
	NodeType_Exp //表达式类型
}node_type_t;

//定义头部的几种类型
typedef enum{
	HeaderType_Include = 1,
	HeaderType_Define,
	HeaderType_Enum,
	HeaderType_Struct
}header_type_t;

//定义代码类型
typedef enum{
	StmtType_If = 1,
	StmtType_While,
	StmtType_For,
	StmtType_Assign,
	StmtType_Decl,
	StmtType_Do,
}stmt_type_t;


//定义表达式类型
typedef enum{
	ExpType_Op
}exp_type_t;

#define MAXCHILDREN 6

typedef struct TreeNode
{
	struct TreeNode *childs[MAXCHILDREN]; //定义子结点的个数
	struct TreeNode *sibling; //定义叶子
	node_type_t node_type; //定义结点类型
	union{
		stmt_type_t stmt;
		header_type_t header;
		exp_type_t exp;
	}type;
	int attr;
	exp_type_t exp_type;
}tree_node_t;
tree_node_t *new_exp_node(exp_type_t type);
tree_node_t *new_stmt_node(stmt_type_t type);
tree_node_t *new_state_node();
tree_node_t *new_include_node();
tree_node_t *new_sub_node();
tree_node_t *new_header_node();
#endif
