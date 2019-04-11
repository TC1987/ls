/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/15 15:35:04 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 05:59:10 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "b_printf.h"

int	ft_uitoa(unsigned long num, unsigned long base)
{
	int	remainder;
	int	count;

	count = 0;
	if (num >= base)
		count += ft_uitoa(num / base, base);
	remainder = num % base;
	ft_pc(remainder > 9 ? (remainder - 10) + 'a' : remainder + '0');
	count++;
	return (count);
}
