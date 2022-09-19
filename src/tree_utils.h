#ifndef TREE_UTILS_H
# define TREE_UTILS_H

# include <stdlib.h>

typedef struct s_ast_node
{
	int			type;
	char		*node_content;
	s_ast_node	*left;
	s_ast_node	*right;
}				t_ast_node;

typedef struct s_tree
{
    size_t      data;
    t_ast_node  *root;   
}               t_tree;

#endif