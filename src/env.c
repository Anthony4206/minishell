#include <stdio.h>
#include "libft.h"

void	built_env(char **env)
{
	int	i;

	i = 0;
	if (env)
	{
		while (env[i])
		{
			printf("%s\n", env[i]);
			i++;
		}
	}
}
