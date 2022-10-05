#ifndef PARSE_H
# define PARSE_H

# include "structs.h"
# include "tree.h"

/*typedef enum e_node
{
	NODE_INFILE_DIR = 1,
	NODE_OUTFILE_DIR,
	NODE_HEREDOC,
	NODE_APP_OUT_REDIR,
	NODE_OR,
	NODE_AND,
	NODE_PIPE,
	NODE_PARENTHESIS,
	NODE_DATA
}			t_node_type;*/

//int	ast_add_node(t_tree *tree, char *element, int type, t_token *lexer);
t_ast_node  *ast_cmd_node_new(char *str);
t_ast_node  *ast_pair_node_new(t_ast_node *left, t_ast_node *right, t_node_type type);
t_ast_node  *ast_error_node_new(char *msg);
t_ast_node  *ast_parse(t_token *lexer, t_token *next, t_token *ptr);
t_ast_node  *ast_parse_string(t_token *lexer);
t_ast_node  *ast_parse_pair(t_token *lexer, t_token *next, t_token *ptr);
t_ast_node  *ft_parse(t_token *lexer);

#endif
