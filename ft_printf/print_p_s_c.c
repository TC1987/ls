/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p_s_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:34:49 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 00:34:50 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*print_c(va_list *argptr, t_flags *s, int *k)
{
	int				i;
	t_str			n;
	char			c;

	n.mid = NULL;
	n.sign = ft_strdup(" ");
	c = ' ';
	if (s->flags[4])
		c = '0';
	n.sign[0] = va_arg(*argptr, int);
	if (s->precisionflag && !s->precision && !n.sign[0])
	{
		free(n.sign);
		n.sign = ft_strdup("");
	}
	i = 1;
	if (s->widthflag && i < s->minwidth)
		n.mid = create_str(s->minwidth - i, c);
	if (!n.sign[0])
		(*k)++;
	if (s->flags[2] > 0)
		n.sign = ft_stradd(n.sign, n.mid);
	else if (s->flags[2] < 1)
		n.sign = ft_stradd(n.mid, n.sign);
	return (n.sign);
}

char		*str_final(t_flags *s, t_str *n, int i, char c)
{
	if (s->precisionflag > 0 && s->precision < i && s->precision >= 0)
	{
		n->num[s->precision] = '\0';
		n->mid = n->num;
		n->num = ft_strdup(n->num);
		free(n->mid);
		i = s->precision;
	}
	n->mid = NULL;
	if (s->widthflag && s->minwidth > i)
		n->mid = create_str(s->minwidth - i, c);
	if (s->flags[2] > 0)
		n->num = ft_stradd(n->num, n->mid);
	if (s->flags[2] < 1)
		n->num = ft_stradd(n->mid, n->num);
	return (n->num);
}

char		*print_s(va_list *argptr, t_flags *s)
{
	int				i;
	t_str			n;
	char			c;

	c = ' ';
	if (s->flags[4])
		c = '0';
	n.num = va_arg(*argptr, char *);
	if (s->precisionflag && !s->precision && !n.num)
	{
		free(n.num);
		n.num = ft_strdup("");
	}
	if (n.num == NULL)
		n.num = ft_strdup("(null)");
	else
		n.num = ft_strdup(n.num);
	i = ft_strlen(n.num);
	return (str_final(s, &n, i, c));
}

char		*p_final(t_flags *s, t_str p, int i, char c)
{
	i = ft_strlen(p.num) + 2;
	if (s->widthflag && s->minwidth > i)
		p.mid = create_str(s->minwidth - i, c);
	if (s->flags[2])
	{
		p.num = ft_stradd(ft_strdup("0x"), p.num);
		p.num = ft_stradd(p.num, p.mid);
	}
	else if (s->flags[4])
	{
		p.num = ft_stradd(p.mid, p.num);
		p.num = ft_stradd(ft_strdup("0x"), p.num);
	}
	else if (!s->flags[2])
	{
		p.num = ft_stradd(ft_strdup("0x"), p.num);
		p.num = ft_stradd(p.mid, p.num);
	}
	return (p.num);
}

char		*print_p(va_list *argptr, t_flags *s)
{
	t_str			p;
	int				i;
	char			c;
	void			*n;

	c = ' ';
	p.mid = NULL;
	p.num = NULL;
	n = va_arg(*argptr, void *);
	p.num = itoa_base((long long int)n, 16, 0);
	if (s->precisionflag && !s->precision && !n)
	{
		free(p.num);
		p.num = ft_strdup("");
	}
	i = ft_strlen(p.num);
	if (s->flags[4] && !s->precisionflag && !s->flags[2])
		c = '0';
	else
		s->flags[4] = 0;
	i = ft_strlen(p.num);
	if (s->precisionflag && s->precision > i)
		p.num = ft_stradd(create_str(s->precision - i, '0'), p.num);
	return (p_final(s, p, i, c));
}
