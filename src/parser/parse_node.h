/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_node.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 06:30:53 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 06:31:19 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_NODE_H
# define PARSE_NODE_H

# include "tree.h"
# include "../lexer/lexer.h"

int			ast_peek(t_token **lexer, int *tok, int size, int opts);
void		ast_scanner_next(t_token **lexer);
t_ast_node	*ast_cmd_node(void);
t_ast_node	*ast_redir_node(t_ast_node *cmd, char *file, int mode, int fd);
t_ast_node	*ast_pair_node(t_ast_node *left, t_ast_node *right, int node_type);
#endif