/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_o_u_x.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:34:42 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 00:34:43 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char			*uitoa_base(unsigned long long int num, int base, char flag)
{
	char			alloc[50];
	char			*res;
	int				i;

	res = (flag != 'X') ? "0123456789abcdef" : "0123456789ABCDEF";
	if (num == 0)
		return (ft_strdup("0"));
	i = 48;
	alloc[49] = '\0';
	while (num != 0)
	{
		alloc[i--] = res[(num % base)];
		num /= base;
	}
	return (ft_strdup(&(alloc[++i])));
}

long long int	get_oux_size(va_list *argptr, t_flags *s)
{
	if (s->flags2[0] > 0)
		return ((unsigned char)va_arg(*argptr, unsigned int));
	else if (s->flags2[1] > 0)
		return ((unsigned short)va_arg(*argptr, unsigned int));
	else if (s->flags2[2] > 0)
		return (va_arg(*argptr, unsigned long long int));
	else if (s->flags2[3])
		return (va_arg(*argptr, unsigned long));
	else
		return (va_arg(*argptr, unsigned int));
}

static char		*oux_final(t_flags *s, t_str n, long long int i, char c)
{
	i = ft_strlen(n.num);
	if (s->widthflag && s->minwidth > i)
		n.mid = create_str(s->minwidth - i, c);
	if ((s->flags[4] && !s->precisionflag) && !s->flags[2])
	{
		if (n.mid != NULL)
			n.num = ft_stradd(n.mid, n.num);
		if (n.sign != NULL)
			n.num = ft_stradd(n.sign, n.num);
	}
	else if (s->flags[2] > 0)
	{
		if (n.sign != NULL)
			n.num = ft_stradd(n.sign, n.num);
		n.num = ft_stradd(n.num, n.mid);
	}
	else if (s->flags[2] == 0)
	{
		if (n.sign != NULL)
			n.num = ft_stradd(n.sign, n.num);
		n.num = ft_stradd(n.mid, n.num);
	}
	return (n.num);
}

void			pres_info_oux(char *c, t_flags *s, long long int *i, t_str *n)
{
	*c = ' ';
	if (s->precisionflag && !s->precision && !*i)
	{
		free(n->num);
		n->num = ft_strdup("");
	}
	*i = ft_strlen(n->num);
	if (s->flags[4] && !s->precisionflag && !s->flags[2])
		*c = '0';
	else if (s->precisionflag && s->precision > *i)
		n->num = ft_stradd(create_str(s->precision - *i, '0'), n->num);
}

char			*print_o_u_x(va_list *argptr, t_flags *s, int base, char flag)
{
	long long int	i;
	t_str			n;
	char			c;

	n.sign = NULL;
	n.mid = NULL;
	n.num = NULL;
	i = get_oux_size(argptr, s);
	n.num = uitoa_base(i, base, flag);
	pres_info_oux(&c, s, &i, &n);
	if (s->flags[0] > 0 && !(*(n.num) == '0' && (int)ft_strlen(n.num) == i))
	{
		if (base == 16 && !(s->precisionflag && !s->precision && !i))
		{
			if (flag)
				n.sign = ft_strdup("0X");
			else if (!flag)
				n.sign = ft_strdup("0x");
		}
		else if (base == 8 && !(s->precisionflag && s->precision > 1))
			n.sign = ft_strdup("0");
		if (n.sign)
			s->minwidth -= ft_strlen(n.sign);
	}
	return (oux_final(s, n, i, c));
}
