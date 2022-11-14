#include <stdio.h> 
#include <unistd.h> 
#include "libft.h" 

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
	if (!ft_strncmp(args[1], "-n\0", 3))
		return (1);
	if (!ft_strncmp(args[1], "-n ", 3))
	{
		backslash = 1;
		i += 3;
	}
	while (args[i])
	{
		ft_putstr(args[i]);
		i++;
	}
	if (!backslash)
		write(1, "\n", 1);
	return (0);
}
