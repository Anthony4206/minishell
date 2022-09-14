/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <mmidon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:14:15 by mmidon            #+#    #+#             */
/*   Updated: 2022/09/12 13:30:32 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSE_H
# define CLOSE_H

# include "structs.h"

void	ft_free_struct(t_ctx *ctx);
void	ft_return_err(char *arg, char *msg);
void	ft_sig_handler(int sig);

#endif