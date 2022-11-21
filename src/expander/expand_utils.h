/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 08:55:07 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 12:41:58 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_UTILS_H
# define EXPAND_UTILS_H

char	*ft_adjust(char *cmd, int i);
char	*ft_env_chr(char *var, char **env);
void	ft_quote(int *quote);
char	*ft_join(char *ret, char *var, int *j);
void	ft_over_find_var(char *cmd, char *var, int *i);

#endif
