//符号表是一种供编译器用于保存有关源程序构造的各种信息的数据结构
//符号表相关，我们将为每个作用建立自己的单独的符号表，符号表的每个条目中
//包含与一个标识符相关的信息，比如它的字符串，它的类型，它的存储位置，
//和其他相关信息。

#include "parser.h"

//初始化语法分析器
void parser_init(parser_rc_t *rc, const char *file_name)
{
	rc->file_name = file_name;
	scanner_rc_t *scanner = (scanner_rc_t *)malloc(sizeof(scanner_rc_t));
	scanner_open_file(scanner,rc->file_name);
	rc->scanner_rc = scanner;
}

tree_node_t * parser_parse(parser_rc_t *rc)
{
	//
	tree_node_t * tree;
	rc->token = scanner_get_next_token(rc->scanner_rc);
	
	//tree = parser_stmt_seq(rc);
	if (rc->token.t == T_STATE)
	{
		//处理state开始的情况
		tree = parser_state(rc);
	} else {
		//处理其它情况
		//包括变量定义，if_else do_while,等情况
		tree = parser_stmt_seq(rc);
	}
	if (rc->token.t != T_DONE)
	{
		parser_syntax_error(rc,"Code ends error");
	}
	return tree;
}
tree_node_t *parser_state(rc)
{
  //to create a state node.
  tree_node_t *t = new 
}
