/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:24:21 by mmidon            #+#    #+#             */
/*   Updated: 2022/11/21 12:25:02 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdlib.h>

#include "libft.h"
#include "../lexer/lexer.h"

t_prompt	g_prompt;

int	built_exit(char **arg)
{
	int	i;

	ft_putstr_fd("exit\n", 2);
	i = -1;
	while (arg[1] && arg[1][++i])
	{
		if (!ft_isdigit(arg[1][i]))
		{
			ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
			exit(255);
		}
	}
	if (arg[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	g_prompt.status = ft_atoi(arg[1]);
	exit(g_prompt.status);
	return (0);
}
