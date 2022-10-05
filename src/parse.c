#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "libft.h"
#include "close.h"
#include "tree.h"
#include "parse.h"

/**
 *
<complete_cmd> ::=  <and_or> <newline>

<and_or>		::=  <pipeline> '&&' <and_or> 
				|	<pipeline> '||' <and_or>
				|	<pipeline>  

<pipeline>		::=  <command> '|' <pipeline>
					<command>

<command>		::=  <simple_cmd> 
				|	'(' <and_or> ')'

<simple_cmd>	::= <token_list> <redir_list> <token_list>
				|	<token_list> <redir_list>
				|	<token_list>

<redir_list>	::=	<redirect> <redir_list>
				|	<redirect>

<redirect>		::= '<' <token>
				| 	'>' <token>
				|	'<<' <token>
				|	'>>' <token>

<token_list>	::= <token> <token_list>
				|	EMPTY
 *
**/

t_token	*ast_scanner_peek(t_token *next)
{
	t_token	*ptr;

	if (next->next)
		ptr = next->next;
	else
		ptr = next;
	printf("%s\n", next->content);
	while (next->next)
	{
		next = next->next;
		printf("%s\n", next->content);
		if (next->type == TOK_AND)
			return (next);
	}
	return (ptr);
}

t_token	*ast_scanner_next(t_token *lexer)
{
	t_token	*ret;

	ret = lexer;
	lexer = lexer->next;
	return (ret);
}

t_ast_node	*ast_cmd_node_new(char *str)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->node_type = NODE_DATA;
	node->data.content = str;
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
	node->data.content = msg;
	return (node);
}

t_ast_node	*ast_parse(t_token *lexer, t_token *next, t_token *ptr)
{
	printf("entering PARSE\n");
	if (!lexer)
		return (NULL);
	ptr = next;
	next = ast_scanner_peek(lexer);
	if (next->type == TOK_STRING)
	{
		printf ("STRING\n");
		return (ast_parse_string(next));
	}
	else if (next->type == TOK_AND)
	{
		printf ("AND\n");
		return (ast_parse_pair(lexer, next, ptr));
	}
	return (ast_error_node_new("syntax error\n"));
}

t_ast_node	*ast_parse_string(t_token *lexer)
{
	t_token	*next;

	next = ast_scanner_next(lexer);
	return (ast_cmd_node_new(next->content));
}

t_ast_node	*ast_parse_pair(t_token *lexer, t_token *next, t_token *ptr)
{
	t_token	*part;
	t_token *tmp;
	t_ast_node	*left;
	t_ast_node	*right;

	part = lexer;
	tmp = part;
	while (tmp->next->type != TOK_AND)
		tmp = next;
	tmp->next = 0;
	tmp = part;
	left = ast_parse(tmp, next, ptr);
	lexer = next;
	right = ast_parse(lexer->next, next, ptr);
	return (ast_pair_node_new(left, right, NODE_AND));
}

t_ast_node	*ft_parse(t_token *lexer)
{
	t_token *next;
	t_token *ptr;
	t_ast_node	*ret;

	next = lexer;
	ptr = lexer;
	ret = ast_parse(lexer, next, ptr);
	return (ret);
}
