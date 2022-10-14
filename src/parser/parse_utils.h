#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

char    *ft_type_redir(int type);
char    **ft_init_redir(t_token *lexer, char **redir);
char    **ft_add_redir(t_token *lexer);
char    **ft_init_arg(t_token *lexer, char **arg);
char    **ft_add_arg(t_token *lexer);
int ft_is_pair(int tested);

#endif
