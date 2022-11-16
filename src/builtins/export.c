#include <stdio.h> 

#include "libft.h"
#include "builtin.h"
#include "../lexer/lexer.h" 

int	ft_findchar(char *str, char c)
{
	int	i;

	i = -1;
	while(str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	return (i);
}

void	is_deja_vu(int *tmp, int *i, char *exported, char **env)
{
	while (env[++(*i)])
	{
		if (!ft_strncmp(exported, env[*i], ft_findchar(exported, '=')) && ft_findchar(exported, '=') == ft_findchar(env[*i], '='))
			*tmp = 1;
	}
	if (*tmp)
		(*i)--;
}

char	**ft_new_env(char **args, t_ctx *ctx, int j)
{
	int		i;
	int	tmp;
	char **new_env;

	i = -1;
	tmp = 0;
	is_deja_vu(&tmp, &i, args[j], ctx->env);
	new_env = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (ctx->env[++i])
	{
		if (tmp && !ft_strncmp(args[j], ctx->env[i], ft_findchar(args[j], '=')) && ft_findchar(ctx->env[i], '=') == ft_findchar(args[j], '='))
			new_env[i] = ft_strdup(args[j]);
		else
			new_env[i] = ft_strdup(ctx->env[i]);
		free(ctx->env[i]);
	}
	free(ctx->env);
	if (!tmp)
		new_env[i++] = ft_strdup(args[j]);
	new_env[i] = 0;
	return(new_env);
}

char	**built_export(char	**args, t_ctx *ctx)
{
	int		j;

	j = 0;
	if (!args[1])
	{
		built_env(ctx->env, 1);
		return (NULL);
	}
	while (args[++j])
		ctx->env = ft_new_env(args, ctx, j);
	return (NULL);
}
