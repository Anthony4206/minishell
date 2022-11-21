/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:29:05 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 13:27:55 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

#include "libft.h"
#include "no_random_quote.h"
#include "expand_wildcard.h"
#include "wildcard_utils.h"
#include "../executor/executor.h"
#include "../executor/executor_utils.h"

void	ft_expand_wildcard(char **cmd, char *wildcard, int pos)
{
	DIR				*dir;
	struct dirent	*sd;
	int				i;

	i = 0;
	dir = opendir(".");
	if (dir == NULL)
	{
		printf("Error! Unable to open directory.\n");
		return ;
	}
	sd = readdir(dir);
	while (sd)
	{
		if (ft_apply_wildcard(wildcard, sd->d_name) > 0)
		{
			ft_add_param(cmd, sd->d_name, pos + i);
			i++;
		}
		sd = readdir(dir);
	}
	if (wildcard != cmd[pos])
		ft_sup_param(cmd, wildcard);
	closedir(dir);
}

void	ft_sup_param(char **cmd, char *wildcard)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen_tab(cmd);
	if (!cmd)
		return ;
	while (ft_strcmp(cmd[i], wildcard))
		i++;
	free(cmd[i]);
	while (i < len)
	{
		cmd[i] = cmd[i + 1];
		i++;
	}
	cmd[i] = NULL;
}

void	ft_add_param(char **cmd, char *str, int pos)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen_tab(cmd) + 1;
	if (!cmd)
		return ;
	cmd[len] = NULL;
	while (i < pos)
		i++;
	while (i < len - 1)
	{
		len--;
		cmd[len] = cmd[len - 1];
	}
	cmd[pos] = ft_strdup(str);
}

int	ft_apply_wildcard(char *wildcard, char *str)
{
	char	*part;
	int		ret;

	part = malloc(sizeof(char) * strlen(wildcard));
	if (!part)
		return (1);
	if (str[0] == '.')
		return (ft_return_free(part, 0));
	ret = ft_over_wildcard(wildcard, str, part);
	return (ret);
	return (ft_return_free(part, ret));
}
