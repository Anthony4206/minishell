/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:45:43 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/24 08:05:37 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "libft.h"

static char	**ft_envp_path(char **envp)
{
	char	**ret;
	char	*envp_path;
	int		i;

	i = -1;
	while (envp[++i])
	{
		envp_path = ft_strnstr(envp[i], "PATH=", 5);
		if (envp_path)
		{
			envp_path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			break ;
		}
	}
	ret = ft_split(envp_path, ':');
	free(envp_path);
	return (ret);
}

void	ft_build_paths(char **paths)
{
	char	*tmp;
	int		i;

	i = -1;
	while (paths[++i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
	}
}

char	*ft_chr_path(char *cmd, char **envp)
{
	char	**paths;
	char	*exec_path;
	int		i;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	paths = ft_envp_path(envp);
	if (!paths)
		return (NULL);
	ft_build_paths(paths);
	i = -1;
	while (paths[++i])
	{
		exec_path = ft_strjoin(paths[i], cmd);
		if (access(exec_path, F_OK | X_OK) == 0)
			return (ft_free_tab(paths), exec_path);
		free(exec_path);
	}
	return (ft_free_tab(paths), NULL);
}
