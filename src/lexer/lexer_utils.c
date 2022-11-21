/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:08:31 by mmidon            #+#    #+#             */
/*   Updated: 2022/11/21 08:00:04 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "libft.h"
#include "lexer.h"
#include "lexer_utils.h"

int	ft_find_content(char *str, char *limiter, t_token *token)
{
	int		i;
	char	*tmp;
	char	*stock;

	i = 0;
	while (str[i] && (ft_strchr(limiter, str[i]) == NULL || i == 0)
		&& ft_strncmp(str + i, "&&", 2))
		i++;
	if (str[i] == '\'' || str[i] == '"')
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
	return (i);
}

void	ft_over_string(char *str, t_token *token, int *i)
{
	if (str[*i] == '\'')
	{
		token->type = TOK_STRING;
		token->string = STRING_QUOTED;
		*i += ft_find_content(str + *i, "'", token);
	}		
	else if (str[*i] == '"')
	{
		token->type = TOK_STRING;
		token->string = STRING_DQUOTED;
		*i += ft_find_content(str + *i, "\"", token);
	}
	else
	{
		token->type = TOK_STRING;
		token->string = STRING_UNQUOTED;
		*i += ft_find_content(str + *i, "\"'<>()&| \t\n\r\v\f", token);
	}
}

char	*ft_add_string(char *str, t_token *token)
{
	int	i;

	i = ft_parse_quotes(str);
	if (i % 2)
		return (str + i);
	i = 0;
	while (str[i] && !ft_isspace(str[i]) && !ft_strchr("<>()|", str[i])
		&& ft_strncmp(str + i, "&&", 2))
		ft_over_string(str, token, &i);
	return (str + i);
}

char	*ft_add_caractere(char *str, t_token *token)
{
	if (str[0] == '(')
		return (token->type = TOK_LP, str + 1);
	else
		return (token->type = TOK_RP, str + 1);
}
