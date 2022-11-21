/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:27:08 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 08:27:23 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_WILDCARD_H
# define EXPAND_WILDCARD_H

void	ft_expand_wildcard(char **cmd, char *wildcard, int pos);
void	ft_sup_param(char **cmd, char *wildcard);
void	ft_add_param(char **cmd, char *str, int pos);
int		ft_apply_wildcard(char *wildcard, char *str);

#endif
