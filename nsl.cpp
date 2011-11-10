#include "nsl.h"

int main(int argc, char **argv)
{
  if (argc < 2)exit(-1);
  parser_rc_t parser;
  parser_init(&parser,argv[1]);
  tree_node_t *t = parser_parse(&parser);
  parser_debug(&parser,tree);
}
