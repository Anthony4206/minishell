/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 06:27:46 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 06:27:55 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_UTILS_H
# define PARSE_UTILS_H

# include "tree.h"
# include "../lexer/lexer.h"

char	*ft_type_redir(int type);
char	**ft_init_redir(t_token **lexer, char **redir);
char	**ft_add_redir(t_token **lexer);
char	**ft_init_arg(t_token **lexer, char **arg);
char	**ft_add_arg(t_token **lexer);

#endif
