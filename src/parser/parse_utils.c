#include "libft.h"
#include "../lexer/lexer.h"

char    **ft_init_redir(t_token *lexer, char **redir)
{
    int i;

    i = 0;
    if (!redir)
        return (-1);
    while (lexer->type == TOK_STRING || lexer->type == TOK_REDIR)
    {
        if (lexer->type = TOK_STRING)
            lexer = lexer->next;
        else if (lexer->type == TOK_REDIR && lexer->next->type == TOK_STRING)
        {
            redir[i] = ft_strdup(lexer->content);
            i++;
            lexer = lexer->next->next;
        }
     else
            return (-1);
    }
    return (redir);
}

char    **ft_init_arg(t_token *lexer, char **redir)
{
    int i;

    i = 0;
    if (!arg)
        return (-1);
    while (lexer->type == TOK_STRING || lexer->type == TOK_REDIR)
    {
        if (lexer->type = TOK_STRING)
        {
            redir[i] = ft_strdup(lexer->content);
            i++;
            lexer = lexer->next;
        }
        else if (lexer->type == TOK_REDIR && lexer->next->type == TOK_STRING)
            lexer = lexer->next->next;
        else
            return (-1);
    }
    return (redir);
}

char    **ft_add_redir(t_token *lexer)
{
    int     i;
    t_token *tmp;

    i = 0;
    tmp = lexer;
    while (tmp->type == TOK_STRING || tmp->type == TOK_REDIR)
    {
        if (tmp->type = TOK_STRING)
            tmp = tmp->next;
        else if (tmp->type == TOK_REDIR && tmp->next->type == TOK_STRING)
        {
            i++;
            tmp = tmp->next->next;           
        }
        else
            return (-1);
    }
    return (ft_init_redir(lexer, malloc(sizeof(char *) * (i + 1))));
}

char    **ft_add_arg(t_token *lexer)
{
    int     i;
    t_token *tmp;

    i = 0;
    while (lexer->type == TOK_STRING || lexer->type == TOK_REDIR)
    {
        if (lexer->type = TOK_STRING)
        {
            i++;
            lexer = lexer->next;
        }
        else if (lexer->type == TOK_REDIR && lexer->next->type == TOK_STRING)
            lexer = lexer->next->next;           
        else
            return (-1);
    }
    return (ft_init_arg(lexer, malloc(sizeof(char *) * (i + 1))));
}