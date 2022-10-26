#include <stdio.h>
#include "libft.h"
#include "parse_node.h"
#include "parse_utils.h"
#include "../lexer/lexer.h"
#include "tree.h"

int	ast_peek(t_token **lexer, int *tok, int size)
{
	int		i;
	t_token	*next;

	i = -1;
	next = *lexer;
	next = next->next;
	while (++i < size)
	{
		if ((int)next->type == tok[i])
		{
			*lexer = next;
			return (1);
		}
	}
	return (0);
}

void	ast_scanner_next(t_token **lexer)
{
	t_token	*next;

	next = *lexer;
	next = next->next;
	*lexer = next;
}

t_ast_node	*ast_cmd_node_new(t_token **lexer)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->node_type = NODE_DATA;
	node->data.content.tok_list = ft_add_arg(lexer);
	node->data.content.redirect = ft_add_redir(lexer);
	node->data.content.next = NULL;
	if (node->data.content.tok_list[0] || node->data.content.redirect[0])
		while (ast_peek(lexer, (int[]){TOK_STRING, TOK_REDIR}, 2))
			;
	return (node);
}

t_ast_node	*ast_pair_node_new
    (t_ast_node *left, t_ast_node *right, int type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->node_type = type;
	node->data.pair.left = left;
	node->data.pair.right = right;
	return (node);	
}
