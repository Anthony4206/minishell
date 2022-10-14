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

t_ast_node	*ast_parse(t_token *lexer)
{
	t_token		*next;

	if (!lexer)
		return (NULL);
	next = ast_scanner_peek(lexer, TOK_AND | TOK_OR);
	if (next->type == TOK_STRING  || next->type == TOK_REDIR)
		return (ast_parse_command(next));
	else if (next->type == TOK_AND || next->type == TOK_OR)
		return (ast_parse_pair(lexer, next));
	return (ast_error_node_new("syntax error\n"));
}

t_ast_node	*ast_parse_command(t_token *lexer)
{
	t_token	*next;

	next = ast_scanner_next(lexer);
	return (ast_cmd_node_new(next));
}

t_ast_node	*ast_parse_pair(t_token *lexer, t_token *next)
{
	t_token		*tmp;
	t_ast_node	*left;
	t_ast_node	*right;

	tmp = lexer;
	tmp->next = 0;
	left = ast_parse(tmp);
	lexer = next;
	if (lexer->next)
		right = ast_parse(lexer->next);
	else
		return (ast_error_node_new("syntax error\n"));
	return (ast_pair_node_new(left, right, NODE_AND));
}
