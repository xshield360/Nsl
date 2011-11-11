#include "inter.h"

/*
void write_banner(FILE *fp)
{
	printf("/*****************************************************\n");
	printf("*    created by nsl                                  *\n");
	printf("*                                                    *\n");
	printf("******************************************************\n\n\n");
}
*/
/*
int traversal_tree(tree_node_t *tree,FILE *fp)
{
	//
	printf("helloworld\n");
	return 1;
}
*/
int gentoc(tree_node_t *tree, char *filename)
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
	
	//write the banner to the file
	//write_banner(fp);
	//traversal the tree, then gen the c code to the file
	//traversal_tree(tree,fp);
	fclose(fp);
	return 1;
}
