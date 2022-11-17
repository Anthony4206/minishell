#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include "libft.h"
#include "executor.h"
#include "path.h"
#include "../lexer/lexer.h"
#include "../parser/parse.h"
#include "../parser/tree.h"
#include "../expander/expand_var.h"
#include "../builtins/builtin.h"
#include "../close.h"

t_prompt	g_prompt;

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		;
	return(i);
}

static void	ft_adjust(t_ctx *ctx, char **tab, int i)
{
	int j;

	j = -1;
	ctx->fd_here_doc = malloc(sizeof(char *) * (i + 2));
	while(tab[++j])
	{
		ctx->fd_here_doc[j] = ft_strdup(tab[j]);
		free(tab[j]);
	}
	ctx->fd_here_doc[j] = 0;
	free(tab);
}

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
	ft_adjust(ctx, tmp, i);
}

void    ft_get_heredoc(char *eof)
{
    char    *line;
    char    *limiter;
    int     fd;

    fd = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
        return ;
    line = "";
    limiter = eof;
    while (1)
    {
        ft_putstr_fd("> ", 1);
        line = get_next_line(STDIN_FILENO);
        if (line == NULL)
            break ;
        if (ft_strlen(limiter) + 1 == ft_strlen(line)
            && !ft_strncmp(line, limiter, ft_strlen(limiter)))
            break ;
        else
            ft_putstr_fd(line, fd);
        free(line);
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

void	ft_exec(t_ast_node *tree, t_ctx *ctx)
{
    t_fd    fds;
	int	    i;
	int	    children;
    int     status;
    pid_t   pid;
	
	if (!tree)
		return ;
	i = -1;
    fds.fd[0] = STDIN_FILENO;
	fds.fd[1] = STDOUT_FILENO;
	fds.fd_close = -1;
    fds.first_in = 1;
    fds.first_out = 1;	
    children = ft_exec_node(tree, ctx, &fds);
	while (1)
    {
		pid = wait(&status);
        if (pid == g_prompt.last_pid)
           g_prompt.status = WEXITSTATUS(status);
        if (pid < 0 && errno != EINTR)
            break;
   }
}

int    ft_exec_redir(t_ast_node *node, t_ctx *ctx, t_fd *fds)
{
    int fd;

	if (ctx->is_first)
		ft_is_here_doc(ctx, node);
	if (node->data.redir.fd == 2)
	{
		ft_get_heredoc(ctx->fd_here_doc[--ctx->len]);
        fd = open(".here_doc", O_RDONLY);
	}
	else
    	fd = open(node->data.redir.file, node->data.redir.mode, 0664);
    if (fd == -1)
    {
        ft_fprintf(2, "open %s failed\n", node->data.redir.file);
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
    ft_exec_node(node->data.redir.cmd, ctx, fds);
    return (1);
}

t_ast_node	*ft_skip_to_pair(t_ast_node *node)
{
	while (node && node->data.pair.right)
	{
		if (node->node_type == NODE_AND || node->node_type == NODE_OR)
			return (node->data.pair.right);
		if (node->node_type && node->node_type <= 5) 
			node = node->data.pair.right;
		else 
			return(NULL);
	}
	return (NULL);
}

int    ft_exec_and_or(t_ast_node *node, t_ctx *ctx, t_fd *fds)
{
    ft_exec_node(node->data.pair.left, ctx, fds);
	if (g_prompt.status)
		return (g_prompt.status);
    waitpid(g_prompt.last_pid, &g_prompt.status, 0);
//    if (g_prompt.status == 2)
 //       g_prompt.status += 128;
//    else
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

int	ft_exec_cmd(t_ast_node *node, t_ctx *ctx, t_fd *fds)
{
	char	*cmd_path;
	int	ret;

	g_prompt.prompt = 0;
	if (ft_expand(node->data.cmd.tok_list, ctx) > 0)
		dprintf(2,"WILDCARD [grrrrr]\n");
	ret = ft_is_builtin(node->data.cmd.tok_list, fds, ctx);
	if (ret == 2)
		return (0);
	else if (ret)
		return (g_prompt.status);
	else
		g_prompt.last_pid = fork();
	if (g_prompt.last_pid == CHILD_PROCESS)
	{        
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
        cmd_path = ft_chr_path(node->data.cmd.tok_list[0], ctx->env);
        if (!cmd_path)
		{
            ft_return_err(node->data.cmd.tok_list[0], "command not found");
			exit (127);
		}
		execve(cmd_path, node->data.cmd.tok_list, ctx->env);
        dprintf(2, "exec %s failed\n", node->data.cmd.tok_list[0]); //////////sussy dprintf//////////////////////////
        exit(1);
	}
	return (1);
}

int	ft_exec_pipe(t_ast_node *node, t_ctx *ctx, t_fd *fds)
{
	int			p[2];
	int			children;
	t_ast_node	*left_exec;
	t_ast_node	*right_exec;
	t_fd		left_fds;
	t_fd		right_fds;

	pipe(p);
	children = 0;
	left_exec = node->data.pair.left;
	left_fds = *fds;
	left_fds.fd[STDOUT_FILENO] = p[STDOUT_FILENO];
	left_fds.fd_close = p[STDIN_FILENO];
	children += ft_exec_node(left_exec, ctx,  &left_fds);
	close(p[STDOUT_FILENO]);
	unlink(".here_doc");
	right_exec = node->data.pair.right;
	right_fds = *fds;
	right_fds.fd[STDIN_FILENO] = p[STDIN_FILENO];
	right_fds.fd_close = p[STDOUT_FILENO];
	children += ft_exec_node(right_exec, ctx, &right_fds);
	close(p[STDIN_FILENO]);
	unlink(".here_doc");
	return (children);
}
