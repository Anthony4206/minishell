#include "libft.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include "../lexer/lexer.h"

int	ft_find_pwd_index(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (!ft_strncmp(env[i], "PWD=", 4))
			return (i);
	}
	printf("minishell: cd: no pwd in env\n");
	return (-1);
}

int	built_cd(char **dir, t_ctx *ctx)
{
	int	i;
	char	*new_pwd;

	if (chdir(dir[1]))
	{
		perror("Error: ");
		return (1);
	}
	i = ft_find_pwd_index(ctx->env);
	if (i < 0)
		return (1);
	new_pwd = malloc(sizeof(char) * PATH_MAX);
	getcwd(new_pwd, PATH_MAX);
	if (!new_pwd[0])
		return (-1);
	free(ctx->env[i]);
	ctx->env[i] = ft_strjoin("PWD=", new_pwd);
	return (0);
}
