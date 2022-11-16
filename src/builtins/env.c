#include <stdio.h>

#include "libft.h"
#include "../executor/executor.h"

//opt 1 = export
//opt 0 = env

void	built_env(char **env, int opt, t_fd *fds)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			if (opt)
			{
				ft_putstr_fd("declare -x ", fds->fd[1]);
				ft_putstr_fd(env[i], fds->fd[1]);
				ft_putstr_fd("\n", fds->fd[1]);
			}
			else if (ft_strchr(env[i], '=') || opt)
			{
				ft_putstr_fd(env[i], fds->fd[1]);
				if (!ft_strchr(env[i], '='))	
					ft_putstr_fd("=''", fds->fd[1]);
				ft_putstr_fd("\n", fds->fd[1]);
			}
			i++;
		}
	}
}
