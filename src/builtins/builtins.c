#include "libft.h"
#include "../context.h"
#include "builtin.h"

int	ft_is_builtin(char **arg, char **env)
{
	if (!ft_strncmp(arg[0], "cd", ft_strlen(arg[0])) && ft_strlen(arg[0]) == 2)
		built_cd(arg, env);
	else if (!ft_strncmp(arg[0], "echo", ft_strlen(arg[0])) && ft_strlen(arg[0]) == 4)
		built_echo(arg);
	else if (!ft_strncmp(arg[0], "pwd", ft_strlen(arg[0])) && ft_strlen(arg[0]) == 3)
		built_pwd(env);
	else if (!ft_strncmp(arg[0], "export", ft_strlen(arg[0])) && ft_strlen(arg[0]) == 6)
		built_export(arg, env);
	else if (!ft_strncmp(arg[0], "unset", ft_strlen(arg[0])) && ft_strlen(arg[0]) == 5)
		env = built_unset(arg, env);
	else if (!ft_strncmp(arg[0], "env", ft_strlen(arg[0])) && ft_strlen(arg[0]) == 3)
		env = built_env(env, 0); // revoir opts
	else if (!ft_strncmp(arg[0], "exit", ft_strlen(arg[0])) && ft_strlen(arg[0]) == 4)
		built_exit(arg);
	else	
		return (0);
	return (1);
}
