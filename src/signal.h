#ifndef SIGNAL_H
# define SIGNAL_H

# include "lexer/lexer.h"

void	ft_init_sig(struct termios *term, struct termios *sign);
void	ft_sig_handler(int sig);

#endif
