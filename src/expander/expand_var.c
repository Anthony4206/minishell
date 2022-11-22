/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:56:17 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/22 08:40:18 by mmidon           ###   ########.fr       */
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
	int		vars[4];

	vars[0] = 0;
	vars[1] = -1;
	vars[2] = 0;
	vars[3] = 0;
	while (cmd[vars[0]])
	{
		if (cmd[vars[0]] == '$' && cmd[vars[0] + 1] != '0'
			&& ft_isdigit(cmd[vars[0] + 1]))
			vars[0] += 2;
		if (cmd[vars[0]] == '"' && !vars[2])
			ft_quote(&vars[3]);
		if (cmd[vars[0]] == '\'' && !vars[3])
			ft_quote(&vars[2]);
		if (cmd[vars[0]] == '$' && !vars[2])
		{
			var = ft_find_var(cmd, &vars[0], &vars[1], env);
			if (var)
				ret = ft_join(ret, var, &vars[1]);
		}
		else
			ret[++vars[1]] = cmd[vars[0]++];
	}
	return (vars[1]);
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
