#include "inter.h"


void write_banner(FILE *fp)
{
	fprintf(fp,"/*****************************************************\n");
	fprintf(fp,"*    created by nsl                                  *\n");
	fprintf(fp,"*                                                    *\n");
	fprintf(fp,"******************************************************\n\n\n");
}


int traversal_tree(symbol_t *symbol,tree_node_t *tree,FILE *fp)
{
   
	if (tree == NULL)
	{
		fprintf(fp,"Error in traversal_tree,There is no AST\n");
		return 0;
	}
	tree_node_t *p;
	p = tree;
	
	if (p->node_type == NodeType_Header)
	{
		//the header about 
		if (p->type.header == HeaderType_Include)
		{
			
			//do the include
			int h = p->attr;
			fprintf(fp,"#include \"%s\"\n",symbol->IncludeListHash[h]->name);
			//printf("#include \"%s\"\n",symbol->IncludeListHash[h]->name);
		}
	} else if (p->node_type == NodeType_Stmt)
	{
		//the decl
		if (p->type.stmt == StmtType_Decl)
		{
			int h = p->attr;
			int type;
			char *name;
			type = symbol->DeclListHash[h]->type;
			name = symbol->DeclListHash[h]->name;
			fprintf(fp,"unsigned ");
			if (type == 8){
				fprintf(fp,"char ");
			} else if (type == 16)
			{
				fprintf(fp,"short ");
			} else if (type == 32){
					fprintf(fp,"int ");
			} else {
				printf("Wrong in gentoc,number must be 8,16,32\n");
				exit(0);
			}
			fprintf(fp,"%s;\n",name);
		}
	}

	if(p->sibling != NULL){
		p = p->sibling;
		traversal_tree(symbol,p,fp);
	} else {
		fprintf(fp,"//end\n");
	}
	return 1;
}

int gentoc(symbol_t *symbol,tree_node_t *tree, char *filename)
{
	// the banner
	// parser the tree ,then gen it into c code.
	FILE *fp;
	if (tree == NULL)
	{
		printf("error in the gentoc, there is no tree_node_t struct\n");
		return 0;
	}
	if (filename == NULL)
	{
		printf("error int the gentoc, there is no filename\n");
		return 0;
	}
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		printf("file open error, the file may be not exist\n");
		return 0;
	}
	//write the banner to the file
	write_banner(fp);
	//traversal the tree, then gen the c code to the file
	traversal_tree(symbol,tree,fp);
	fclose(fp);
	return 1;
}
