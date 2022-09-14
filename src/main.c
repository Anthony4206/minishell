/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <mmidon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:23:52 by alevasse          #+#    #+#             */
/*   Updated: 2022/09/14 12:44:43 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

#include "structs.h"
#include "close.h"
#include "libft.h"
#include "lexer.h"

void rl_replace_line (const char *text, int clear_undo);

t_ctx	ft_init(char **envp)
{
	struct sigaction	sa;
	t_ctx				ret;

	ret.start_lexer = NULL;
	ret.env = envp;
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

int	main(int argc, char **argv, char **envp)
{
	t_ctx	ctx;
	char	*line_read;

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
			ft_lexer(&ctx, line_read);
			ft_free_struct(&ctx);
		}
		free(line_read);
	}
	return (0);
}
