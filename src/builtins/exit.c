#include <stdlib.h>

#include "libft.h"
#include "../lexer/lexer.h"

t_prompt	g_prompt;

int	built_exit(char **arg)
{
	ft_putstr_fd("exit\n",2);
	if (arg[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
    g_prompt.status = ft_atoi(arg[1]);
	exit(g_prompt.status);
	return (0);
}
