/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 06:08:39 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 15:26:03 by alevasse         ###   ########.fr       */
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

t_ast_node	*ast_parse_cmd(t_token **lexer)
{
	t_ast_node	*ret;
	t_ast_node	*cmd;
	int			i;

	i = -1;
	if (ast_peek(lexer, (int []){TOK_LP}, 1, 1))
		return (ast_parse_parent(lexer));
	if (ast_peek(lexer, (int []){TOK_AND, TOK_OR, TOK_PIPE, TOK_RP}, 4, 0))
		return (NULL);
	ret = ast_cmd_node();
	cmd = ret;
	ret = ast_parse_redir(ret, lexer);
	while (!ast_peek(lexer, (int []){TOK_AND, TOK_OR, TOK_PIPE, TOK_RP}, 4, 0))
	{
		if ((*lexer)->type == TOK_ADD && (*lexer)->next->type == TOK_EOF)
			break ;
		if (!ast_peek(lexer, (int []){TOK_STRING}, 1, 1))
			return (NULL);
		if ((*lexer)->type == TOK_STRING)
			cmd->data.cmd.tok_list[++i] = ft_strdup((*lexer)->content);
		if (ast_peek(lexer, (int []){TOK_EOF}, 1, 0))
			break ;
		ret = ast_parse_redir(ret, lexer);
	}
	return (cmd->data.cmd.tok_list[++i] = 0, ret);
}
