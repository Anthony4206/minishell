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

t_ast_node	*ast_parse(t_token *lexer)
{
	t_ast_node	*cmd;

	if (!lexer)
		return (NULL);
	cmd = ast_parse_line(&lexer);
	if (cmd && (cmd->data.content.tok_list[0] || cmd->data.content.redirect[0]))
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
	if (cmd && (cmd->data.content.tok_list[0] || cmd->data.content.redirect[0]))
	{
		if (ast_peek(lexer, (int[]){TOK_AND, TOK_OR}, 2))
		{
			if ((*lexer)->type == TOK_AND)
			{
				if (ast_peek(lexer,
					(int[]){TOK_STRING, TOK_REDIR, TOK_L_PARENTHESIS}, 3))
					cmd = ast_pair_node_new(cmd, ast_parse_line(lexer), NODE_AND);
				else
					(*lexer)->next->type = TOK_ERROR;
			}
			else if ((*lexer)->type == TOK_OR)
			{
				if (ast_peek(lexer,
					(int[]){TOK_STRING, TOK_REDIR, TOK_L_PARENTHESIS}, 3))
					cmd = ast_pair_node_new(cmd, ast_parse_line(lexer), NODE_OR);
				else
					(*lexer)->next->type = TOK_ERROR;
			}
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
	if (cmd && (cmd->data.content.tok_list[0] || cmd->data.content.redirect[0]))
	{
		while (ast_peek(lexer, (int[]){TOK_PIPE}, 1))
		{
			if (ast_peek(lexer,
				(int[]){TOK_STRING, TOK_REDIR, TOK_L_PARENTHESIS}, 3))
			{
				new = ast_cmd_node_new(lexer);
				ft_tok_add_back(&cmd, new);
			}
			else
				(*lexer)->next->type = TOK_ERROR;
		}
	}
	return (cmd);
}

t_ast_node	*ast_parse_parent(t_token **lexer)
{
	t_ast_node	*cmd;

	if ((*lexer)->type != TOK_L_PARENTHESIS)
		return (NULL);
	if (!ast_peek(lexer,
		(int[]){TOK_STRING, TOK_REDIR, TOK_L_PARENTHESIS}, 3))		
		return (NULL);
	cmd = ast_parse_line(lexer);
	if (!ast_peek(lexer, (int[]){TOK_R_PARENTHESIS}, 1))
		return (NULL);
	return (cmd);
}
