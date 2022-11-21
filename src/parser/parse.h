/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 06:03:42 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 06:03:45 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "tree.h"
# include "../lexer/lexer.h"

t_ast_node	*ast_parse(t_token *lexer);
t_ast_node	*ast_parse_line(t_token **lexer);
t_ast_node	*ast_parse_pipe(t_token **lexer);
t_ast_node	*ast_parse_redir(t_ast_node *cmd, t_token **lexer);
t_ast_node	*ast_parse_cmd(t_token **lexer);
t_ast_node	*ast_parse_parent(t_token **lexer);

#endif
