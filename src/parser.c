//符号表是一种供编译器用于保存有关源程序构造的各种信息的数据结
//符号表相关，我们将为每个作用建立自己的单独的符号表，符号表的每个条目中
//包含与一个标识符相关的信息，比如它的字符串，它的类型，它的存储位置，
//和其他相关信息。

#include "parser.h"
#include "stdio.h"
#include "stdlib.h"

	
//初始化语法分析器
void parser_init(parser_rc_t *rc, const char *file_name)
{
	rc->file_name = file_name;
	scanner_rc_t *scanner = (scanner_rc_t *)malloc(sizeof(scanner_rc_t));
	scanner_open_file(scanner,rc->file_name);
	rc->scanner_rc = scanner;
}
//
void parser_syntax_error(parser_rc_t *rc, const char *msg)
{
	fprintf(stderr,"Line %d,Unexcepted token [%s]\n",scanner_get_curr_line(rc->scanner_rc),token_get_name(rc->token.t));
	if (msg)
	{
		fprintf(stderr,"Detail:%s\n",msg);;
	}
	exit(-1);
}
//
tree_node_t *parser_block(parser_rc_t *rc)
{
	tree_node_t *tree;
	return tree;
}
//
tree_node_t * parser_parse(parser_rc_t *rc)
{
	//
	tree_node_t * tree;
	rc->token = scanner_get_next_token(rc->scanner_rc);
	
	//tree = pddarser_stmt_seq(rc);
	//deal the '#'
	if (rc->token.t == T_POUND)
	{
		//#include "a.h" #define A 30
		parser_match(rc,T_POUND);
		if (rc->token.t == T_INCLUDE)
		{
			parser_include(rc);
		}else if (rc->token.t == T_DEFINE)
		{
			parser_define(rc);
		} else {
			parser_syntax_error(rc,"error in the #define");
		}

	} else if (rc->token.t == T_ENUM)
	{
	  tree = parser_enum(rc);
	} else if (rc->token.t == T_STATE)
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
//parser the enum
tree_node_t *parser_enum(parser_rc_t *rc)
{
	return NULL;
}
//get the next token
void parser_match(parser_rc_t *rc, TokenType expected)
{
  if (rc->token.t == expected)
  {
    rc->token = scanner_get_next_token(rc->scanner_rc);
  } else {
    parser_syntax_error(rc,NULL);
  }
}

//parse the stmt
/*
unsigned a:b;
if
while

*/
tree_node_t *parser_stmt(parser_rc_t *rc)
{
  tree_node_t *t = NULL;
  switch(rc->token.t)
    {
    case T_SEMI:
      parser_match(rc,T_SEMI);
      break;
    case T_IF:
      parser_match(rc,T_IF);
      t = parser_if_stmt(rc);
      break;
    case T_WHILE:
      t = parser_while_stmt(rc);
      break;
    case T_DO:
      t = parser_do_stmt(rc);
      break;
    case T_ID:
      t = parser_assign_stmt(rc);
      break;
    case T_UNSIGNED:
      //unsigned ID:8,16,32.
      t = parser_unsigned_stmt(rc);
      break;
    default:
      parser_syntax_error(rc,NULL);
      break;
    }
  return t;
}
//parser_if_stmt rc
tree_node_t *parser_if_stmt(parser_rc_t *rc)
{
  tree_node_t *t = new_stmt_node(StmtType_If);
  parser_match(rc,T_IF);
  parser_match(rc,T_LP);
  t->childs[0] = parser_exp(rc);
  parser_match(rc,T_RP);
  t->childs[1] = parser_block(rc);
  if (rc->token.t == T_ELSE) {
    parser_match(rc,T_ELSE);
    t->childs[2] = parser_block(rc);
  }
  return t;
}
//parser_while_stmt(rc)
tree_node_t *parser_while_stmt(parser_rc_t *rc)
{
  tree_node_t *t = new_stmt_node(StmtType_While);
  parser_match(rc,T_WHILE);
  parser_match(rc,T_LP);
  t->childs[0] = parser_exp(rc);
  parser_match(rc,T_RP);
  t->childs[1] = parser_block(rc);
  return t;
}
//parser_do_stmt(rc)
tree_node_t *parser_do_stmt(parser_rc_t *rc)
{
  tree_node_t *t = new_stmt_node(StmtType_Do);
  parser_match(rc,T_DO);
  t->childs[0] = parser_block(rc);
  parser_match(rc,T_WHILE);
  parser_match(rc,T_LP);
  t->childs[1] = parser_exp(rc);
  parser_match(rc,T_RP);
  return t;
}
//parser_assign_stmt(rc)
tree_node_t *parser_assign_stmt(parser_rc_t *rc)
{
  tree_node_t *t = new_stmt_node(StmtType_Assign);
  return t;
}
//parser_unsigned_stmt(rc)
tree_node_t *parser_unsigned_stmt(parser_rc_t *rc)
{
  tree_node_t *t = new_stmt_node(StmtType_Decls);
  parser_match(rc,T_UNSIGNED);
  if (t!=0 && rc->token.t == T_ID){
    t->attr.name = (char *)malloc(strlen(rc->token.c)+1);
    memset(t->attr.name,0,strlen(rc->token.c)+1);
    memcpy(t->attr.name,rc->token.c,strlen(rc->token.c));
  }
  parser_match(rc,T_COLON);
  parser_match(rc,T_NUMBER);
  parser_match(rc,T_SEMI);
  return t;
}
//parser_include rc
tree_node_t *parser_include(parser_rc_t *rc)
{
  tree_node_t *t = new_include_node();
  parser_match(rc,T_POUND);
  parser_match(rc,T_INCLUDE);
  parser_match(rc,T_LITERAL);
  parser_match(rc,T_LITERAL);
  return t;
}
//parser_define rc
tree_node_t *parser_define(parser_rc_t *rc)
{
  tree_node_t *t = new_state_node();
  parser_match(rc,T_DEFINE);
  parser_match(rc,T_ID);
  t->childs[0] = parser_exp(rc);
  return t;
}

//parser_exp
tree_node_t *parser_exp(parser_rc_t *rc)
{
  tree_node_t *t = parser_simple_exp(rc);
  if (rc->token.t == T_LT
      ||rc->token.t == T_GT
      ||rc->token.t == T_LE
      ||rc->token.t == T_GE
      ||rc->token.t == T_EQ
      ||rc->token.t == T_NEQ)
    {
      tree_node_t *p = new_exp_node(ExpType_Op);
      if (p != NULL)
      {
	p->childs[0] = t;
	p->attr.op = rc->token.t;
	t = p;
      }
      parser_match(rc,rc->token.t);
      if (t != NULL)
      {
	t->childs[1] = parser_simple_exp(rc);
      }
    }
  return t;
}
//parser_simple_exp
tree_node_t *parser_simple_exp(parser_rc_t *rc)
{
  tree_node_t *t = parser_term(rc);
  while(rc->token.t == T_MINUS || rc->token.t == T_PLUS)
    {
      tree_node_t *p = new_exp_node(ExpType_Op);
      if (p!=NULL)
	{
	  p->childs[0] = t;
	  p->attr.op = rc->token.t;
	  t = p;
	  parser_match(rc,rc->token.t);
	  t->childs[1] = parser_term(rc);
	}
    }
}
//parser_term rc
tree_node_t *parser_term(parser_rc_t *rc)
{
  tree_node_t *t = parser_factor(rc);
  while(rc->token.t == T_MUL || rc->token.t == T_DIV || rc->token.t == T_MOD)
    {
      tree_node_t *p = new_exp_node(ExpType_Op);
      if (p!= NULL)
	{
	  p->childs[0] = t;
	  p->attr.op = rc->token.t;
	  t = p;
	  parser_match(rc,rc->token.t);
	  t->childs[1] = parser_factor(rc);
	}
    }
  return t;
}

//parser_factor(rc)
tree_node_t *parser_factor(parser_rc_t *rc)
{
  tree_node_t *t = NULL;
  switch (rc->token.t)
    {
    case T_NUMBER:
      t = new_exp_node(ExpType_Op);
      t->attr.val = atoi(rc->token.c);
      parser_match(rc,T_NUMBER);
      break;
    default:
      parser_syntax_error(rc,NULL);
      break;
    }
  return t;
}


//parse the stmt_seq
tree_node_t *parser_stmt_seq(parser_rc_t *rc)
{
  tree_node_t *t = parser_stmt(rc);
  tree_node_t *p = t;
  while(rc->token.t != T_DONE && rc->token.t != T_ERROR)
  {
    tree_node_t *q = NULL;
    if (rc->token.t != T_DONE){
      q = parser_stmt(rc);
      if (q != NULL)
	{
	  if (t == NULL) t = p = q;
	  else {
	    p->sibling = q;
	    p = q;
	  }
	}
    }
  }
}





//parse the cts:stc "AAA"|start {AAA}
tree_node_t *parser_substate(parser_rc_t *rc)
{
  tree_node_t *t = new_state_node();
  if (rc->token.t == T_CTS || rc->token.t == T_STC)
  {
    parser_match(rc,T_STC);
    parser_match(rc,T_REGEX);
    
    parser_match(rc,T_LC);
    t->childs[0] = parser_block(rc); //deal the block stmt_seq.
    parser_match(rc,T_RC);
  } else {
    t = parser_stmt_seq(rc);
  }
  return t;
}

tree_node_t *parser_state(parser_rc_t *rc)
{
  //to create a state node.
  tree_node_t *t = new_state_node();
  parser_match(rc,T_STATE);
  parser_match(rc,T_ID);
  parser_match(rc,T_LC);
  t->childs[0] = parser_substate(rc); //parser the block ,two structre
  parser_match(rc,T_RC);
  return t;
}
