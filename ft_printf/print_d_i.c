/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d_i.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:34:28 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 00:34:29 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		get_decimal(va_list *argptr, t_flags *s, long long int *i)
{
	if (s->flags2[0] > 0)
		*i = (char)va_arg(*argptr, int);
	else if (s->flags2[1] > 0)
		*i = (short)va_arg(*argptr, int);
	else if (s->flags2[2] > 0)
		*i = va_arg(*argptr, long long);
	else if (s->flags2[3] > 0)
		*i = va_arg(*argptr, long);
	else
		*i = va_arg(*argptr, int);
}

static char	*decimal_final(t_flags *s, char *sign, char *mid, char *num)
{
	if (s->flags[4] > 0 && s->precisionflag == 0 && s->flags[2] == 0)
	{
		if (sign != NULL)
			mid = ft_stradd(sign, mid);
		if (mid != NULL)
			num = ft_stradd(mid, num);
	}
	else if (s->flags[2] > 0)
	{
		if (sign != NULL)
			num = ft_stradd(sign, num);
		num = ft_stradd(num, mid);
	}
	else if (s->flags[2] == 0)
	{
		if (sign != NULL)
			num = ft_stradd(sign, num);
		num = ft_stradd(mid, num);
	}
	return (num);
}

static void	get_sign_d(long long int *i, t_flags *s, char **sign)
{
	if (*i >= 0 && s->flags[3] > 0)
		*sign = ft_strdup("+");
	else if (*i >= 0 && s->flags[1] > 0)
		*sign = ft_strdup(" ");
	else if (*i < 0)
		*sign = ft_strdup("-");
}

static void	d_precision(t_flags *s, long long int *i, char **num, char *c)
{
	if (s->flags[4] > 0 && s->precisionflag == 0 && s->flags[2] == 0)
		*c = '0';
	else if (s->precisionflag > 0 && s->precision > *i)
	{
		*num = ft_stradd(create_str(s->precision - *i, '0'), *num);
		*i = ft_strlen(*num);
	}
}

char		*print_d_i(va_list *argptr, t_flags *s)
{
	long long int	i;
	char			*sign;
	char			*mid;
	char			*num;
	char			c;

	sign = NULL;
	mid = NULL;
	num = NULL;
	get_decimal(argptr, s, &i);
	num = itoa_base(i, 10, 0);
	c = ' ';
	if (s->precisionflag && !s->precision && !i)
	{
		free(num);
		num = ft_strdup("");
	}
	get_sign_d(&i, s, &sign);
	i = ft_strlen(num);
	d_precision(s, &i, &num, &c);
	if (s->widthflag && s->minwidth > i)
		mid = create_str(s->minwidth - i - (sign != NULL), c);
	return (decimal_final(s, sign, mid, num));
}
