/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <mmidon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:23:52 by alevasse          #+#    #+#             */
/*   Updated: 2022/10/15 10:02:43 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "parser/parse.h"
#include "parser/tree.h"
#include "close.h"
#include "libft.h"
#include "lexer/lexer.h"
#include "builtins/builtin.h" 

void	rl_replace_line(const char *text, int clear_undo);

char	**ft_dup(char	**envp)
{
	char	**dup;
	int	i = 0;

	while (envp[i++]);
	dup = malloc(sizeof(char *) * (i + i));
	i = -1;
	while (envp[++i])
		dup[i] = ft_strdup(envp[i]);
	dup[i] = 0;
	return (dup);
}

t_ctx	*ft_init(char **envp)
{
	struct sigaction	sa;
	t_ctx				*ret;

	ret = malloc(sizeof(t_ctx));
	ret->start_lexer = NULL;
	ret->env = ft_dup(envp);
	sa.sa_handler = ft_sig_handler;
	if (sigemptyset(&sa.sa_mask) == -1)
		ft_return_err("sigemptyset", strerror(errno));
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_return_err("sigaction", strerror(errno));
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		ft_return_err("sigaction", strerror(errno));
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

void	ft_show_list(t_token *list)
{
	while (list)
	{
		printf("%s$\n", list->content);
		printf("%u$\n", list->type);
		list = list->next;
	}
}

void    ft_visit(t_ast_node *tree)
{
	int	i;
	int	j;

	i = -1;
//	printf("%d", tree->node_type);
    if (tree->node_type == NODE_AND)
    {
        printf("Pair(\n");
        ft_visit(tree->data.pair.left);
        ft_visit(tree->data.pair.right);
        printf(")\n");
    }
    else if (tree->node_type == NODE_DATA)
	{
		while (tree->data.content.tok_list[++i])
		{
			j = -1;
			if (tree->data.content.tok_list)
			{
        		printf("Word/arg(\"%s\")\n", tree->data.content.tok_list[i]);
				free(tree->data.content.tok_list[i]);
			}
			if (tree->data.content.redirect)
			{
				while (tree->data.content.redirect[++j])
        			printf("Word/redir[%d](\"%s\")\n", j,tree->data.content.redirect[j]);
			}
		}
	}
	else
        printf("Word(\"%s\")\n", tree->data.error.msg);
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx		*ctx;
	t_ast_node	*exec_tree;
	char		*line_read;

	(void)(argc + argv);
	ctx = ft_init(envp);
	while (1)
	{
		line_read = readline("minishell$ ");
		if (!line_read)
			return (0);
		if (line_read && *line_read)
		{
			if (!ft_strcmp(line_read, "exit"))
				return (0);
			ft_add_history(line_read);
			if (ft_lexer(ctx, line_read) < 0)
				printf("TMP ERROR [handle readline]\n");////
//			ft_show_list(ctx->start_lexer);
			exec_tree = ast_parse(ctx->start_lexer);
			ft_visit(exec_tree);
			ft_free_struct(ctx);
			//system("leaks minishell");
		}
		free(line_read);
	}
	return (0);
}
