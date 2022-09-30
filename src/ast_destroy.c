#include <errno.h>

#include "libft.h"
#include "close.h"
#include "tree.h"
#include "ast_destroy.h"

static void	ast_destroy_node(t_ast_node *node)
{
	if (node->node_content)
		free(node->node_content);
	free(node);
}

static void	ast_rec_destroy(t_ast_node *cur)
{
	if (cur->left)
		ast_rec_destroy(cur->left);
	if (cur->right)
		ast_rec_destroy(cur->right);
	ast_destroy_node(cur);
}

int	ast_destroy(t_tree *tree)
{
	if (!tree)
		return (ft_return_err("empty tree", strerror(errno)));
	if (tree->root)
		ast_rec_destroy(tree->root);
	free(tree);
	return (1);
}
