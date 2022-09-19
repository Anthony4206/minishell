/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:14:15 by mmidon            #+#    #+#             */
/*   Updated: 2022/09/19 11:50:33 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLOSE_H
# define CLOSE_H

# include "structs.h"

void	ft_free_struct(t_ctx *ctx);
int 	ft_return_err(char *arg, char *msg);
void	ft_sig_handler(int sig);

#endif