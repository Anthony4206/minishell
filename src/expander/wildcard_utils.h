/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:26:04 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 12:38:19 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_UTILS_H
# define WILDCARD_UTILS_H

int		ft_first_wildcard(char *wildcard, int *i, char *part, char *str);
int		ft_last_wildcard(char *part, char *str, int len);
void	ft_add_part(char *part, char *wildcard, int *i, int *last);
int		ft_over_wildcard(char *wildcard, char *str, char *part);

#endif
