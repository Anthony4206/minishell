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
    int             i;

    i = 0;
    dir = opendir(".");
    if (dir == NULL)
    {
        printf("Error! Unable to open directory.\n");
        return ;
    }
    sd = readdir(dir);
    while (sd)
    {
        if (ft_apply_wildcard(wildcard, sd->d_name) > 0)
        {
            ft_add_param(cmd, sd->d_name, pos + i);
            i++;
        }
        sd = readdir(dir);
    }
    if (wildcard != cmd[pos])
        ft_sup_param(cmd, wildcard);   
    closedir(dir);
}

void    ft_sup_param(char **cmd, char *wildcard)
{
    int i;
    int len;

    i = 0;
    len = ft_strlen_tab(cmd);
    if (!cmd)
        return ;
    while (ft_strcmp(cmd[i], wildcard))
        i++;
    free(cmd[i]);
    while (i < len)
    {
        cmd[i] = cmd[i + 1];
        i++;
    }
    cmd[i] = NULL;
}

void    ft_add_param(char **cmd, char *str, int pos)
{
    int     i;
    int     len;

    i = 0;
    len = ft_strlen_tab(cmd) + 1;
    if (!cmd)
        return ;
    cmd[len] = NULL;
    while (i < pos)
        i++;
    while (i < len - 1)
    {
        len--;
        cmd[len] = cmd[len - 1];
    }
    cmd[pos] = ft_strdup(str);
}

int ft_apply_wildcard(char *wildcard, char *str)
{
    char    *part;
    int     i;
    int     j;
    int     len;
    int     len_str;
    int     last;

    i = 0;
    last = 0;
    part = malloc(sizeof(char) * strlen(wildcard));
    if (!part)
        return (1);  
    if (str[0] == '.')
    {
        free(part);
        return (0);
    }
    if (wildcard[0] != '*')
    {
        while (wildcard[i] && wildcard[i] != '*')
        {
            if (wildcard[i] != str[i])
            {
                free(part);
                return (0);
            }
            i++;
        }
    }
    while (wildcard[i])
    {
        if (wildcard[i] == '*')
        {
            i++;
            continue ;
        }      
        j = 0;
        while (wildcard[i + j] && wildcard[i + j] != '*')
        {
            part[j] = wildcard[i + j];
            if (wildcard[i + j + 1] == '\0')
                last = 1;
            j++;
        }
        part[j] = '\0';
        len = ft_strlen(part);
        str = ft_strstr(str, part);
        if (last && str != NULL)
        {
            len_str = ft_strlen(str);
            while (len_str && len)
            {
                if (str[len_str - 1] != part[len - 1])
                {
                    free(part);
                    return (0) ;
                }
                len_str--;
                len--;
            }
            free(part);
            return (1);
        }
        if (str == NULL || (*(str + len) != '\0' && wildcard[i + len] != '*'))
        {
            free(part);
            return (0);
        }
        i += len;
    }
    free(part);
    return (1);
}
