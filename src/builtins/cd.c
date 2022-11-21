#include "libft.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include "../lexer/lexer.h"
#include "builtin.h" 
int ft_find_home_index(char **env)
{
    int i;
    i = -1;
    while (ft_strncmp(env[++i], "HOME=", 5))
        ;
    return (i);
}
int ft_find_pwd_index(char **env, char *pwd,int size)
{
    int i;
    i = -1;
    while (env[++i])
    {
        if (!ft_strncmp(env[i], pwd, size))
            return (i);
    }
    printf("minishell: cd: no pwd in env\n");
    return (-1);
}
int built_cd(char **dir, t_ctx *ctx)
{
    int i;
    int j;
    char    *new_pwd;
    char    *new_old_pwd;
    j = ft_find_pwd_index(ctx->env, "OLDPWD=", 7);
    if (j < 0)
        return (-1);
    new_old_pwd = malloc(sizeof(char) * PATH_MAX);
    getcwd(new_old_pwd, PATH_MAX);
    if (!new_old_pwd || !new_old_pwd[0])
        return (-1);
    free(ctx->env[j]);
    ctx->env[j] = ft_strjoin("OLDPWD=", new_old_pwd);
    if (!dir[1])
        chdir(ctx->env[ft_find_home_index(ctx->env)] + 5);
    else if (chdir(dir[1]))
    {
        perror("Error: ");
        return (1);
    }
    i = ft_find_pwd_index(ctx->env, "PWD=", 4);
    if (i < 0)
        return (1);
    new_pwd = malloc(sizeof(char) * PATH_MAX);
    getcwd(new_pwd, PATH_MAX);
    if (!new_pwd || !new_pwd[0])
        return (-1);
    free(ctx->env[i]);
    ctx->env[i] = ft_strjoin("PWD=", new_pwd);
    free(new_pwd);
    free(new_old_pwd);
    return (0);
}