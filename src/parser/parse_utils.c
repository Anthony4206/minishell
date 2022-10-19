#include <stdio.h>
#include "libft.h"
#include "../lexer/lexer.h"

int	ft_is_pair(int tested)
{
	if (tested == TOK_AND || tested == TOK_OR)
		return (1);
	return (0);
}

t_token *ft_find_pair(t_token	*lst)
{
	int	parenth;

	if (lst->type == TOK_L_PARENTHESIS)
		parenth = 1;
	else
		parenth = 0;
	while (lst && lst->next)
	{
		if (lst->next->type == TOK_L_PARENTHESIS)
			parenth = 1;
		if (lst->next->type == TOK_R_PARENTHESIS)
			parenth = 0;
		else if ((lst->next->type == TOK_AND || lst->next->type == TOK_OR) && !parenth)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

char	*ft_type_redir(int type)
{
	if (type == REDIR_INFILE)
		return ("0");
	else if (type == REDIR_OUTFILE)
		return ("1");
	else if (type == REDIR_APP_OUTFILE)
		return ("2");
	else
		return ("3");
}
 
char	**ft_init_redir(t_token *lexer, char **redir)
{
    int	i;

    i = 0;
	if (!redir)
		return (NULL);
    while (lexer && !ft_is_pair(lexer->type))
    {
        if (lexer->type == TOK_STRING)
            lexer = lexer->next;
        else if (lexer->type == TOK_REDIR && lexer->next->type == TOK_STRING)
        {
            redir[i] = ft_calloc(sizeof(char) * (ft_strlen(lexer->next->content) + 2), 1);
            ft_strlcat(redir[i], ft_type_redir(lexer->redir), -1);
            ft_strlcat(redir[i++], lexer->next->content, -1);
            lexer = lexer->next->next;
        }
        else
            return (NULL);
    }
    redir[i] = 0;
    return (redir);
}

char    **ft_add_redir(t_token *lexer)
{
    int     i;
    t_token *tmp;

    i = 0;
    tmp = lexer;
    while (tmp && (tmp->type == TOK_STRING || tmp->type == TOK_REDIR))
    {
        if (tmp->type == TOK_STRING)
            tmp = tmp->next;
        else if (tmp->type == TOK_REDIR && tmp->next->type == TOK_STRING)
        {
            i++;
            tmp = tmp->next->next;
        }
        else
            return (NULL);
    }
    return (ft_init_redir(lexer, malloc(sizeof(char *) * (i + 1))));
}

char    **ft_init_arg(t_token *lexer, char **arg)
{
    int i;

    i = 0;
    if (!arg)
        return (NULL);
    while (lexer && (lexer->type == TOK_STRING || lexer->type == TOK_REDIR || lexer->type == TOK_L_PARENTHESIS))
    {
        if (lexer->type == TOK_STRING)
        {
            arg[i++] = ft_strdup(lexer->content);
            lexer = lexer->next;
        }
        else if (lexer->type == TOK_REDIR && lexer->next->type == TOK_STRING)
            lexer = lexer->next->next;
		else if (lexer->type == TOK_L_PARENTHESIS)
			lexer = lexer->next;
        else
            return (NULL);
    }
    arg[i] = 0;
    return (arg);
}

char    **ft_add_arg(t_token *lexer)
{
    int     i;
    t_token *tmp;

    i = 0;
    tmp = lexer;
    while (tmp && (tmp->type == TOK_STRING || tmp->type == TOK_REDIR ||tmp->type == TOK_L_PARENTHESIS))
    {
        if (tmp->type == TOK_STRING)
        {
            i++;
            tmp = tmp->next;
        }
        else if (tmp->type == TOK_REDIR)
        {
			if (!tmp->next)
				return (NULL);
			if (tmp->next->type == TOK_STRING)
            	tmp = tmp->next->next;
			else
				return (NULL);
        }
		else if (tmp->type == TOK_L_PARENTHESIS)
			tmp = tmp->next;
        else
            return (NULL);
    }
    return (ft_init_arg(lexer, malloc(sizeof(char *) * (i + 1))));
}
