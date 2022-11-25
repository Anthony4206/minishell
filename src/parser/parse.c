/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 06:03:55 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 15:26:12 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>

#include "libft.h"
#include "../close.h"
#include "tree.h"
#include "parse.h"
#include "parse_utils.h"
#include "parse_node.h"
#include "../lexer/lexer.h"

t_prompt	g_prompt;

t_ast_node	*ast_parse(t_token *lexer)
{
	t_ast_node	*cmd;

	if (!lexer)
		return (NULL);
	cmd = ast_parse_line(&lexer);
	if (!ast_peek(&lexer, (int []){TOK_EOF}, 1, 0))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		return (0);
	}
	return (cmd);
}

t_ast_node	*ast_parse_line(t_token **lexer)
{
	t_ast_node	*cmd;

	cmd = ast_parse_pipe(lexer);
	if (cmd && ast_peek(lexer, (int []){TOK_AND}, 1, 0))
	{
		if ((*lexer)->next->next->type == TOK_STRING
			|| (*lexer)->next->next->type == TOK_REDIR
			|| (*lexer)->next->next->type == TOK_LP)
		{
			ast_scanner_next(lexer);
			cmd = ast_pair_node(cmd, ast_parse_line(lexer), NODE_AND);
		}
	}
	else if (cmd && ast_peek(lexer, (int []){TOK_OR}, 1, 0))
	{
		if ((*lexer)->next->next->type == TOK_STRING
			|| (*lexer)->next->next->type == TOK_REDIR
			|| (*lexer)->next->next->type == TOK_LP)
		{
			ast_scanner_next(lexer);
			cmd = ast_pair_node(cmd, ast_parse_line(lexer), NODE_OR);
		}
	}
	return (cmd);
}

t_ast_node	*ast_parse_pipe(t_token **lexer)
{
	t_ast_node	*cmd;

	cmd = ast_parse_cmd(lexer);
	if (cmd && ast_peek(lexer, (int []){TOK_PIPE}, 1, 0))
	{
		if ((*lexer)->next->next->type == TOK_STRING
			|| (*lexer)->next->next->type == TOK_REDIR
			|| (*lexer)->next->next->type == TOK_LP)
		{
			ast_scanner_next(lexer);
			cmd = ast_pair_node(cmd, ast_parse_pipe(lexer), NODE_PIPE);
		}
	}
	return (cmd);
}

t_ast_node	*ast_parse_redir(t_ast_node *cmd, t_token **lexer)
{
	int	token_type;

	while (ast_peek(lexer, (int []){TOK_REDIR}, 1, 0))
	{
		if ((*lexer)->next->next->type != TOK_STRING)
			return (cmd);
		ast_scanner_next(lexer);
		token_type = (*lexer)->redir;
		ast_scanner_next(lexer);
		if (token_type == REDIR_INFILE)
			cmd = ast_redir_node(cmd, (*lexer)->content, O_RDONLY, 0);
		else if (token_type == REDIR_OUTFILE)
			cmd = ast_redir_node(cmd, (*lexer)->content,
					O_WRONLY | O_CREAT | O_TRUNC, 1);
		else if (token_type == REDIR_APP_OUTFILE)
			cmd = ast_redir_node(cmd, (*lexer)->content,
					O_WRONLY | O_CREAT | O_APPEND, 1);
		else if (token_type == REDIR_HERE_DOC)
			cmd = ast_redir_node(cmd, (*lexer)->content, O_RDONLY, 2);
		(*lexer)->type = TOK_ADD;
	}
	return (cmd);
}

t_ast_node	*ast_parse_parent(t_token **lexer)
{
	t_ast_node	*cmd;

	if ((*lexer)->type != TOK_LP)
		return (NULL);
    g_prompt.block = 1;
	cmd = ast_parse_line(lexer);
	if (!ast_peek(lexer, (int []){TOK_RP}, 1, 1))
		return (cmd);
	ast_peek(lexer, (int []){TOK_AND, TOK_OR, TOK_PIPE}, 3, 0);
	cmd = ast_parse_redir(cmd, lexer);
    g_prompt.block = 0;
	return (cmd);
}
