#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "libft.h"
#include "../close.h"
#include "tree.h"
#include "parse.h"
#include "parse_utils.h"
#include "parse_node.h"
#include "../lexer/lexer.h"
#include "../lexer/parenthesis.h" 

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

int	ft_peek(t_token *lexer, t_token_type tok)
{
	while (lexer && lexer->type != TOK_AND && lexer->type != TOK_OR)
	{
		if (lexer->type == tok)
			return (1);
		lexer = lexer->next;
	}
	return (0);
}

t_ast_node	*ast_parse_parenth(t_token *lexer, t_token *next)
{
	t_token		*end_of_parenth;
	t_token		*tmp;
	t_ast_node	*left;
	t_ast_node	*right;

	if (next->next->type == TOK_R_PARENTHESIS)
		return (ast_error_node_new("syntax error near unexpected token `)'"));
	end_of_parenth = ft_find_peer(next);
	while (next && next != end_of_parenth)
		next = next->next;
	if (next->next)
		next = next->next;
	tmp = lexer;
	while (tmp->next && tmp->next != end_of_parenth)
		tmp = tmp->next;
	tmp->next = 0;
	tmp = lexer->next;
	while (lexer != next)
	{
		if (lexer->type == TOK_STRING && lexer->next->type == TOK_L_PARENTHESIS)
			return (ast_error_node_new("syntax error near unexpected token `()'"));
		lexer = next;
	}
	left = ast_parse(tmp);
	if (lexer->next)
	{
		if (lexer->type == TOK_REDIR)
			right = ast_parse(lexer);
		else
			right = ast_parse(lexer->next);
	}
	else
		right = NULL;
	return (ast_pair_node_new(left, right, NODE_AND));
}

void ft_show_list(t_token *lexer);

t_ast_node	*ast_parse(t_token *lexer)
{
	t_token		*next;

	if (!lexer)
		return (NULL);
	next = ast_scanner_peek(lexer);
	if (next->type == TOK_AND || next->type == TOK_OR)
		return (ast_parse_pair(lexer, next));
	else if (next->type == TOK_L_PARENTHESIS)
		return (ast_parse_parenth(lexer, next));
	else
	{
		next = ast_redir_peek(next);
		if (next)
			return(ast_parse_command(lexer));
	}
	return (ast_error_node_new("syntax error 2\n"));
}

t_ast_node	*ast_parse_command(t_token *lexer)
{
	t_token	*tmp;
	//t_token	*next;
	t_token	*head;

	if (ft_peek(lexer, TOK_PIPE))
	{
		head = lexer;
		tmp = lexer;
		while (lexer->next && lexer->next->type != TOK_PIPE)
			lexer = lexer->next;
		tmp = lexer->next;
		lexer->next = 0;
		lexer = head;
		return (ast_cmd_node_new(tmp->next, ast_parse_command(lexer)));
	}
	return (ast_cmd_node_new(lexer, NULL));
}

t_ast_node	*ast_parse_pair(t_token *lexer, t_token *next)
{
	t_token		*tmp;
	t_ast_node	*left;
	t_ast_node	*right;

	tmp = lexer;
	while (tmp && !ft_is_pair(tmp->next->type))
		tmp = tmp->next;
	tmp->next = 0;
	left = ast_parse(lexer);
	lexer = next;
	if (lexer->next)
		right = ast_parse(lexer->next);
	else
		return (ast_error_node_new("syntax error 3\n"));
	return (ast_pair_node_new(left, right, NODE_AND));
}
