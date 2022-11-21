/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:56:17 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 12:42:04 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h> 
#include <dirent.h>
#include <stdio.h>

#include "libft.h"
#include "expand_wildcard.h"
#include "expand_utils.h"
#include "no_random_quote.h" 
#include "../lexer/lexer.h"

t_prompt	g_prompt;

char	*ft_find_var(char *cmd, int *i, int *j, char **env)
{
	char	*var;
	char	*ret;
	char	*tmp;

	tmp = NULL;
	var = ft_calloc(sizeof(char), ARG_MAX);
	ft_over_find_var(cmd, var, i);
	if (!ft_strcmp(var, "$") && ft_strlen(var) == 1)
		ret = ft_strdup(var);
	else
		ret = ft_env_chr(var, env);
	if (cmd[*i] && cmd[(*i)++ + 1] == '$')
	{
		free(var);
		var = ft_find_var(cmd, i, j, env);
		if (ret)
			tmp = ft_strdup(ret);
		free(ret);
		ret = ft_strjoin(tmp, var);
		free(tmp);
	}
	free(var);
	return (ret);
}

int	ft_over_expand_var(char *cmd, char **env, char *var, char *ret)
{
	int		i;
	int		j;
	int		quote;

	i = 0;
	j = -1;
	quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
			ft_quote(&quote);
		if (cmd[i] == '$' && !quote)
		{
			var = ft_find_var(cmd, &i, &j, env);
			if (var)
				ret = ft_join(ret, var, &j);
		}
		else
			ret[++j] = cmd[i++];
	}
	return (j);
}

char	*ft_expand_var(char *cmd, char **env)
{
	char	*var;
	char	*ret;
	int		add;

	var = NULL;
	if (!cmd || !cmd[0])
		return (NULL);
	ret = ft_calloc(sizeof(char), ARG_MAX);
	if (!ret)
		return (NULL);
	add = ft_over_expand_var(cmd, env, var, ret);
	return (ft_adjust(ret, add + 1));
}

void	ft_over_expand(t_ctx *ctx, char **cmd, int i)
{
	char	*cpy;

	if (ft_strchr(cmd[i], '$'))
	{
		cpy = ft_expand_var(cmd[i], ctx->env);
		free(cmd[i]);
		if (cpy && cpy[0] && ft_strlen(cpy))
			cmd[i] = ft_strdup(cpy);
		else
			cmd[i] = ft_strdup("");
		free(cpy);
	}
	if (ft_strchr(cmd[i], '"') || ft_strchr(cmd[i], '\''))
	{
		cpy = ft_no_random_quote(cmd[i]);
		free(cmd[i]);
		if (cpy && cpy[0])
			cmd[i] = ft_strdup(cpy);
		else
			cmd[i] = ft_strdup("");
		free(cpy);
	}
}

int	ft_expand(char **cmd, t_ctx *ctx)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		ft_over_expand(ctx, cmd, i);
		if (ft_strchr(cmd[i], '*'))
			ft_expand_wildcard(cmd, cmd[i], i);
	}
	return (0);
}
