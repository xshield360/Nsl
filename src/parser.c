#include "parser.h"
#include "stdio.h"
#include "stdlib.h"

/*
 * function name : parser_init
 * we use it to init the parser. 
 */	
void parser_init(parser_rc_t *rc, const char *file_name)
{
	rc->file_name = file_name;
	scanner_rc_t *scanner = (scanner_rc_t *)malloc(sizeof(scanner_rc_t));
	
	if (scanner_open_file(scanner,rc->file_name) >= 0 ) {
		rc->scanner_rc = scanner;
		//init the symbol table
		symbol_t *symbol = (symbol_t *)malloc(sizeof(symbol_t));
		rc->symbol = symbol;
	} else {
		printf("scanner_open_file error, the file may be not exist\n");
		exit(0);
	}
}

/*
 * function name: parser_program
 * use it to parser the program
 */
tree_node_t *parser_program(parser_rc_t *rc)
{
	//we get the token to check the state.
	tree_node_t *tree = NULL;
	if (rc == NULL) 
	{
		//
		printf("rc is null \n");
		return tree;
	}
	rc->token = scanner_get_next_token(rc->scanner_rc);
	
	if (rc->token.t == T_POUND)
	{
		//the headers
		tree = parser_header(rc);
	} else if (rc->token.t == T_SUB)
	{
		//the sub 
		tree = parser_sub(rc);
	} else if (rc->token.t == T_STATE)
	{
		//the state
		tree = parser_state(rc);
	} else if (rc->token.t == T_UNSIGNED)
	{
		tree = parser_decls(rc);
	} else if (rc->token.t == T_ENUM)
	{
		tree = parser_enum(rc);
	} else {
		parser_syntax_error(rc,"code error in the parogram");
	}
	return tree;
}

/*
 * function name: parser_sub
 * use it to parser the sub function
 */
tree_node_t *parser_sub(parser_rc_t *rc)
{
	//to create a sub node
	tree_node_t *t = new_sub_node();
	parser_match(rc,T_SUB);
	
	//we need to store the T_ID into the symbol table
	
	if (t!=0 && rc->token.t == T_ID) 
	{
		//we get the value then insert into the symbol table.
		//the code about push the value into the symbol table
	}
	
	t->childs[0] = parser_block(rc); //parser the block about the sub
	return t;
}

/*
 * function name: parser_state
 * use it to parser the state block
 */
tree_node_t *parser_state(parser_rc_t *rc)
{
	tree_node_t *t = new_state_node();
	parser_match(rc,T_STATE);
	//we then need push the ID into the symbol table
	if (t!= 0 && rc->token.t == T_ID)
	{
		//the code about push the ID value into the symbol table.
	}
	t->childs[0] = parser_state_block(rc);
	return t;
}

/*
 * function name: parser_header
 * to parser the header about the program
 */
tree_node_t *parser_header(parser_rc_t *rc)
{
	tree_node_t *t = NULL;
	parser_match(rc,T_POUND);
	//we check if it is the define or the include.
	if (rc->token.t == T_DEFINE)
	{
		t = parser_define(rc);
	} else if (rc->token.t == T_INCLUDE) {
		t = parser_include(rc);
	}
	return t;
}


/*
 * function name: parser_decls
 * to parser decls 
 */
tree_node_t *parser_decls(parser_rc_t *rc){
	//
}

/*
 * function name: parser_decl
 * to parser decl
 */
tree_node_t *parser_decl(parser_rc_t *rc){
	//
}

tree_node_t *parser_state_block(parser_rc_t *rc){}
tree_node_t *parser_regex_action(parser_rc_t *rc)//{stc|cts+id+:+block} 
{

}
tree_node_t *parser_block(parser_rc_t *rc){
	tree_node_t *t = NULL;
	return t;
}

tree_node_t *parser_define(parser_rc_t *rc){
	tree_node_t *t = new_header_node(HeaderType_Define);
	parser_match(rc,T_DEFINE);
	
	return t;
}
tree_node_t *parser_include(parser_rc_t *rc){
	tree_node_t *t = new_header_node(HeaderType_Include);
	parser_match(rc,T_INCLUDE);
	//write the symbol into the symbol table;
	
	return t;
}
tree_node_t *parser_enum(parser_rc_t *rc){
	tree_node_t *t = NULL;
	return t;
}

tree_node_t *parser_stmts(parser_rc_t *rc){
	tree_node_t *t = NULL;
	return t;
}
tree_node_t *parser_stmt(parser_rc_t *rc){
	tree_node_t *t = NULL;
	return t;
}

tree_node_t *parser_stmt_exp(parser_rc_t *rc){
	tree_node_t *t = NULL;
	return t;
}
tree_node_t *parser_stmt_if(parser_rc_t *rc){
	tree_node_t *t = NULL;
	return t;
} 
tree_node_t *parser_stmt_do(parser_rc_t *rc){
	tree_node_t *t = NULL;
	return t;
}
tree_node_t *parser_stmt_while(parser_rc_t *rc){
	tree_node_t *t = NULL;
	return t;
}

void parser_debug(parser_rc_t *rc,tree_node_t * tree){
	//debug
	
}

/*
 * function name: parser_match
 * to match the Token
 */
void parser_match(parser_rc_t *rc,TokenType expected){
	if (rc->token.t == expected)
	{
		rc->token = scanner_get_next_token(rc->scanner_rc);
	} else {
		parser_syntax_error(rc,NULL);
	}

}

/*
 * function name: parser_syntax_error
 * to display the syntax error
 */
void parser_syntax_error(parser_rc_t *rc, const char *msg){
	fprintf(stderr,"Line %d,Unexcepted token [%s]\n",scanner_get_curr_line(rc->scanner_rc),token_get_name(rc->token.t));
    if (msg)
	{
		fprintf(stderr,"Detail:%s\n",msg);;
	}
    exit(-1);
}
