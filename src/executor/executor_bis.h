/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_bis.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:54:42 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 13:20:53 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_BIS_H
# define EXECUTOR_BIS_H

int	ft_exec_redir(t_ast_node *node, t_ctx *ctx, t_fd *fds);
int	ft_exec_cmd(t_ast_node *node, t_ctx *ctx, t_fd *fds);

#endif
