#include "libft.h"
#include "structs.h"

static int	ft_parse_duplicate(t_token *lexer)
{
	t_token	*ptr;

	ptr = lexer;
	while (ptr)
	{
		if (ptr->type == TOK_L_PARENTHESIS && ptr->next->type)
		ptr = ptr->next;
	}
}

int	ft_parse_parenth(t_token *lexer)
{
	int		count_parenth[2];
	t_token	*ptr;
	
	ptr = lexer;
	ft_bzero(count_parenth, 2);
	while (ptr)
	{
		if (ptr->type == TOK_L_PARENTHESIS)
			count_parenth[0]++;
		else if (ptr->type == TOK_R_PARENTHESIS)
			count_parenth[1]++;
		ptr = ptr->next;
	}
	if (count_parenth[0] != count_parenth[1])
		return (-1);
	ft_parse_duplicates(lexer);
	return (0);
}
