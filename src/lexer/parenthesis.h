/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 07:00:33 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 07:00:36 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARENTHESIS_H
# define PARENTHESIS_H

t_token	*ft_find_peer(t_token *l_parenthesis);
int		ft_parse_parenth(t_token *lexer);

#endif
