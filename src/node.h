//定义结点的三种类型
typedef enum{
	NodeType_State = 1,
	NodeType_Block,
	NodeType_Stmt
}node_type_t;

typedef enum{

};

//最多一共有五个子结点
/*
s -> state id { block }
block-> S  x : { stmt }
s->stc|cts
stmt -> stmt; //这个最后推出语句

*/
#define MAXCHILDREN 6

typedef struct TreeNode
{
	struct TreeNode *childs[MAXCHILDREN]; //定义子结点的个数
	struct TreeNode *sibling; //定义叶子
	node_type_t node_type_t; //定义结点类型

}tree_node_t;

