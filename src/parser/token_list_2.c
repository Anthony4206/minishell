#include "libft.h"
#include "tree.h"

t_ast_node	*ft_tok_last(t_ast_node *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->data.content.next != NULL)
		lst = lst->data.content.next;
	return (lst);
}

void	ft_tok_add_back(t_ast_node **lst, t_ast_node *new)
{
	t_ast_node	*last;

	if (*lst != NULL)
	{
		last = *lst;
		last = ft_tok_last(*lst);
		last->data.content.next = new;
		return ;
	}
	*lst = new;
}
