/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:44:53 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/14 11:17:55 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_free_tab(char **split)
{
	size_t	i;

	i = 0;
	if (!split)
		return (-1);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (-1);
}
