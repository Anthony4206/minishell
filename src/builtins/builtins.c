/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:26:05 by mmidon            #+#    #+#             */
/*   Updated: 2022/11/21 12:27:57 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

#include "libft.h"
#include "builtin.h"

t_prompt	g_prompt;

int	ft_is_builtin(char **arg, t_fd *fds, t_ctx *ctx)
{
	g_prompt.status = 0;
	if (!ft_strncmp(arg[0], "cd", ft_strlen(arg[0])) && ft_strlen(arg[0]) == 2)
		g_prompt.status = built_cd(arg, ctx);
	else if (!ft_strncmp(arg[0], "echo", ft_strlen(arg[0]))
		&& ft_strlen(arg[0]) == 4)
		g_prompt.status = built_echo(arg, fds);
	else if (!ft_strncmp(arg[0], "pwd", ft_strlen(arg[0]))
		&& ft_strlen(arg[0]) == 3)
		g_prompt.status = built_pwd(fds, ctx);
	else if (!ft_strncmp(arg[0], "export", ft_strlen(arg[0]))
		&& ft_strlen(arg[0]) == 6)
		g_prompt.status = built_export(arg, fds, ctx);
	else if (!ft_strncmp(arg[0], "unset", ft_strlen(arg[0]))
		&& ft_strlen(arg[0]) == 5)
		g_prompt.status = built_unset(arg, ctx);
	else if (!ft_strncmp(arg[0], "env", ft_strlen(arg[0]))
		&& ft_strlen(arg[0]) == 3)
		g_prompt.status = built_env(ctx->env, 0, fds, arg);
	else if (!ft_strncmp(arg[0], "exit", ft_strlen(arg[0]))
		&& ft_strlen(arg[0]) == 4)
		g_prompt.status = built_exit(arg);
	else
		return (g_prompt.status);
	return (2);
}
