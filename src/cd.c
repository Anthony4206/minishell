#include "libft.h"
#include <stdio.h>

int	built_cd(char *dir)
{
	if (chdir(dir))
	{
		perror("Error: ");
		return (1);
	}
	return (0);
}
