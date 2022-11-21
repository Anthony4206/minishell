/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:20:06 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 13:29:02 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# include "../parser/tree.h"
# include "../lexer/lexer.h"

int			ft_strlen_tab(char **tab);
void		ft_adjust_exec(t_ctx *ctx, char **tab, int i);
t_ast_node	*ft_skip_to_pair(t_ast_node *node);

#endif
