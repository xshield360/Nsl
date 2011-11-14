#ifndef __NSL_INTER_H__
#define __NSL_INTER_H__

#include "node.h"
#include "stdio.h"
#include "stdlib.h"
#include "symbol.h"

//gen the tree to c code output *filename
void write_banner();
int gentoc(symbol_t *symbol,tree_node_t *tree, char *filename);
int traversal_tree(symbol_t *symbol,tree_node_t *tree,FILE *fp);

#endif



