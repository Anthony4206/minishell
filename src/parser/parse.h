#ifndef PARSE_H
# define PARSE_H

# include "tree.h"
# include "../lexer/lexer.h"

t_ast_node  *ast_parse(t_token *lexer);
t_ast_node	*ast_parse_command(t_token *lexer);
t_ast_node  *ast_parse_pair(t_token *lexer, t_token *next);

#endif
