#include <stdio.h>

#include "libft.h"
#include "builtin.h"

int	ft_is_builtin(char **arg, t_fd *fds, t_ctx *ctx)
{
	if (!ft_strncmp(arg[0], "cd", ft_strlen(arg[0])) && ft_strlen(arg[0]) == 2)
		built_cd(arg, ctx);
	else if (!ft_strncmp(arg[0], "echo", ft_strlen(arg[0]))
        && ft_strlen(arg[0]) == 4)
		built_echo(arg, fds);
	else if (!ft_strncmp(arg[0], "pwd", ft_strlen(arg[0]))
        && ft_strlen(arg[0]) == 3)
		built_pwd(fds, ctx);
	else if (!ft_strncmp(arg[0], "export", ft_strlen(arg[0]))
        && ft_strlen(arg[0]) == 6)
		built_export(arg, fds, ctx);
	else if (!ft_strncmp(arg[0], "unset", ft_strlen(arg[0]))
        && ft_strlen(arg[0]) == 5)
		built_unset(arg, ctx);
	else if (!ft_strncmp(arg[0], "env", ft_strlen(arg[0]))
        && ft_strlen(arg[0]) == 3)
		built_env(ctx->env, 0, fds);
	else if (!ft_strncmp(arg[0], "exit", ft_strlen(arg[0])) && ft_strlen(arg[0]) == 4)
		built_exit(arg);
	else	
		return (0);
	return (1);
}
