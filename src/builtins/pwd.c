#include <stdio.h>
#include "libft.h"
#include "../lexer/lexer.h"
#include "../executor/executor.h"

void	built_pwd(t_fd *fds, t_ctx *ctx)
{
	int	i;

	i = -1;
	if (ctx->env)
	{
		while (ft_strncmp(ctx->env[++i], "PWD=", 4) && ctx->env[i]);
		ft_putstr_fd(ctx->env[i] + 4, fds->fd[1]);
		ft_putstr_fd("\n", fds->fd[1]);
	}
}
