/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:10:05 by mmidon            #+#    #+#             */
/*   Updated: 2022/11/21 07:08:38 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

# include "../lexer/lexer.h"

char	*ft_add_string(char *str, t_token *token);
char	*ft_add_two_char(char *str, t_token *token);
char	*ft_add_caractere(char *str, t_token *token);
int		ft_find_content(char *str, char *limiter, t_token *token);

#endif
