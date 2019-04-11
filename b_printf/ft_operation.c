/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 19:16:28 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 06:01:00 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_printf.h"
#include <stdarg.h>

int	ft_operation(va_list argptr, char c)
{
	if (c == 'd' || c == 'i')
		return (ft_ia(va_arg(argptr, int)));
	else if (c == 's')
		return (ft_ps(va_arg(argptr, char *)));
	else if (c == 'p')
		return (ft_ps("0x") + ft_uitoa(va_arg(argptr, unsigned long), 16));
	else if (c == 'c')
		return (ft_pc(va_arg(argptr, int)));
	else if (c == 'o')
		return (ft_uitoa(va_arg(argptr, unsigned int), 8));
	else if (c == 'u')
		return (ft_uitoa(va_arg(argptr, unsigned int), 10));
	else if (c == 'x')
		return (ft_uitoa(va_arg(argptr, unsigned int), 16));
	else if (c == '%')
		return (ft_pc('%'));
	return (0);
}
