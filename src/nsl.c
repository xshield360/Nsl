#include "nsl.h"

void usage()
{
	printf("nsl: missing INPUT or OUTPUT\n");
	printf("Usage: nsl [INPUT] [OUTPUT]\n");
	printf("\n");
}
int  main(int argc, char **argv)
{
	if (argc < 3)
	{
		usage();
		exit(-1);
	}
	parser_rc_t parser;
	symbol_t *symbol;
	parser_init(&parser,argv[1]);

	tree_node_t *tree = parser_program(&parser);
	symbol = parser.symbol;
	gentoc(symbol,tree,argv[2]);
}
