#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#include "libft.h"
#include "../lexer/lexer.h"
#include "../parser/parse.h"
#include "../parser/tree.h"
#include "path.h"

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

void    ft_exec_redir(char **redir)
{
    int i;
    int fd;

    i = -1;
    while (redir[++i])
    {
        if (redir[i][0] == '0') // '<'
        {
            fd = open(redir[i] + 1, O_RDONLY);
            if (fd == -1)
                return ;
       }
        else if (redir[i][0] == '1') // '>'
        {
            fd = open(redir[i] + 1, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
                return ;
        }
        else if (redir[i][0] == '2') // ">>"
        {
            fd = open(redir[i] + 1, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd == -1)
                return ;
        }
        else if (redir[i][0] == '3') // "<<"
        {
            ft_get_heredoc(redir[i] + 1);
            fd = open(".here_doc", O_RDONLY);
            if (fd == -1)
                return ;
            unlink(".here_doc");
        }
        if (redir[i][0] != '0') // '>' or ">>" or "<<"
            dup2(fd, 1);
        else if (redir[i][0] == '0') // '<'
            dup2(fd, 0);
        close(fd);
    }
}

void	ft_open_pipes(t_ast_node *exec)
{
    int fd[2];

	if (pipe(fd) == -1)
		return ;
	exec->data.content.next->data.content.pipes[1] = fd[1];
	exec->data.content.pipes[0] = fd[0];
}

void    ft_dup_pipe(t_ast_node *exec)
{
    if (exec->data.content.pipes[1])
        dup2(exec->data.content.pipes[1], STDOUT_FILENO);
    if (exec->data.content.pipes[0])
        dup2(exec->data.content.pipes[0], STDIN_FILENO);
}

void    ft_execve(t_ast_node *exec, t_ctx *ctx)
{
    char *cmd_path;

    cmd_path = ft_chr_path(exec->data.content.tok_list[0], ctx->env);
    if (!cmd_path)
        return ;
    execve(cmd_path, exec->data.content.tok_list ,ctx->env);
    exit(1);
}

void ft_fork(t_ast_node *exec, t_ctx *ctx)
{
    pid_t   pid;

    pid = fork();
    if (pid == -1)
        return ;
    if (pid == 0)
    {
        if (exec->data.content.tok_list[0] == 0)
            return ;
        if (exec->data.content.pipes[0] || exec->data.content.pipes[1])
            ft_dup_pipe(exec);
        if (exec->data.content.redirect && exec->data.content.redirect[0] != NULL)
            ft_exec_redir(exec->data.content.redirect);
        ft_execve(exec, ctx);
   }
//   return (pid);
}

/*void    ft_wait(pid_t l_pid, t_ctx *ctx)
{
    int     status;
    pid_t   pid;

    while (1)
    {
        pid = wait(&status);
        if (pid == l_pid)
            ctx->ex_status = WEXITSTATUS(status);
        if (pid < 0 && errno != EINTR)
            break ;
    }
}*/

int    ft_exec_cmd(t_ast_node *exec, t_ctx *ctx)
{
    int pid;
    int status;
    int ret;

    status = 0;
    if (!exec)
        return (-1);
    if (exec->node_type == NODE_PIPE || exec->node_type == NODE_DATA)
    {
        if (exec->data.content.next)
        {
            ft_open_pipes(exec);
            ft_exec_cmd(exec->data.content.next, ctx);
        }
        ft_fork(exec, ctx);
        if (exec->data.content.pipes[0] > 0)
            close(exec->data.content.pipes[0]);
        if (exec->data.content.pipes[1] > 0)
            close(exec->data.content.pipes[1]);
    }
    else if (exec->node_type == NODE_AND || exec->node_type == NODE_OR)
    {
        if (fork() == 0)
            ft_exec_cmd(exec->data.pair.left, ctx);
        wait(0);
        ft_exec_cmd(exec->data.pair.right, ctx);
    }
    pid = wait(&status);
    if (WIFEXITED(status))
    {
		ret = WEXITSTATUS(status);
        return (ret);
    }
    return (0);
}
