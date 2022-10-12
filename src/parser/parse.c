#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "libft.h"
#include "../close.h"
#include "tree.h"
#include "parse.h"
#include "parse_utils.h"
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

/*int	ft_is_node(t_token *curr_tok, t_token_type tok_type, char *content)
{
	if (curr_tok == NULL)
		return (0);
	if (curr_tok->type == tok_type)
	{
		if (content)
		{
			
		}
		curr_tok = curr_tok->next;
		return (1);	
	}
	curr_tok = curr_tok->next;
	return (0);
}

t_command	*ast_parse_pipeline(t_token *lexer)
{
	t_command	*ret;

	ret = ft_lst_new();

	return (ret);
}*/

t_ast_node	*ast_parse(t_token *lexer)
{
	t_token		*next;

	if (!lexer)
		return (NULL);
	next = ast_scanner_peek(lexer, TOK_AND | TOK_OR);
	if (next->type == TOK_STRING  || next->type == TOK_REDIR)
		return (ast_parse_command(next));
	else if (next->type == TOK_AND)
		return (ast_parse_pair(lexer, next));
	return (ast_error_node_new("syntax error\n"));
}

t_ast_node	*ast_parse_command(t_token *lexer)
{
//	t_token	*next;
	char	**argv;
	char	**redir;

	argv = ft_add_arg(lexer);
	redir = ft_add_redir(lexer);
//	next = ast_scanner_next(lexer);
	return (ast_cmd_node_new(next->content));
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
