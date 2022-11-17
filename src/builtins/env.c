/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 08:12:58 by mmidon            #+#    #+#             */
/*   Updated: 2022/11/17 14:12:37 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>

#include "libft.h"
#include "../executor/executor.h"

//opt 1 = export
//opt 0 = env

static void	ft_print_var(char *printed, t_fd *fds)
{
	int	i;
	int	cjunker_quotes;

	cjunker_quotes = 0;
	i = -1;
	ft_putstr_fd("declare -x ", fds->fd[1]);
	while (printed[++i])
	{
		write(fds->fd[1], &printed[i], 1);
		if (printed[i] == '=')
		{
			write(fds->fd[1], "\"", 1);
			cjunker_quotes = 1;
		}
	}
	if (cjunker_quotes)
		write(fds->fd[1], "\"", 1);
	write(fds->fd[1], "\n", 1);
}

static void	ft_export(char **env, t_fd *fds)
{
	int	ascii;
	int	i;

	ascii = 0;
	while (++ascii <= 127)
	{
		i = -1;
		while (env[++i])
		{
			if (env[i][0] == ascii)
				ft_print_var(env[i], fds);
		}
	}
}

int	built_env(char **env, int opt, t_fd *fds)
{
	int	i;

	i = 0;
	if (env)
	{
		if (opt)
		{
			ft_export(env, fds);
			return (0);
		}
		while (env[i])
		{
			if (ft_strchr(env[i], '=') || opt)
			{
				ft_putstr_fd(env[i], fds->fd[1]);
				if (!ft_strchr(env[i], '='))
					ft_putstr_fd("=''", fds->fd[1]);
				ft_putstr_fd("\n", fds->fd[1]);
			}
			i++;
		}
	}
	return (0);
}
