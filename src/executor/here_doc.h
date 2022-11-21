/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:55:26 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 13:20:36 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

void	ft_is_here_doc(t_ctx *ctx, t_ast_node *tree);
void	ft_get_heredoc(char *eof);

#endif
