/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <mmidon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:23:52 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/05 14:45:40 by mmidon           ###   ########.fr       */
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
#include "expander/expand_var.h"

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

    if (tree->node_type == NODE_AND || tree->node_type == NODE_OR)
    {
        printf("Pair(\n");
		printf("left -->	"); 
        ft_visit(tree->data.pair.left);
		printf("right -->	"); 
        ft_visit(tree->data.pair.right);
        printf(")\n");
    }
    else if (tree->node_type == NODE_DATA || tree->node_type == NODE_PIPE)
	{
		i = -1;
		while (tree->data.content.tok_list[++i])
			if (tree->data.content.tok_list)
        		printf("Word/arg/%d(\"%s\")\n", i, tree->data.content.tok_list[i]);
		i = -1;
		while (tree->data.content.redirect[++i])
			if (tree->data.content.redirect)
        		printf("Word/redir/%d(\"%s\")\n", i , tree->data.content.redirect[i]);
		if (tree->data.content.next)
			ft_visit(tree->data.content.next);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx		*ctx;
//	t_ast_node	*exec_tree;
	char		**line_read;

	(void)(argc + argv);
	ctx = ft_init(envp);
	while (1)
	{
		line_read = malloc(sizeof(char *) * 3);
		line_read[0] = readline("minishell$ ");
		line_read[1] = 0;
		if (!line_read[0])
			return (0);
		if (line_read[0] && *line_read[0])
		{
			ft_add_history(line_read[0]);
			line_read = ft_expand(line_read, ctx);
			printf("result: %s\n", line_read[0]);
			free(line_read[0]);
		/*	if (ft_lexer(ctx, line_read) < 0)
			{
				printf("syntax error\n");
			}
			else
			{
				exec_tree = ast_parse(ctx->start_lexer);
				if (exec_tree)
					ft_visit(exec_tree);
			}
			ctx->start_lexer = NULL;
			//system("leaks minishell");
		*/}
		free(line_read);
	}
	ft_free_struct(ctx);
	return (0);
}
