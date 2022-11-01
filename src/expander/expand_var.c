#include "libft.h"
#include <dirent.h>

int	ft_expand(char **cmd, t_ctx *ctx)
{
	int	i;
	DIR *folder;
	struct dirent *entry;

	i = -1;
	folder = opendir(".");
	if (folder == NULL)
    {
        printf("Unable to read directory\n");
        return(1);
    }
	while(cmd[++i])
	{
		if(ft_strchr(cmd[i], '$'))
			cmd[i] = ft_expand_var(cmd[i], ctx->env);
		if (ft_strchr(cmd[i], '*'))
			cmd[i] = ft_expand_wildcard(cmd[i], entry, folder);
	}
	closedir(folder);
}
