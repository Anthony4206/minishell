#include <stdio.h>
#include "libft.h"
#include "parse_node.h"
#include "parse_utils.h"
#include "../lexer/lexer.h"
#include "tree.h"

t_token	*ast_redir_peek(t_token *next)
{
	while (next->next)
	{
		if (next->type == TOK_REDIR)
			return (next);
		next = next->next;
	}
	return (next);
}

t_token	*ast_scanner_peek(t_token *next)
{
	while (next->next)
	{
		if (next->type == TOK_AND || next->type == TOK_OR || next->type == TOK_L_PARENTHESIS)
			return (next);
		next = next->next;
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

void	ft_show_list(t_token *lexer);

t_ast_node	*ast_cmd_node_new(t_token *lexer, t_ast_node *next)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->node_type = NODE_DATA;
	node->data.content.tok_list = ft_add_arg(lexer);
	if (!node->data.content.tok_list)
		return (ast_error_node_new("syntax error near redirection"));
	node->data.content.redirect = ft_add_redir(lexer);
	node->data.content.next = next;
	return (node);
}

t_ast_node	*ast_pair_node_new(t_ast_node *left, t_ast_node *right, t_node_type type)
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
