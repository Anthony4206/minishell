#include <stdio.h> 
#include "libft.h"
#include "../parser/tree.h"

int ft_strlen_tab(char **tab)
{
    int i;
    
    i = -1;
    while (tab[++i]);
    return (i);
}


void    ft_free_tree(t_ast_node *tree)
{
    if (tree->node_type == NODE_AND || tree->node_type == NODE_OR
        || tree->node_type == NODE_PARENTHESIS)
    {
        ft_free_tree(tree->data.pair.left);
        if (tree->data.pair.right)
			ft_free_tree(tree->data.pair.right);
//        printf("to be freed [pair] %p\n", tree); 
        free(tree);
    }
    else if (tree->node_type == NODE_DATA || tree->node_type == NODE_PIPE)
    {
        if (tree->data.content.next)
            ft_free_tree(tree->data.content.next);
        ft_free_n_tab(tree->data.content.tok_list, ft_strlen_tab(tree->data.content.tok_list));
        ft_free_n_tab(tree->data.content.redirect, ft_strlen_tab(tree->data.content.redirect));
//        printf("to be freed [data] %p\n", tree); 
		free(tree);
    }
	else
	{
//        printf("to be freed [error] %p\n", tree);
		//free(tree->data.error.msg);
		free(tree);
	}
}
