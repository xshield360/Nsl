#include "parser.h"
#include "stdio.h"
#include "stdlib.h"

/*
 * function name : parser_init
 * we use it to init the parser. 
 */	
void parser_init(parser_rc_t *rc, const char *file_name) {
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
tree_node_t *parser_program(parser_rc_t *rc) {
	//we get the token to check the state.
	tree_node_t *tree = NULL;
	tree_node_t *p = NULL;
	tree_node_t *q = NULL;

	if (rc == NULL) 
	{
		//
		printf("rc is null \n");
		return tree;
	}
	
	while(1) {
		rc->token = scanner_get_next_token(rc->scanner_rc);
		TokenType t = rc->token.t;
		if (t == T_POUND) {
			//the headers
			p = parser_header(rc);
		} else if (t == T_SUB){
			//the sub 
			p = parser_sub(rc);
		} else if (t == T_STATE){
			//the state
			p = parser_state(rc);
		} else if (t == T_UNSIGNED){
			p = parser_decl(rc);
		} else if (t == T_ENUM){
			p = parser_enum(rc);
		} else if (t == T_DONE){
			break;
		} else {
			parser_syntax_error(rc,"code error in the parogram");
	    }
		// add the node to the tree
		if (tree != NULL) {
			q = tree;
			while(q->sibling != NULL) q = q->sibling;
			q->sibling = p;
		} else {
			tree = p;
		}
	}
	return tree;
}

/*
 * function name: parser_sub
 * use it to parser the sub function
 */
tree_node_t *parser_sub(parser_rc_t *rc) {
	//to create a sub node
	tree_node_t *t = new_sub_node();
	parser_match(rc,T_SUB);
	
	//we need to store the T_ID into the symbol table
	
	if (t!=0 && rc->token.t == T_ID) 
	{
		//we get the value then insert into the symbol table.
		//the code about push the value into the symbol table
		parser_match(rc,T_ID);
		t->childs[0] = parser_block(rc); //parser the block about the sub
	}
	return t;
}

/*
 * function name: parser_state
 * use it to parser the state block
 */
tree_node_t *parser_state(parser_rc_t *rc) {
	tree_node_t *t = new_state_node();
	parser_match(rc,T_STATE);
	//we then need push the ID into the symbol table
	if (t!= 0 && rc->token.t == T_ID)
	{
		//the code about push the ID value into the symbol table.
		parser_match(rc,T_ID);
		t->childs[0] = parser_block(rc);
		return t;
	}
	return t;
}

/*
 * function name: parser_header
 * to parser the header about the program
 */
tree_node_t *parser_header(parser_rc_t *rc) {
	tree_node_t *t = NULL;
	parser_match(rc,T_POUND);
	//we check if it is the define or the include.
	if (rc->token.t == T_DEFINE)
	{
		t = parser_define(rc);
	} else if (rc->token.t == T_INCLUDE) {
		t = parser_include(rc);
	} else if (rc->token.t == T_IF) { // deal the #if define *** #ELSE    #endif
	} else if (rc->token.t == T_ELSE){
	} else if (rc->token.t == T_ENDIF){
	}
	return t;
}

/*
 * function name: parser_decls
 * to parser decls 
 */
tree_node_t *parser_decls(parser_rc_t *rc) {
	//
}

/*
 * function name: parser_decl
 * to parser decl
 */
tree_node_t *parser_decl(parser_rc_t *rc) {
	//unsigned ...:number;
	tree_node_t *t = new_stmt_node(StmtType_Decl);
	char *name;
	int type;
	parser_match(rc,T_UNSIGNED);
	if (t!=NULL && rc->token.t == T_ID)
	{                                                                                                         
		name = rc->token.c;
		t->attr = hash(rc->token.c);
		//IncludeList_insert(rc->symbol,rc->token.c);
		parser_match(rc,T_ID);
		parser_match(rc,T_COLON);
		if (t!= NULL && rc->token.t == T_NUMBER)
		{
			type = atoi(rc->token.c);
			t->attr = hash(name);
			DeclList_insert(rc->symbol,name,type);
			parser_match(rc,T_NUMBER);
			//parser_match(rc,T_SEMI);
			if (rc->token.t != T_SEMI)
			{
				parser_syntax_error(rc,"Error in parser_decl,the end must be semi\n");
			}
		} else {
			parser_syntax_error(rc,"Error in the parser_decl,the number must be 8,16,32\n");
		}
	} else {
		parser_syntax_error(rc,"Error in the parser_decl");
	}
	return t;
}

tree_node_t *parser_regex_action(parser_rc_t *rc)//{stc|cts+id/regex+:+block} 
{

}
/*
 * Notice the block is just like {stmts} style. so we need to match the { and the }.
 */
tree_node_t *parser_block(parser_rc_t *rc){
	tree_node_t *t = new_stmt_node(StmtType_Block);
	tree_node_t *p;
	p = t;
	parser_match(rc,T_LC);
	while(rc->token.t != T_LC) {
		tree_node *q = parser_stmt(rc);
		if (q!=NULL)
		{
			p->sibling = q;
			p = q;
		}
	}
	t = parser_stmts(rc);
	parser_match(rc,T_RC);
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
	if (t!=NULL && rc->token.t == T_LITERAL)
	{
		//copy the string to the symbol table.
		//
		t->attr = hash(rc->token.c);
		IncludeList_insert(rc->symbol,rc->token.c);
	}
	return t;
}
tree_node_t *parser_enum(parser_rc_t *rc){
	tree_node_t *t = new_header_node(HeaderType_Enum);
	parser_match(rc,T_ENUM);
	int h = 0;
	char *name;
	int last_value =0,now_value = 0;
	if (rc->token.t == T_ID)
	{
		//it may be the enum name
		h = hash(rc->token.c);
		t->attr = h;
		printf("hash value is %d\n",h);
		EnumListHash_insert(rc->symbol,rc->token.c,0,1);
		//we insert the name into enum hash.
		parser_match(rc,T_ID);
	}
	parser_match(rc,T_LC);
	//check if the next word{a,b,c}
	while(1)
	{
		if (rc->token.t == T_ID)
		{
			//add a into the symbol table
			//There is no name
			
			printf("aaaaaa hash value is %d\n",h);
			if (h == 0)
			{
				//we insert a=0,into the table.
				h = hash(rc->token.c);
				t->attr = h;
				name = rc->token.c;
				printf("hash value is %d\n",h);
				parser_match(rc,T_ID);
				if (rc->token.t == T_ASSIGN) {
					parser_match(rc,T_ASSIGN);
					if (rc->token.t == T_NUMBER) {
						now_value = atoi(rc->token.c);
						last_value = now_value;
						parser_match(rc,T_NUMBER);
					} else {
						printf("error\n");
					}
				} else if (rc->token.t == T_COMMA)
				{
					now_value = last_value = 0;
				}
				EnumListHash_insert(rc->symbol,name,now_value,2); //type=2,
			} else {
				//add the values to 
				name = rc->token.c;
				parser_match(rc,T_ID);
				printf("name %s\n",name);
				if (rc->token.t == T_ASSIGN)
				{
					parser_match(rc,T_ASSIGN);
					if (rc->token.t == T_NUMBER)
					{
						last_value = now_value;
						now_value = atoi(rc->token.c);
						parser_match(rc,T_NUMBER);
					} else {
						printf("error\n");
					}
				} else if (rc->token.t == T_COMMA)
				{
					now_value = last_value + 1;
					last_value = now_value;
				}
				EnumList * list;
				list = rc->symbol->EnumListHash[h];
				printf("name %s now_value %d\n",name,now_value);
				EnumList_add(list,name,now_value,2);
			}
			
			if (rc->token.t == T_COMMA)
			{	
				parser_match(rc,T_COMMA);
			}
		} else if (rc->token.t == T_RC){
			break;
		} else {
			printf("Error in the parser_enum,wrong struct\n");
			break;
		}
	}
	//
	if (rc->token.t == T_RC) parser_match(rc,T_RC);
	
	if (rc->token.t != T_SEMI)
	{
		parser_syntax_error(rc,"Error in parser_enum\n");
	}
		
	return t;
	
}

tree_node_t *parser_stmts(parser_rc_t *rc) {
	tree_node_t *t = parser_stmt(rc);
	tree_node_t *p;
	p = t;
	while (rc->token.t != T_DONE && rc->token.t != T_ERROR) {
		tree_node_t *q = NULL;
		if (rc->token.t != T_DONE) {
			q = parser_stmt(rc);
			if (q != NULL) {
				if (t == NULL) t = p = q;
				else {
					p->sibling = q;
					p = q;
				}
			}
		}
	}
	return t;
}

tree_node_t *parser_stmt(parser_rc_t *rc){
	tree_node_t *t = NULL;
	switch(rc->token.t) {
		case T_SEMI:
			parser_match(rc,T_SEMI);
			break;
		case T_LC:
			t = parser_block(rc);
			break;
		case T_IF:
			t = parser_stmt_if(rc);
			break;
		case T_WHILE:
			t = parser_stmt_while(rc);
			break;
		case T_DO:
			t = parser_stmt_do(rc);
			break;
		case T_UNSIGNED:
			t = parser_decl(rc);
			break;
		case T_ID:
			t = parser_stmt_assign(rc);
			break;
		case T_STC:
			t = parser_action_block(rc);
		case T_CTS:
			t = parser_action_block(rc);
		default: 
			parser_syntx_error(rc,NULL);
			break;
	}
	return t;
}
//cts|stc regex|start|end : action_block
tree_node_t *parser_action_block(parser_rc_t *rc) {
	 tree_node_t *t = new_stmt_anode(StmtType_ActionBlock);
	 if (t!= NULL) {
		if (rc->token.t == T_STC) {
			//record the stc
			parser_match(rc,T_STC);
		} else if (rc->token.t == T_CTS) {
			//record the cts
			parser_match(rc,T_CTS);
		}
		t->childs[0] = parser_action_regex(rc);
		parser_match(rc,T_COLON);
		t-childs[1] = parser_block(rc);
		return t;
	 }
}

//parser the action regex.

tree_node_t *parser_action_regex(parser_rc_t *rc) {
	tree_node_t *t = newstmt_node(StmtType_Regex);
	if (t!=NULL) {
		if (rc->token.t == T_START) {
			//record the start
			parser_match(rc,T_START);
		} else if (rc->token.t == T_END) {
			//record the end
			parser_match(rc,T_END);
		} else if (rc->token.t == T_LITERAL){
			//record the literal
			parser_match(rc,T_LITERAL);
		}
	}
	return t;
}

tree_node_t *parser_stmt_assign(parser_rc_t *rc) {
	tree_node_t *t = new_stmt_node(StmtType_Assign);
	if (t!= NULL && rc->token.t = T_ID) {
		parser_match(rc,T_ID);
		parser_match(rc,T_ASSIGN);
		t->childs[0] = parser_stmt_exp(rc);
		return t;
	}
	parser_syntx_error(rc,NULL);
	return t;
}

tree_node_t *parser_stmt_exp(parser_rc_t *rc){
	tree_node_t *t = NULL;
	tree_node_t *t = parser_simple_exp(rc);
	if (rc->token.t == T)
	return t;
}
tree_node_t *parser_exp(parser_rc_t *rc) {
  tree_node_t *t = parser_simple_exp(rc);
  if (rc->token.t == T_LT ||
      rc->token.t == T_GT ||
      rc->token.t == T_LE ||
      rc->token.t == T_GE ||
      rc->token.t == T_EQ ||
      rc->token.t == T_NEQ
      ) {
    tree_node_t *p = new_exp_node(ExpType_Op);
    if (p != NULL) {
      p->childs[0] = t;
      p->attr.op = rc->token.t;
      t = p; 
    }
    parser_match(rc, rc->token.t);
    if (t != NULL)
      t->childs[1] = parser_simple_exp(rc);
  }
  return t;
}

tree_node_t *parser_simple_exp(parser_rc_t *rc) {
  tree_node_t *t = parser_term(rc);
  while (rc->token.t == T_MINUS || rc->token.t == T_PLUS) {
    tree_node_t *p = new_exp_node(ExpType_Op);
    if (p != NULL) {
      p->childs[0] = t;
      p->attr.op = rc->token.t;
      t = p;
      parser_match(rc, rc->token.t);
      t->childs[1] = parser_term(rc);
    }
  }
  return t;
}

tree_node_t *parser_term(parser_rc_t *rc) {
  tree_node_t *t = parser_factor(rc);
  while (rc->token.t == T_MUL || rc->token.t == T_DIV || rc->token.t == T_MOD) {
    tree_node_t *p = new_exp_node(ExpType_Op);
    if (p != NULL) {
      p->childs[0] = t;
      p->attr.op = rc->token.t;
      t = p;
      parser_match(rc, rc->token.t);
      t->childs[1] = parser_factor(rc);
    }
  }
  return t;
}

tree_node_t *parser_factor(parser_rc_t *rc) {
  tree_node_t *t = NULL;
  switch (rc->token.t) {
    case T_INTEGER:
      t = new_exp_node(ExpType_Integer);
      t->attr.val = atoi(rc->token.c);
      parser_match(rc, T_INTEGER);
      break;
    case T_DOUBLE:
      t = new_exp_node(ExpType_Double);
      t->attr.dval = atof(rc->token.c);
      parser_match(rc, T_DOUBLE);
      break;
    case T_STRING:
      t = new_exp_node(ExpType_String);
      t->attr.name = (char *)malloc(strlen(rc->token.c) + 1);
      memset(t->attr.name, 0, strlen(rc->token.c) + 1);
      memcpy(t->attr.name, rc->token.c, strlen(rc->token.c));
      parser_match(rc, T_STRING);
      break;
    case T_IDENTIFIER:
      t = new_exp_node(ExpType_Identifier);
      t->attr.name = (char *)malloc(strlen(rc->token.c) + 1);
      memset(t->attr.name, 0, strlen(rc->token.c) + 1);
      memcpy(t->attr.name, rc->token.c, strlen(rc->token.c));
      parser_match(rc, T_IDENTIFIER);
      break;
    case T_LP:
      parser_match(rc, T_LP);
      t = parser_exp(rc);
      parser_match(rc, T_RP);
      break;
    default:
      parser_syntax_error(rc, NULL);
      break;
  }
  return t;
}

tree_node_t *parser_stmt_if(parser_rc_t *rc){
	tree_node_t *t = new_stmt_node(StmtType_If);
	parser_match(rc,T_IF);
	parser_match(rc,T_LP);
	t->childs[0] = parser_stmt_exp(rc);
	parser_match(rc,T_RP);
	if (rc->token.t == T_LC) {
		t->childs[1] = parser_block(rc);
	} else {
		t->childs[1] = parser_stmt_exp(rc);
	}	
	return t;
} 
tree_node_t *parser_stmt_do(parser_rc_t *rc){
	
	tree_node_t *t = new_stmt_node(StmtType_Do);
	parser_match(rc,T_DO);
	t->childs[0] = parser_block(rc);
	parser_match(rc,T_WHILE);
	parser_match(rc,T_LP);
	t->childs[1] = parser_stmt_exp(rc);
	parser_match(rc,T_RP);
	parser_match(rc,T_SEMI);
	
	return t;
}

tree_node_t *parser_stmt_while(parser_rc_t *rc){
	tree_node_t *t = new_stmt_node(StmtType_While);
	parser_match(rc,T_WHILE);
	parser_match(rc,T_LP);
	t->childs[0] = parser_stmt_exp(rc);
	parser_match(rc,T_RP);
	t->childs[1] = parser_block(rc);
	return t;
}

void parser_debug(parser_rc_t *rc,tree_node_t * tree){
	//debug the rc tree
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
