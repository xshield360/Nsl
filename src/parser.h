#ifndef __NSL_PARSER_H__
#define __NSL_PARSER_H__

#include "scanner.h"
#include "node.h"
#include "symbol.h"

typedef struct 
{
	const char *file_name;
	Token token;
	scanner_rc_t *scanner_rc;
	symbol_t *symbol;
}parser_rc_t;

void parser_init(parser_rc_t *rc, const char *file_name);

tree_node_t *parser_program(parser_rc_t *rc);
tree_node_t *parser_sub(parser_rc_t *rc);
tree_node_t *parser_state(parser_rc_t *rc);
tree_node_t *parser_header(parser_rc_t *rc);

tree_node_t *parser_decls(parser_rc_t *rc);
tree_node_t *parser_decl(parser_rc_t *rc);
tree_node_t *parser_state_block(parser_rc_t *rc);
tree_node_t *parser_regex_action(parser_rc_t *rc);//{stc|cts+id+:+block}
tree_node_t *parser_block(parser_rc_t *rc);

tree_node_t *parser_define(parser_rc_t *rc);
tree_node_t *parser_include(parser_rc_t *rc);
tree_node_t *parser_enum(parser_rc_t *rc);

tree_node_t *parser_stmts(parser_rc_t *rc);
tree_node_t *parser_stmt(parser_rc_t *rc);

tree_node_t *parser_stmt_exp(parser_rc_t *rc);
tree_node_t *parser_stmt_if(parser_rc_t *rc);//if () block else block 
tree_node_t *parser_stmt_do(parser_rc_t *rc);//do block while();
tree_node_t *parser_stmt_while(parser_rc_t *rc);//while() block
tree_node_t *parser_stmt_assign(parser_rc_t *rc);// a=b; a=c

void parser_debug(parser_rc_t *rc,tree_node_t * tree);
void parser_match(parser_rc_t *rc,TokenType expected);
void parser_syntax_error(parser_rc_t *rc, const char *msg);

tree_node_t *parser_term(parser_rc_t *rc);
tree_node_t *parser_factor(parser_rc_t *rc);

#endif
