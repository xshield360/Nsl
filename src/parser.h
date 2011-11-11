
/*
上下文无关文法

由终结符号，非终结符号，一个开始符号，一组产生式组成




BNF文法


处理文法的语法分析器大体上可以分为三种：通用的，
自顶向下
从顶部开始构造语法树

自底向上
从叶子结点开始构造语法树

总是按照从左到右的方式被扫描，每次扫描一个符号

LL文法

LR文法

E－>E + T | T
T -> T * F | F
F -> (E) | id
上述文法属于LR文法，适用于自底向上的语法分析技术。

E->TE1;
E1-> + TE1|e;
T->FT1;
T1->* FT1 | e
F->(E)|id  无左递归版本，适用于自顶向下的语法分析。



*/
#include "scanner.h"
#include "node.h"



typedef struct 
{
	const char *file_name;
	Token token;
	scanner_rc_t *scanner_rc;
}parser_rc_t;

void parser_init(parser_rc_t *rc, const char *file_name);

tree_node_t *parser_parse(parser_rc_t *rc);

//处理state的情况
tree_node_t *parser_state(parser_rc_t *rc);

void parser_debug(parser_rc_t *rc,tree_node_t * tree);

void parser_match(parser_rc_t *rc,TokenType expected);
tree_node_t *parser_stmt(parser_rc_t *rc);
tree_node_t *parser_if_stmt(parser_rc_t *rc);
tree_node_t *parser_while_stmt(parser_rc_t *rc);
tree_node_t *parser_do_stmt(parser_rc_t *rc);
tree_node_t *parser_assign_stmt(parser_rc_t *rc);
tree_node_t *parser_unsigned_stmt(parser_rc_t *rc);
tree_node_t *parser_include(parser_rc_t *rc);
tree_node_t *parser_define(parser_rc_t *rc);
tree_node_t *parser_exp(parser_rc_t *rc);
tree_node_t *parser_simple_exp(parser_rc_t *rc);
tree_node_t *parser_term(parser_rc_t *rc);
tree_node_t *parser_factor(parser_rc_t *rc);
tree_node_t *parser_stmt_seq(parser_rc_t *rc);
tree_node_t *parser_substate(parser_rc_t *rc);
tree_node_t *parser_state(parser_rc_t *rc);



