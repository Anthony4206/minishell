/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:14:06 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 13:37:24 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include "libft.h"
#include "executor_utils.h"
#include "../lexer/lexer.h"

t_prompt	g_prompt;

void	ft_is_here_doc(t_ctx *ctx, t_ast_node *tree)
{
	char	**tmp;
	int		i;

	i = -1;
	tmp = malloc(sizeof(char *) * 100);
	if (!tree)
		return ;
	while (tree->node_type == NODE_REDIR)
	{
		if (tree->data.redir.fd == 2)
			tmp[++i] = ft_strdup(tree->data.redir.file);
		tree = tree->data.redir.cmd;
	}
	tmp[++i] = 0;
	ctx->len = i;
	ctx->is_first = 0;
	ft_adjust_exec(ctx, tmp, i);
}

void	ft_get_heredoc(char *eof)
{
	char	*line;
	char	*limiter;
	int		fd;

	pipe(g_prompt.pipe_fd);
	dup2(STDIN_FILENO, g_prompt.pipe_fd[1]);
	fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	line = "";
	limiter = eof;
	g_prompt.prompt = 1;
	g_prompt.here_doc = 1;
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(g_prompt.pipe_fd[1]);
		if (line == NULL || !g_prompt.here_doc)
			break ;
		if (ft_strlen(limiter) + 1 == ft_strlen(line)
			&& !ft_strncmp(line, limiter, ft_strlen(limiter)))
			break ;
		else
			ft_putstr_fd(line, fd);
		free(line);
	}
	close(g_prompt.pipe_fd[0]);
	close(fd);
	unlink(".here_doc");
}
