#ifndef TREE_H
# define TREE_H

# include <stdlib.h>
# include "structs.h"

typedef	struct s_ast_node t_ast_node;
typedef	struct s_pair_content t_pair_content;
typedef char *t_string_content;

typedef enum	 e_node
{
	NODE_INFILE_DIR = 1,
	NODE_OUTFILE_DIR,
	NODE_HEREDOC,
	NODE_APP_OUT_REDIR,
	NODE_OR,
	NODE_AND,
	NODE_PIPE,
	NODE_PARENTHESIS,
	NODE_ERROR,
	NODE_DATA
}	t_node_type;

typedef	struct s_pair_content
{
	t_ast_node	*left;
	t_ast_node	*right;
}				t_pair_content;

typedef union	u_node_content
{
	t_pair_content		pair;
	t_string_content	content;
}						t_node_content;

typedef struct s_ast_node
{
	t_node_type			node_type;
	t_node_content		data;
}						t_ast_node;

/*typedef struct s_tree
{
	size_t				data_size;
	t_ast_node			*root;
}						t_tree;*/
#endif
