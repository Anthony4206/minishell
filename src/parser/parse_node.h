#ifndef PARSE_NODE_H
# define PARSE_NODE_H

# include "tree.h"
# include "../lexer/lexer.h"

t_token	    *ast_scanner_peek(t_token *next);
t_token		*ast_redir_peek(t_token *next);
t_token	    *ast_scanner_next(t_token *lexer);
t_ast_node	*ast_cmd_node_new(t_token *lexer, t_ast_node *next);
t_ast_node	*ast_pair_node_new(t_ast_node *left, t_ast_node *right, t_node_type type);
t_ast_node	*ast_error_node_new(char *msg);

#endif
