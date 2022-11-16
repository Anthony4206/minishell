#include <stdio.h> 
#include <unistd.h>

#include "libft.h" 
#include "../executor/executor.h"

static int ft_option(char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 0;
	while (arg[++i])
	{
		if (arg[i] != 'n')
			return (0);
	}
	return (1);
}

int	built_echo(char **args, t_fd *fds)
{
	int		i;
	int		backslash;

	if (!args || !args[1])
	{
		write(fds->fd[1], "\n", 1);
		return (1);
	}
	i = 1;
	backslash = 0;
	if (ft_option(args[1]))
	{
		i++;
		backslash = 1;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], fds->fd[1]);
		if (args[i + 1])
			write(fds->fd[1], " ", 1);
		i++;
	}
	if (!backslash)
		write(fds->fd[1], "\n", 1);
	return (0);
}
