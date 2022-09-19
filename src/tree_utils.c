#include <stdio.h>
#include <errno.h>

#include "lexer.h"
#include "libft.h"
#include "tree.h"
#include "close.h"

static void	ast_rec_add_node(t_ast_node *cur, t_ast_node *new)
{
	if(new->type == TOK_L_PARENTHESIS)
	{
		printf("left %s\n",new->node_content);
		if (!cur->left)
			cur->left = new;
		else
			ast_rec_add_node(cur->left, new);
	}
	else
	{
		printf("right %s\n",new->node_content);
		if (!cur->right)
			cur->right = new;
		else
			ast_rec_add_node(cur->right, new);
	}
}

static  t_ast_node *ast_create_node(int data_size, char *element, int type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
	{
		ft_return_err("malloc", strerror(errno));
		return (node);
	}
	node->node_content = malloc(sizeof(data_size));
	if (!node->node_content)
	{
		ft_return_err("malloc", strerror(errno));
		free (node);
		node = NULL;
		return (node);
	}
	ft_memcpy(node->node_content, element, data_size);
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	ast_add_node(t_tree *tree, char *element, int type)
{
	t_ast_node	*node;

	if (!tree)
		return (ft_return_err("tree", strerror(errno)));
	if (!element)
		return (ft_return_err("element", strerror(errno)));
	node = ast_create_node(tree->data_size, element, type);
	if (tree->root)
		ast_rec_add_node(tree->root, node);
	else
		tree->root = node;
	return (1);
}
