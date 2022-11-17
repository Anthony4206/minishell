#ifndef BUILTIN_H
# define BUILTIN_H

#include "../lexer/lexer.h"
#include "../executor/executor.h"

int	    ft_is_builtin(char **arg, t_fd *fds, t_ctx *ctx);
int		ft_findchar(char *str, char c);

int		built_cd(char **dir, t_ctx *ctx);
int		built_pwd(t_fd *fds, t_ctx *ctx);
int		built_echo(char **args, t_fd *fds);
int		built_env(char **env, int opt, t_fd *fds);
int		built_exit(char **status);

int		built_export(char **exported, t_fd *fds, t_ctx *ctx);
int		built_unset(char **unseted, t_ctx *ctx);

#endif
