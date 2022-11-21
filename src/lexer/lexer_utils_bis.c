/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_bis.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 07:02:13 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 14:54:59 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "lexer.h"
#include "lexer_utils.h"

char	*ft_over_add_two_char(char *str, t_token *token, int type, int redir)
{
	if (ft_strncmp(str, "<<", 2) == 0 || ft_strncmp(str, ">>", 2) == 0)
	{
		token->type = type;
		token->redir = redir;
		return (str + 2);
	}
	else
	{
		token->type = type;
		token->redir = redir;
		return (str + 1);
	}
}

char	*ft_add_two_char(char *str, t_token *token)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (ft_over_add_two_char(str, token, TOK_REDIR, REDIR_HERE_DOC));
	else if (ft_strncmp(str, "<", 1) == 0)
		return (ft_over_add_two_char(str, token, TOK_REDIR, REDIR_INFILE));
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (ft_over_add_two_char(str, token, TOK_REDIR, REDIR_APP_OUTFILE));
	else if (ft_strncmp(str, ">", 1) == 0)
		return (ft_over_add_two_char(str, token, TOK_REDIR, REDIR_OUTFILE));
	else if (ft_strncmp(str, "||", 2) == 0)
		return (token->type = TOK_OR, str + 2);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (token->type = TOK_PIPE, str + 1);
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (token->type = TOK_AND, str + 2);
	return (NULL);
}
