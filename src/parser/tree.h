#ifndef TREE_H
# define TREE_H

# include <stdlib.h>

typedef	struct s_ast_node t_ast_node;
typedef	struct s_pair_content t_pair_content;

typedef enum	 e_node
{
	NODE_OR = 1,
	NODE_AND,
	NODE_PIPE,
	NODE_DATA
}	t_node_type;

typedef struct s_cmd_content
{
	char		**tok_list;
	char		**redirect;
	t_ast_node	*next;
}				t_cmd_content;

typedef	struct s_pair_content
{
	t_ast_node	*left;
	t_ast_node	*right;
}				t_pair_content;

typedef union	u_node_content
{
	t_pair_content		pair;
	t_cmd_content		content;
}						t_node_content;

typedef struct s_ast_node
{
	t_node_type			node_type;
	t_node_content		data;
}						t_ast_node;

#endif
