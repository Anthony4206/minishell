#include <stdio.h> 
#include <unistd.h> 
#include "libft.h" 

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

int	built_echo(char **args)
{
	int		i;
	int		backslash;

	if (!args)
	{
		write(1, "\n", 1);
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
		ft_putstr(args[i]);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!backslash)
		write(1, "\n", 1);
	return (0);
}
