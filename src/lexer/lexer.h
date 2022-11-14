/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:03:39 by mmidon            #+#    #+#             */
/*   Updated: 2022/11/14 13:42:44 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>

# include "../parser/tree.h"
# include "../context.h"

int		ft_parse_quotes(char *str);
char	*ft_chr_token(t_ctx *ctx, char *str);
int		ft_lexer(t_ctx *ctx, char *line);
int		ft_count_quotes(char *str);

#endif