/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alevasse <alevasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 06:59:49 by alevasse          #+#    #+#             */
/*   Updated: 2022/05/06 06:41:07 by alevasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_parser(const char *fmt, va_list args)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			i++;
			len += ft_define_args(fmt, args, &i);
		}
		else
			len += ft_putchar_size(fmt[i]);
		i++;
	}
	return (len);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		ret;

	va_start(args, fmt);
	ret = ft_parser(fmt, args);
	va_end(args);
	return (ret);
}
