#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "libft.h"
#include "../close.h"
#include "tree.h"
#include "parse.h"
#include "parse_utils.h"
#include "parse_node.h"
#include "token_list_2.h"
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
	t_ast_node	*cmd;

	if (!lexer)
		return (NULL);
	cmd = ast_parse_line(&lexer);
	if (cmd->data.content.tok_list[0] || cmd->data.content.redirect[0])
		ast_peek(&lexer, (int[]){TOK_EOF}, 1);
	if (lexer->type != TOK_EOF)
	{
		printf("syntaxe error\n");
		return (NULL);
	}
	return (cmd);
}

t_ast_node	*ast_parse_line(t_token **lexer)
{
	t_ast_node	*cmd;

	cmd = ast_parse_pipe(lexer);
	if (cmd->data.content.tok_list[0] || cmd->data.content.redirect[0])
	{
		if (ast_peek(lexer, (int[]){TOK_AND, TOK_OR}, 2))
		{
			ast_scanner_next(lexer);
			if ((*lexer)->type == TOK_AND)
				cmd = ast_pair_node_new(cmd, ast_parse_line(lexer), NODE_AND);
			else
				cmd = ast_pair_node_new(cmd, ast_parse_line(lexer), NODE_OR);
		}
	}
	return (cmd);
}

t_ast_node	*ast_parse_pipe(t_token **lexer)
{
	t_ast_node	*cmd;
	t_ast_node	*new;

	if ((*lexer)->type == TOK_L_PARENTHESIS || ast_peek(lexer, (int[]){TOK_L_PARENTHESIS}, 1))
		return (ast_parse_parent(lexer));
	cmd = ast_cmd_node_new(lexer);
	if (cmd->data.content.tok_list[0] || cmd->data.content.redirect[0])
	{
		while (ast_peek(lexer, (int[]){TOK_PIPE}, 1))
		{
			ast_scanner_next(lexer);
			new = ast_cmd_node_new(lexer);
			ft_tok_add_back(&cmd, new);
		}
	}
	return (cmd);
}

t_ast_node	*ast_parse_parent(t_token **lexer)
{
	t_ast_node	*cmd;

	if ((*lexer)->type != TOK_L_PARENTHESIS)
		return (NULL);
	ast_scanner_next(lexer);
	cmd = ast_parse_line(lexer);
	if (!ast_peek(lexer, (int[]){TOK_R_PARENTHESIS}, 1))
	{
		return (NULL);
	}
	return (cmd);
}
