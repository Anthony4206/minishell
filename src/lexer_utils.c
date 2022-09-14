/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <mmidon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:08:31 by mmidon            #+#    #+#             */
/*   Updated: 2022/09/14 15:14:58 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "lexer.h"
#include "structs.h"

int	ft_find_content(char *str, char *limiter, t_token *token)
{
	int		i;
	char	*tmp;
	char	*stock;
	
	i = 0;
	printf("str %s\n",str);
	while (str[i] && (ft_strchr(limiter, str[i] || i != 0)) == NULL)
		i++;
	if (i)
	{
		tmp = ft_calloc(sizeof(char), (i + 1));
		ft_strncpy(tmp, str, i);
		stock = ft_strjoin(token->content, tmp);
		if (ft_strlen(token->content) != 0 && token->type == TOK_STRING)
			free(token->content);
		token->content = ft_strdup(stock);
		free(stock);
		free(tmp);
	}
	if (token->string == STRING_UNQUOTED)
		return (i);
	return(i + 2);
}

char	*ft_add_string(char *str, t_token *token)
{
	int	i;

	i = 0;
	ft_parse_quotes(str);
	while(str[i] && !ft_isspace(str[i]) && !ft_strchr("<>()|", str[i]))
	{
		if (str[i] == '\'')
		{
			token->type = TOK_STRING;
			token->string = STRING_QUOTED;
			i += ft_find_content(str + i, "'", token);
		}		
		else if (str[i] == '"')
		{
			token->type = TOK_STRING;
			token->string = STRING_DQUOTED;
			i += ft_find_content(str + i, "\"", token);
		}	
		else
		{
			token->type = TOK_STRING;
			token->string = STRING_UNQUOTED;
			i += ft_find_content(str + i, "\"'<>()| \t\n\r\v\f", token);
		}
	}
	return (str + i);
}

char	*ft_add_two_char(char *str, t_token *token)
{
	if (ft_strncmp(str, "<<", 2) == 0)
		return (token->type = TOK_HERE_DOC, str + 2);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (token->type = TOK_INFILE_REDIR, str + 1);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (token->type = TOK_APP_OUT_REDIR, str + 2);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (token->type = TOK_OUTFILE_REDIR, str + 1);
	else if (ft_strncmp(str, "||", 2) == 0)
		return (token->type = TOK_OR, str + 2);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (token->type = TOK_PIPE, str + 1);
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (token->type = TOK_AND, str + 2);
	return (NULL);
}

char	*ft_add_caractere(char *str, t_token *token)
{
	if (str[0] == '(')
		return (token->type = TOK_L_PARENTHESIS, str + 1);
	else
		return (token->type = TOK_R_PARENTHESIS, str + 1);
}
