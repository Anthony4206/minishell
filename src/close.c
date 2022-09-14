/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <mmidon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:14:45 by mmidon            #+#    #+#             */
/*   Updated: 2022/09/14 11:16:29 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "structs.h"

void rl_replace_line (const char *text, int clear_undo);

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
}

void	ft_return_err(char *arg, char *msg)
{
	char	*ret;

	ret = ft_calloc(ft_strlen(arg) + ft_strlen(msg) + 11, 1);
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
	exit(EXIT_FAILURE);
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
	}
}
