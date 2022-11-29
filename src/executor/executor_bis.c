/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:11:57 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/29 07:58:09 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include "../parser/tree.h"
#include "../lexer/lexer.h"
#include "../expander/expand_var.h"
#include "../builtins/builtin.h"
#include "path.h"
#include "here_doc.h"
#include "executor.h"
#include "../close.h"

t_prompt	g_prompt;

int	ft_over_exec_redir(t_ast_node *node, t_ctx *ctx, t_fd *fds, int fd)
{
	if (fd == -1)
	{
		ft_return_err("no such file or directory", node->data.redir.file);
		return (1);
	}
	if (fds->first_in && (node->data.redir.fd == 0 || node->data.redir.fd == 2))
	{
		fds->fd[0] = fd;
		fds->first_in = 0;
	}
	if (fds->first_out && node->data.redir.fd == 1)
	{
		fds->fd[1] = fd;
		fds->first_out = 0;
	}	
	fds->fd_close = node->data.redir.fd;
	if (!node->data.redir.cmd || node->data.redir.cmd->node_type == NODE_CMD)
	{
		fds->first_in = 1;
		fds->first_out = 1;
		ctx->is_first = 1;
		ctx->len = 0;
	}
	return (0);
}

int	ft_exec_redir(t_ast_node *node, t_ctx *ctx, t_fd *fds)
{
	int	fd;

	if (ctx->is_first)
		ft_is_here_doc(ctx, node);
	if (node->data.redir.fd == 2)
	{
		ft_get_heredoc(ctx->fd_here_doc[--ctx->len]);
		if (!g_prompt.here_doc)
			return (1);
		else
			fd = open(".here_doc", O_RDONLY);
	}
	else
	{
			fd = open(node->data.redir.file, node->data.redir.mode, 0664);
		if (ft_over_exec_redir(node, ctx, fds, fd) == 1)
			return (1);
	}
	ft_exec_node(node->data.redir.cmd, ctx, fds);
	return (1);
}

int	ft_children(t_ast_node *node, t_ctx *ctx, t_fd *fds)
{
	char	*cmd_path;

	cmd_path = NULL;
	if (fds->fd_close != fds->fd[STDIN_FILENO])
		dup2(fds->fd[STDIN_FILENO], STDIN_FILENO);
	if (fds->fd_close != fds->fd[STDOUT_FILENO])
		dup2(fds->fd[STDOUT_FILENO], STDOUT_FILENO);
	if (fds->fd[STDIN_FILENO] != STDIN_FILENO)
		close(fds->fd[STDIN_FILENO]);
	if (fds->fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(fds->fd[STDOUT_FILENO]);
	if (fds->fd_close > 2)
		close(fds->fd_close);
	if (node->data.cmd.tok_list[0] == 0)
		exit(1);
	if (ctx->env[0] != NULL)
		cmd_path = ft_chr_path(node->data.cmd.tok_list[0], ctx->env);
	if (!cmd_path)
	{
		ft_return_err(node->data.cmd.tok_list[0], "command not found");
		exit (127);
	}
	execve(cmd_path, node->data.cmd.tok_list, ctx->env);
	ft_return_err("execve", "failled");
	exit(1);
}

int	ft_exec_cmd(t_ast_node *node, t_ctx *ctx, t_fd *fds)
{
	int		ret;

	g_prompt.prompt = 0;
	ft_expand(node->data.cmd.tok_list, ctx);
	ret = ft_is_builtin(node->data.cmd.tok_list, fds, ctx);
	if (ret == 2)
		return (0);
	else if (ret)
		return (g_prompt.status);
	else
		g_prompt.last_pid = fork();
	if (g_prompt.last_pid == CHILD_PROCESS)
		ft_children(node, ctx, fds);
	return (1);
}
