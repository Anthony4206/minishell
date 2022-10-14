#include <stdio.h>
#include "libft.h"
#include "parse_node.h"
#include "parse_utils.h"
#include "../lexer/lexer.h"
#include "tree.h"

t_token	*ast_scanner_peek(t_token *next, t_token_type tok)
{
	while (next->next)
	{
		next = next->next;
		if (next->type == tok)
			return (next);
	}
	return (next);
}

t_token	*ast_scanner_next(t_token *lexer)
{
	t_token	*ret;

	ret = lexer;
	lexer = lexer->next;
	return (ret);
}

t_ast_node	*ast_cmd_node_new(t_token *lexer)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->node_type = NODE_DATA;
	node->data.content.tok_list = ft_add_arg(lexer);
	node->data.content.redirect = ft_add_redir(lexer);
	return (node);
}

t_ast_node	*ast_pair_node_new
    (t_ast_node *left, t_ast_node *right, t_node_type type)
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

t_ast_node	*ast_error_node_new(char *msg)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->node_type = NODE_ERROR;
	node->data.error.msg = msg;
	return (node);
}
