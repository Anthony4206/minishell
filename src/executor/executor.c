/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:49:16 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 15:03:57 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "executor.h"
#include "path.h"
#include "executor_bis.h"
#include "here_doc.h"
#include "executor_utils.h"
#include "../lexer/lexer.h"
#include "../parser/parse.h"
#include "../parser/tree.h"
#include "../expander/expand_var.h"
#include "../builtins/builtin.h"
#include "../close.h"

t_prompt	g_prompt;
void	rl_replace_line(const char *text, int clear_undo);

void	ft_exec(t_ast_node *tree, t_ctx *ctx)
{
	t_fd	fds;
	int		i;
	int		status;
	pid_t	pid;

	if (!tree)
		return ;
	i = -1;
	fds.fd[0] = STDIN_FILENO;
	fds.fd[1] = STDOUT_FILENO;
	fds.fd_close = -1;
	fds.first_in = 1;
	fds.first_out = 1;
	ft_exec_node(tree, ctx, &fds);
	while (1)
	{
		pid = wait(&status);
		if (pid == g_prompt.last_pid)
			g_prompt.status = WEXITSTATUS(status);
		if (pid < 0 && errno != EINTR)
			break ;
	}
}

int	ft_exec_node(t_ast_node *node, t_ctx *ctx, t_fd *fds)
{
	int	ret;

	ret = 0;
	if (node->node_type == NODE_CMD)
	{
		ret = ft_exec_cmd(node, ctx, fds);
		g_prompt.status = ret;
		unlink(".here_doc");
		return (ret);
	}
	else if (node->node_type == NODE_PIPE)
		return (ft_exec_pipe(node, ctx, fds));
	else if (node->node_type == NODE_REDIR)
	{
		ret = ft_exec_redir(node, ctx, fds);
		unlink(".here_doc");
		return (ret);
	}
	else if (node->node_type == NODE_AND || node->node_type == NODE_OR)
		return (ft_exec_and_or(node, ctx, fds));
	else
		return (0);
}

int	ft_exec_and_or(t_ast_node *node, t_ctx *ctx, t_fd *fds)
{
	ft_exec_node(node->data.pair.left, ctx, fds);
	if (g_prompt.status)
		return (g_prompt.status);
	waitpid(g_prompt.last_pid, &g_prompt.status, 0);
	g_prompt.status = WEXITSTATUS(g_prompt.status);
	if (node->node_type == NODE_AND && g_prompt.status == 0)
		ft_exec_node(node->data.pair.right, ctx, fds);
	else if (node->node_type == NODE_OR && g_prompt.status != 0)
		ft_exec_node(node->data.pair.right, ctx, fds);
	else
	{
		node = ft_skip_to_pair(node->data.pair.right);
		if (node)
			ft_exec_node(node, ctx, fds);
	}
	return (1);
}

int	ft_exec_pipe(t_ast_node *node, t_ctx *ctx, t_fd *fds)
{
	int			p[2];
	t_fd		left_fds;
	t_fd		right_fds;

	if (pipe(p) == -1)
		return (1);
	left_fds = *fds;
	left_fds.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
	left_fds.fd_close = p[STDIN_FILENO];
	ft_exec_node(node->data.pair.left, ctx, &left_fds);
	close(p[STDOUT_FILENO]);
	unlink(".here_doc");
	right_fds = *fds;
	right_fds.fd[STDIN_FILENO] = p[STDIN_FILENO];
	right_fds.fd_close = p[STDOUT_FILENO];
	ft_exec_node(node->data.pair.right, ctx, &right_fds);
	close(p[STDIN_FILENO]);
	unlink(".here_doc");
	return (0);
}
