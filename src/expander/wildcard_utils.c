/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 10:26:19 by alevasse          #+#    #+#             */
/*   Updated: 2022/11/21 12:39:27 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

#include "libft.h"
#include "no_random_quote.h"
#include "wildcard_utils.h"
#include "expand_wildcard.h"
#include "../executor/executor.h"

int	ft_first_wildcard(char *wildcard, int *i, char *part, char *str)
{
	if (wildcard[0] != '*')
	{
		while (wildcard[*i] && wildcard[*i] != '*')
		{
			if (wildcard[*i] != str[*i])
				return (ft_return_free(part, 0));
			(*i)++;
		}
	}
	return (1);
}

int	ft_last_wildcard(char *part, char *str, int len)
{
	int	len_str;

	len_str = ft_strlen(str);
	while (len_str && len)
	{
		if (str[len_str - 1] != part[len - 1])
			return (ft_return_free(part, 0));
		len_str--;
		len--;
	}
	return (ft_return_free(part, 1));
}

void	ft_add_part(char *part, char *wildcard, int *i, int *last)
{
	int	j;

	j = 0;
	while (wildcard[*i + j] && wildcard[*i + j] != '*')
	{
		part[j] = wildcard[*i + j];
		if (wildcard[*i + j + 1] == '\0')
			*last = 1;
		j++;
	}
	part[j] = '\0';
}

int	ft_over_wildcard(char *wildcard, char *str, char *part)
{
	int		i;
	int		len;
	int		last;
	int		ret;

	i = 0;
	last = 0;
	ret = ft_first_wildcard(wildcard, &i, part, str);
	if (!ret)
		return (ret);
	while (wildcard[i])
	{
		if (wildcard[i] == '*' && ++i)
			continue ;
		ft_add_part(part, wildcard, &i, &last);
		len = ft_strlen(part);
		str = ft_strstr(str, part);
		if (last && str != NULL)
			return (ft_last_wildcard(part, str, len));
		if (str == NULL || (*(str + len) != '\0' && wildcard[i + len] != '*'))
			return (ft_return_free(part, 0));
		i += len;
	}
	return (1);
}
