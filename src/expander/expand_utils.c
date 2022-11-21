/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:54:48 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 12:42:05 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h> 
#include <dirent.h>
#include <stdio.h>

#include "libft.h"
#include "expand_wildcard.h"
#include "no_random_quote.h" 
#include "../lexer/lexer.h"

t_prompt	g_prompt;

char	*ft_adjust(char *cmd, int i)
{
	char	*ret;
	int		size;

	size = -1;
	while (cmd[++size])
		;
	ret = malloc(sizeof(char) * size + 1);
	size = -1;
	while (cmd[++size] && i--)
		ret[size] = cmd[size];
	ret[size++] = 0;
	free(cmd);
	return (ret);
}

char	*ft_env_chr(char *var, char **env)
{
	int		i;
	char	*ret;
	int		var_len;

	if (!ft_strcmp(var, "$?") && ft_strlen(var) == 2)
		return (ft_itoa(g_prompt.status));
	var_len = ft_strlen(var);
	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], var + 1, var_len - 1)
			&& env[i][var_len - 1] == '=')
		{
			ret = ft_strdup(env[i] + var_len);
			return (ret);
		}
	}
	return (NULL);
}

char	*ft_join(char *ret, char *var, int *j)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_strdup(ret);
	tmp2 = ft_strjoin(tmp, var);
	ft_strlcpy(ret, tmp2, ARG_MAX);
	free(tmp2);
	(*j) += ft_strlen(var);
	free(var);
	free(tmp);
	return (ret);
}

void	ft_quote(int *quote)
{
	if (*quote)
		*quote = 0;
	else
		*quote = 1;
}

void	ft_over_find_var(char *cmd, char *var, int *i)
{
	int		k;

	k = -1;
	while (cmd[*i + 1] && ((cmd[*i + 1] >= 'A' && cmd[*i + 1] <= 'Z')
			|| (cmd[*i + 1] >= 'a' && cmd[*i + 1] <= 'z')
			|| cmd[*i + 1] == '?' || cmd[*i + 1] == '_'))
		var[++k] = cmd[(*i)++];
	var[++k] = cmd[(*i)];
}
