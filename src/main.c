/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:23:52 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/24 08:13:22 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <termios.h>
#include <string.h>
#include <signal.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "signal.h"
#include "parser/parse.h"
#include "parser/tree.h"
#include "lexer/lexer.h"
#include "builtins/builtin.h" 
#include "executor/executor.h"
#include "close.h"

t_prompt	g_prompt;

void	rl_replace_line(const char *text, int clear_undo);

char	**ft_dup(char **envp)
{
	char	**dup;
	int		i;

	i = 0;
	while (envp[i++])
		;
	dup = malloc(sizeof(char *) * (i + i));
	i = -1;
	while (envp[++i])
		dup[i] = ft_strdup(envp[i]);
	dup[i] = 0;
	return (dup);
}

t_ctx	*ft_init(char **envp)
{
	t_ctx				*ret;

    if (!envp)
        return (NULL);
	ret = malloc(sizeof(t_ctx));
	ret->start_lexer = NULL;
	ret->exec_tree = NULL;
	ret->env = ft_dup(envp);
	ret->fd_here_doc = NULL;
	ret->len = 0;
	ret->is_first = 1;
	return (ret);
}

void	ft_add_history(char *line)
{
	int	i;

	i = -1;
	while (line[++i] && ft_isspace(line[i]))
		if (line[i + 1] == '\0')
			return ;
	add_history(line);
}

int	ft_shell(t_ctx *ctx, char *line, struct termios *term, struct termios *sign)
{
	if (line && *line)
	{
		ft_add_history(line);
		tcsetattr(STDIN_FILENO, TCSANOW, sign);
		if (ft_lexer(ctx, line) < 0)
			printf("syntax error\n");
		else
		{
			ctx->exec_tree = ast_parse(ctx->start_lexer);
			if (ctx->exec_tree)
				ft_exec(ctx->exec_tree, ctx);
			if (ctx->exec_tree)
				ft_free_tree(ctx->exec_tree);
			ft_free_all(ctx->start_lexer);
		}
		ctx->start_lexer = NULL;
		tcsetattr(STDIN_FILENO, TCSANOW, term);
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx			*ctx;
	struct termios	term;
	struct termios	sign;
	char			*line_read;

	(void)(argc + argv);
	ft_init_sig(&term, &sign);
	ctx = ft_init(envp);
	while (1)
	{
		ctx->is_first = 1;
		g_prompt.prompt = 1;
		if (g_prompt.status == 132)
			g_prompt.status--;
		line_read = readline("\033[0;36mminishell-1.0$ \033[0m");
		if (!line_read)
			break ;
		ft_shell(ctx, line_read, &term, &sign);
		free(line_read);
	}
	ft_free_struct(ctx);
	return (0);
}
