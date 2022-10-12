/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:14:15 by mmidon            #+#    #+#             */
/*   Updated: 2022/09/22 10:11:43 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSE_H
# define CLOSE_H

#include "lexer/lexer.h"

void	ft_free_struct(t_ctx *ctx);
int		ft_return_err(char *arg, char *msg);
void	ft_sig_handler(int sig);

#endif
