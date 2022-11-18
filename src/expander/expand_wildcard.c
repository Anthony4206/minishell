#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

#include "libft.h"
#include "expand_wildcard.h"
#include "../executor/executor.h"

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
            cmd = ft_add_param(cmd, sd->d_name, pos);
        sd = readdir(dir);
        if (wildcard != cmd[pos])
            cmd = ft_sup_param(cmd, wildcard);
    }
    closedir(dir);
}

void    ft_sup_param(char **cmd, char *wildcard)
{
    int     i;

    i = -1;
    if (!cmd)
        return (NULL);
    while (ft_strcmp(cmd[++i], wildcard))
        cmd[i] = cmd[i];
    free(cmd[i]);
    while (cmd[i++])
        cmd[i] = cmd[i - 1];
}

void    ft_add_param(char **cmd, char *str, int pos)
{
    int     i;

    i = -1;
    while (++i < pos)
        cmd[i + 1] = cmd[i];
    cmd[i] = ft_strdup(str);
    while (cmd[i++])
        cmd[i + 1] = cmd[i];
    cmd[i + 1] = ft_strdup("");
}

int ft_apply_wildcard(char *wildcard, char *str)
{
    char    *part;
    int     i;
    int     j;

    i = -1;
    part = malloc(sizeof(char) * strlen(wildcard));
    if (!part)
        return (1);
/*  if (wildcard[0] != '*')
    {
        while (wildcard && wildcard[i] != '*')
        {
            if (wildcard[i] != str[i])
                 return (1);
            i++;
        }
    }*/
    while (wildcard[++i])
    {
        if (wildcard[i] == '*') 
            continue ;
        j = 0;
        while (wildcard[i + j] && wildcard[i + j] != '*')
        {
            part[j] = wildcard[i + j];
            j++;
        }
        part[j] = '\0';
        if (ft_strstr(str, part) == NULL)
        {
            free(part);
            return (0);
        }
        i += ft_strlen(part);
    }
    free(part);
    return (1);
}
