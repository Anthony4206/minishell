/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:03:39 by mmidon            #+#    #+#             */
/*   Updated: 2022/09/21 09:35:28 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>

# include "structs.h"

size_t	*ft_parse_quotes(char *str);
char	*ft_chr_token(t_ctx *ctx, char *str);
int		ft_lexer(t_ctx *ctx, char *line);
int		ft_count_quotes(char *str);

#endif