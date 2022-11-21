/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:40:19 by mmidon            #+#    #+#             */
/*   Updated: 2022/11/21 12:40:21 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "libft.h"
#include "../lexer/lexer.h"
#include "../executor/executor.h"

int	built_pwd(t_fd *fds, t_ctx *ctx)
{
	int	i;

	i = -1;
	if (!ctx->env)
		return (1);
	else
	{
		while (ft_strncmp(ctx->env[++i], "PWD=", 4) && ctx->env[i])
			;
		ft_putstr_fd(ctx->env[i] + 4, fds->fd[1]);
		ft_putstr_fd("\n", fds->fd[1]);
	}
	return (0);
}
