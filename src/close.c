/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:14:45 by mmidon            #+#    #+#             */
/*   Updated: 2022/11/17 15:12:33 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <signal.h>
#include <termios.h>

#include "libft.h"
# include "lexer/lexer.h"

t_prompt	g_prompt;

void	rl_replace_line(const char *text, int clear_undo);

void	ft_free_struct(t_ctx *ctx)
{
	t_token	*ptr;

	while (ctx->start_lexer)
	{
		ptr = ctx->start_lexer->next;
		if (ft_strlen(ctx->start_lexer->content))
			free (ctx->start_lexer->content);
		if (ctx->start_lexer != NULL)
			free (ctx->start_lexer);
		ctx->start_lexer = ptr;
	}
	if (ctx->env)
		ft_free_tab(ctx->env);
//	ft_free_tab(ctx->fd_here_doc);
	free(ctx);
}

void	ft_free_all(t_token *lexer)
{
	t_token *tmp;
	
	while (lexer)
	{
		tmp = lexer->next;
		if (lexer->content)
		{
			free(lexer->content);
			lexer->content = NULL;
		}
		free(lexer);
		lexer = tmp;
	}
}

void    ft_free_tree(t_ast_node *tree)
{
	int	i;

	i = -1;
    if (tree->node_type == NODE_CMD)
	{
		while (tree->data.cmd.tok_list[++i])
			free(tree->data.cmd.tok_list[i]);
		free(tree);
	}
    else if (tree->node_type == NODE_REDIR)
    {
        if (tree->data.redir.cmd)
            ft_free_tree(tree->data.redir.cmd);
		free(tree);
    }
	else if (tree->node_type == NODE_AND || tree->node_type == NODE_OR
		|| tree->node_type == NODE_PIPE)
	{
		if (tree->data.pair.left)
        	ft_free_tree(tree->data.pair.left);
		if (tree->data.pair.right)
        	ft_free_tree(tree->data.pair.right);
		free(tree);
	}
}

int	ft_return_err(char *arg, char *msg)
{
	char	*ret;

	ret = ft_calloc(ft_strlen(arg) + ft_strlen(msg) + 15, 1);
	if (ret)
	{	
		ft_strlcat(ret, "minishell: ", -1);
		ft_strlcat(ret, arg, -1);
		ft_strlcat(ret, ": ", -1);
		ft_strlcat(ret, msg, -1);
		ft_strlcat(ret, "\n", -1);
		ft_putstr_fd(ret, 2);
		free(ret);
	}
	return (0);
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_prompt.status = 1;
		write(1, "\n", 1);
		if (g_prompt.prompt)
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		else
			kill(1, SIGINT);
	}
	if (sig == SIGQUIT)
	{
		if (g_prompt.prompt)
		{
			rl_on_new_line();
			rl_redisplay();
		}
		else
		{
			g_prompt.status = 132;
			printf("Quit: 3\n");
			rl_on_new_line();
		}
	}
}
