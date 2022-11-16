#include <dirent.h>
#include <sys/types.h>
#include "libft.h"

void    ft_expand_wildcard(char **cmd)
{
    DIR             *dir;
    struct dirent   *sd;

    dir = opendir(".");
    if (dir == NULL)
    {
        printf("Error! Unable to open directory.\n");
        exit(1);
    }
    while ((sd = readdir(dir)) != NULL)
    {
        
        printf(">> %s\n", sd->d_name);
    }
    closedir(dir);
    return (0);
}
