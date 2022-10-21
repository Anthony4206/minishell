#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

t_token *ft_find_pair(t_token *lst);
void    ft_free_all(t_token *lexer);
void    ft_free_tree(t_ast_node *tree);
char    *ft_type_redir(int type);
char    **ft_init_redir(t_token *lexer, char **redir);
char    **ft_add_redir(t_token *lexer);
char    **ft_init_arg(t_token *lexer, char **arg);
char    **ft_add_arg(t_token *lexer);
int	ft_is_pair(int tested);

#endif
