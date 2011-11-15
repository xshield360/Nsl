#include "node.h"
#include <stdio.h>
#include <stdlib.h>


tree_node_t *new_exp_node(exp_type_t type)
{

}
tree_node_t *new_stmt_node(stmt_type_t type)
{
	tree_node_t *t = (tree_node_t *)malloc(sizeof(tree_node_t)+1);
	for (int i =0; i < MAXCHILDREN; ++i)
		t->childs[i] = NULL;
	t->sibling = NULL;
	t->node_type = NodeType_Stmt;
	t->type.stmt = StmtType_Decl;
}
//state node, 就一种类型
tree_node_t *new_state_node()
{
	//
}
tree_node_t *new_include_node()
{


}
tree_node_t *new_sub_node(){}
tree_node_t *new_header_node(header_type_t type){
	tree_node_t *t = (tree_node_t *)malloc(sizeof(tree_node_t)+1);
	for (int i =0;i < MAXCHILDREN; ++i)
		t->childs[i] = NULL;
	t->sibling = NULL;
	t->node_type = NodeType_Header;
	t->type.header = type;
	return t;
}
