#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include "libft.h"
#include "lexer.h"
#include "parse.h"
#include "tree.h"
#include "close.h"

/*t_tree	*ast_new_tree(size_t data_size)
{
	t_tree	*tree;

	tree = NULL;
	if (!data_size)
	{
		ft_return_err("empty node", strerror(errno));
		return (tree);
	}
	tree = malloc(sizeof(t_tree));
	if (!tree)
	{
		ft_return_err("malloc", strerror(errno));
		return (tree);
	}
	tree->data_size = data_size;
	tree->root = NULL;
	return (tree);
}*/
