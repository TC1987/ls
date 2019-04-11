/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_f.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:34:35 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 00:34:36 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		power(int n, int i)
{
	int		k;
	int		res;

	res = n;
	k = 0;
	if (i == 0)
		return (1);
	while (k < i - 1)
	{
		res = res * n;
		k++;
	}
	return (res);
}

char	*ftoa(long double f, int n)
{
	char	*flpt;
	char	*intpt;
	long	fl;
	long	i;
	char	*neg;

	neg = 0;
	if (f < 0)
		neg++;
	i = (long long)f;
	intpt = itoa_base(i, 10, 0);
	f = f - (long double)i;
	f = (f * power(10, n));
	fl = (f >= 0) ? (long)(f + 0.5) : (long)(f - 0.5);
	flpt = itoa_base(fl, 10, 0);
	if (neg)
		intpt = ft_stradd(ft_strdup("-"), intpt);
	if (n == 0)
		return (intpt);
	intpt = ft_stradd(intpt, ft_strdup("."));
	intpt = ft_stradd(intpt, flpt);
	return (intpt);
}

char	*print_f(va_list *argptr, t_flags *s)
{
	char	*num;
	int		n;

	n = 6;
	if (s->precisionflag && s->precision >= 0)
		n = s->precision;
	if (s->flags2[4])
		num = ftoa(va_arg(*argptr, long double), n);
	else if (s->flags2[3])
		num = ftoa(va_arg(*argptr, double), n);
	else
		num = ftoa(va_arg(*argptr, double), n);
	return (num);
}

char	*print_perc(t_flags *s, char l)
{
	char	*mid;
	char	c;
	char	*m;

	m = ft_strdup("a");
	m[0] = l;
	mid = NULL;
	c = ' ';
	if (s->flags[4] && !s->flags[2])
		c = '0';
	if (s->widthflag && s->minwidth > 1)
		mid = create_str(s->minwidth - 1, c);
	if (s->flags[2] > 0)
		mid = ft_stradd(m, mid);
	else if (s->flags[2] == 0)
		mid = ft_stradd(mid, m);
	return (mid);
}
