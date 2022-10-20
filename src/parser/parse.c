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

	if (next->next->type != TOK_STRING)
		return (ast_error_node_new("syntax error in parenthesis"));
	end_of_parenth = ft_find_peer(next);
	while (next && next != end_of_parenth)
		next = next->next;
	if (next->next)
		next = next->next;
	tmp = lexer;
	while (tmp->next && tmp->next != end_of_parenth)
		tmp = tmp->next;
	tmp->next = 0;
	tmp = lexer;
	while (lexer != next)
	{
		if (lexer->type == TOK_STRING && lexer->next->type == TOK_L_PARENTHESIS)
			return (ast_error_node_new("syntax error near unexpected token `()'"));
		lexer = next;
	}
	left = ast_parse(tmp->next);
	free(tmp);
	free(end_of_parenth);
	if (lexer->next)
	{
		if (lexer->type == TOK_REDIR)
			right = ast_parse(lexer);
		else
			right = ast_parse(lexer->next);
	}
	else
		right = NULL;
	return (ast_pair_node_new(left, right, NODE_PARENTHESIS));
}

void ft_show_list(t_token *lexer);

t_ast_node	*ast_parse(t_token *lexer)
{
	t_token		*next;
	t_token	*head;
	head = lexer;
	while (lexer)
	{
		printf("lex		%p\n", lexer); 
		printf("content %s	%p\n", lexer->content, lexer->content);
		printf("type %d\n\n", lexer->type);
		lexer = lexer->next;
	}
	lexer = head;

/*	printf("PARSE\n"); 
	ft_show_list(lexer);
	printf("\n"); 
*/	if (!lexer)
		return (NULL);
	next = ast_scanner_peek(lexer);
	if (next->type == TOK_AND || next->type == TOK_OR)
		return (ast_parse_pair(lexer, next, next->type));
	else if (next->type == TOK_L_PARENTHESIS)
		return (ast_parse_parenth(lexer, next));
	else
		return (ast_parse_command(lexer));
	return (ast_error_node_new("syntax error 2\n"));
}

t_token	*ft_last_pipe(t_token *lexer)
{
	t_token	*ptr;
	
	ptr = NULL;
	while (lexer && lexer->next)
	{
		if (lexer->next->type == TOK_PIPE)
			ptr = lexer;
		lexer = lexer->next;
	}
	return (ptr);
}

t_ast_node	*ast_parse_command(t_token *lexer)
{
	t_token	*tmp;
	t_token	*head;
	t_token	*ptr;

	if (ft_peek(lexer, TOK_PIPE))
	{
		head = lexer;
		tmp = lexer;
		if (lexer->type == TOK_PIPE)
			return (ast_error_node_new("syntax error pipe\n"));
		ptr = ft_last_pipe(lexer);
		tmp = ptr->next;
		ptr->next = NULL;
		if (!tmp->next || !(tmp->next->type == TOK_STRING || tmp->next->type == TOK_REDIR || tmp->next->type == TOK_L_PARENTHESIS))
			return (ast_error_node_new("syntax error pipe2\n"));
		ptr = tmp->next;
		free(tmp);
		lexer = head;
		return (ast_cmd_node_new(ptr, ast_parse_command(lexer), NODE_PIPE));
	}
	return (ast_cmd_node_new(lexer, NULL, 0));
}

t_ast_node	*ast_parse_pair(t_token *lexer, t_token *next, int type)
{
	t_token		*tmp;
	t_ast_node	*left;
	t_ast_node	*right;

	tmp = lexer;
	tmp = ft_find_pair(tmp);
	tmp->next = 0;
	left = ast_parse(lexer);
	lexer = next;
	if (lexer->next)
	{
		right = ast_parse(lexer->next);
		free(lexer);
	}
	else
	{
		free(lexer);
		return (ast_error_node_new("syntax error 3\n"));
	}
	if (type == TOK_AND)
		type = NODE_AND;
	if (type == TOK_OR)
		type = NODE_OR;
	return (ast_pair_node_new(left, right, type));
}
