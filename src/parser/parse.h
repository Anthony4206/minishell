#ifndef PARSE_H
# define PARSE_H

# include "tree.h"
# include "../lexer/lexer.h"

t_ast_node  *ast_cmd_node_new(char *str);
t_ast_node  *ast_pair_node_new(t_ast_node *left, t_ast_node *right, t_node_type type);
t_ast_node  *ast_error_node_new(char *msg);
t_ast_node  *ast_parse(t_token *lexer);
t_ast_node  *ast_parse_string(t_token *lexer);
t_ast_node  *ast_parse_pair(t_token *lexer, t_token *next);

#endif
