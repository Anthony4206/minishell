#ifndef BUILTIN_H
# define BUILTIN_H

#include "../lexer/lexer.h"

int	    ft_is_builtin(char **arg, t_ctx *ctx);
int		ft_findchar(char *str, char c);
int		built_echo(char **args);
int		built_cd(char **dir, t_ctx *ctx);
void	built_exit(char **status);
void	built_pwd(char **env);
void	built_env(char **env, int opt);
char	**built_export(char **exported, t_ctx *ctx);
char	**built_unset(char **unseted, t_ctx *ctx);

#endif
