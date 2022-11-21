/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 05:59:25 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 05:59:28 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H

# include "lexer/lexer.h"

void	ft_init_sig(struct termios *term, struct termios *sign);
void	ft_sig_handler(int sig);

#endif
