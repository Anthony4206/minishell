#ifndef TREE_H
# define TREE_H

# include <stdlib.h>

typedef struct s_ast_node
{
	int					type;
	char				*node_content;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_tree
{
	size_t				data_size;
	char				**env;
	t_ast_node			*root;
	t_ast_node			*ptr;
}						t_tree;

#endif
