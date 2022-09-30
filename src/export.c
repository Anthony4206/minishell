#include "libft.h"
#include <stdio.h> 

char	**built_export(char	*exported, char	**env)
{
	int	i;
	char	**new_env;

	i = 0;
	while (env[i++]);
	new_env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (env[++i])
	{
		new_env[i] = ft_strdup(env[i]);
		free(env[i]);
	}
	free(env);
	new_env[i] = ft_strdup(exported);
	new_env[++i] = 0;
	return (new_env);
}
