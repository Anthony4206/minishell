#include <dirent.h>
#include <sys/types.h>

#include "executor.h"
#include "libft.h"

void    ft_expand_wildcard(char **cmd, char *wildcard, int pos)
{
    DIR             *dir;
    struct dirent   *sd;

    dir = opendir(".");
    sd = readdir(dir);
    if (dir == NULL)
    {
        printf("Error! Unable to open directory.\n");
        return ;
    }
    while (sd)
    {
		if (ft_apply_wildcard(wildcard, sd->d_name) > 0)
			ft_add_param(cmd, sd->d_name, pos);
        sd = readdir(dir);
    }
    closedir(dir);
}

void	ft_add_param(char **cmd, char *str, int pos)
{
	char	**new_cmd;
	int		i;

	i = -1;
	new_cmd = malloc((sizeof(char *)) * ft_strlen_tab(cmd) + 1);
	if (!new_cmd)
		return (NULL);
	while (++i < pos)
		new_cmd[i] = cmd[i];
	new_cmd[i] = ft_strdup(str);
	while (cmd[i])
		new_cmd[i + 1] = cmd[i++];
	free(cmd)
}

int	ft_apply_wildcard(char *wildcard, char *str)
{
	char	*part;
	int		i;
	int		j;

	i = 0;
	part = malloc(strlen(wildcard));
	if (!part)
		return (1);
/*	if (wildcard[0] != '*')
	{
		while (wildcard && wildcard[i] != '*')
		{
			if (wildcard[i] != str[i])
				 return (1);
			i++;
		}
	}*/
	while (wildcard[i])
	{
		if (wildcard[++i] == '*') 
			continue ;
		j = 0;
		while (wildcard[i] && wildcard[i] != '*')
			part[j] = wildcard[i + j++];
		part[j] = '\0';
		if (ft_strstr(str, part) == NULL)
			return (0);
		i += strlen(part);
	}
	free(part);
	return (1);
}
