#ifndef TOKEN_LIST_2_H
# define TOKEN_LIST_2_H

# include "tree.h"


t_ast_node	*ft_tok_last(t_ast_node *lst);
void	    ft_tok_add_back(t_ast_node **lst, t_ast_node *new);

#endif