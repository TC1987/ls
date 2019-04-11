/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_printf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 17:09:58 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 05:57:43 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "b_printf.h"

int	b_printf(const char *restrict format, ...)
{
	int		i;
	int		count;
	va_list	argptr;

	i = 0;
	count = 0;
	va_start(argptr, format);
	while (format[i])
	{
		if (format[i] != '%')
			count += ft_pc(format[i]);
		else
		{
			i++;
			if (!format[i])
				return (count);
			i = ft_is_space(format, i);
			count += ft_operation(argptr, format[i]);
		}
		i++;
	}
	va_end(argptr);
	return (count);
}
