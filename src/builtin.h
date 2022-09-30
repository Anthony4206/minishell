#ifndef BUILTIN_H
# define BUILTIN_H

int		built_echo(char *args);
int		built_cd(char *dir);
void	built_exit(int	status);
void	built_pwd(char **env);
void	built_env(char **env);
char	**built_export(char   *exported, char **env);

#endif
