/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:28:35 by mmidon            #+#    #+#             */
/*   Updated: 2022/11/22 09:40:39 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include "../lexer/lexer.h"
#include "builtin.h" 

int	ft_find_home_index(char **env)
{
	int	i;

	i = -1;
	while (ft_strncmp(env[++i], "HOME=", 5))
		;
	return (i);
}

int	ft_find_pwd_index(char **env, char *pwd, int size)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], pwd, size))
			return (i);
	}
	printf("minishell: cd: no pwd in env\n");
	return (-1);
}

char	*ft_new_pwd(void)
{
	char	*ret;

	ret = malloc(sizeof(char) * PATH_MAX);
	getcwd(ret, PATH_MAX);
	if (!ret || !ret[0])
		return (NULL);
	return (ret);
}

int	ft_change_pwd(char *pwd, char *oldpwd, t_ctx *ctx)
{
	int	i;
	int	j;

	i = ft_find_pwd_index(ctx->env, "PWD=", 4);
	j = ft_find_pwd_index(ctx->env, "OLDPWD=", 7);
	if (i < 0 || j < 0)
	{
		perror("Error :");
		return (1);
	}
	free(ctx->env[i]);
	ctx->env[i] = ft_strjoin("PWD=", pwd);
	free(ctx->env[j]);
	ctx->env[j] = ft_strjoin("OLDPWD=", oldpwd);
	return (0);
}

int	built_cd(char **dir, t_ctx *ctx)
{
	char	*new_pwd;
	char	*new_old_pwd;

	new_old_pwd = ft_new_pwd();
	if (!new_old_pwd)
	{
		perror("Error: ");
		return (1);
	}
	if (!dir[1])
		chdir(ctx->env[ft_find_home_index(ctx->env)] + 5);
	else if (chdir(dir[1]))
	{
		perror("Error: ");
		free(new_old_pwd);
		return (1);
	}
	new_pwd = ft_new_pwd();
	return (ft_change_pwd(new_pwd, new_old_pwd, ctx));
}
