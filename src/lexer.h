/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmidon <mmidon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:03:39 by mmidon            #+#    #+#             */
/*   Updated: 2022/09/14 11:46:22 by mmidon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>

# include "structs.h"

size_t	*ft_parse_quotes(char *str);
char	*ft_chr_token(t_ctx *ctx, char *str);
void	ft_lexer(t_ctx *ctx, char *line);
int		ft_count_quotes(char *str);

#endif
