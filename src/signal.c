/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 05:59:35 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 05:59:37 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <signal.h>
#include <termios.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "libft.h"
#include "close.h"
#include "lexer/lexer.h"

void	rl_replace_line(const char *text, int clear_undo);
t_prompt	g_prompt;

void	ft_init_sig(struct termios *term, struct termios *sign)
{
	struct sigaction	sa;

	g_prompt.prompt = 1;
	g_prompt.here_doc = 0;
	g_prompt.status = 0;
	sa.sa_handler = ft_sig_handler;
	sa.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_return_err("sigaction", strerror(errno));
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		ft_return_err("sigaction", strerror(errno));
	tcgetattr(STDIN_FILENO, sign);
	sign->c_lflag |= ECHOCTL;
	*term = *sign;
	term->c_lflag &= ~ECHOCTL;
}

void	ft_sigint(void)
{
	g_prompt.status = 1;
	write(1, "\n", 1);
	if (g_prompt.here_doc)
		g_prompt.here_doc = 0;
	if (g_prompt.prompt)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		kill(1, SIGINT);
	g_prompt.prompt = 1;
}

void	ft_sigquit(void)
{
	if (g_prompt.here_doc)
		return ;
	if (g_prompt.prompt)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		g_prompt.status = 132;
		printf("Quit: 3\n");
		rl_on_new_line();
	}
}

void	ft_sig_handler(int sig)
{
	if (sig == SIGINT)
		ft_sigint();
	if (sig == SIGQUIT)
		ft_sigquit();
}
