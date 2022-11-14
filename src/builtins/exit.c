#include <stdlib.h>

#include "libft.h"

void	built_exit(char **arg)
{
    int status;
	/// A REVOIR
    status = ft_atoi(arg[1]);
	exit(status);
}
