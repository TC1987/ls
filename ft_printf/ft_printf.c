/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:33:26 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 00:33:28 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*get_arg(va_list *argptr, char **format, int *i)
{
	t_flags		s;
	char		*str;

	s.flags = malloc(sizeof(int) * 5);
	s.flags2 = malloc(sizeof(int) * 5);
	getflags(&s, format);
	getwidth(argptr, &s, format);
	getprecision(argptr, &s, format);
	getflags2(&s, format);
	str = conversion(**format, argptr, &s, i);
	(*format)++;
	free(s.flags);
	free(s.flags2);
	return (str);
}

void		make_str(t_str *n, int i, int *m, va_list *argptr)
{
	while (*n->mid != '\0')
	{
		if (*n->mid == '%')
		{
			*n->mid = '\0';
			n->num = ft_stradd(n->num, ft_strdup(n->temp));
			n->mid++;
			n->temp = get_arg(argptr, &(n->mid), &i);
			n->num = ft_stradd(n->num, n->temp);
			if (i > 0)
			{
				i = ft_strlen(n->num);
				write(1, n->num, i);
				(*m) += i;
				write(1, "\0", 1);
				(*m)++;
				i = 0;
				n->num = NULL;
				n->temp = NULL;
			}
			n->temp = n->mid;
		}
		else
			n->mid++;
	}
}

int			ft_printf(const char *format, ...)
{
	va_list		argptr;
	t_str		n;
	int			i;
	char		*strcpy;
	int			m;

	m = 0;
	n.num = NULL;
	n.mid = NULL;
	n.temp = NULL;
	i = 0;
	n.mid = ft_strdup(format);
	strcpy = n.mid;
	va_start(argptr, format);
	n.temp = n.mid;
	make_str(&n, i, &m, &argptr);
	n.num = ft_stradd(n.num, ft_strdup(n.temp));
	i = ft_strlen(n.num);
	write(1, n.num, i);
	va_end(argptr);
	free(strcpy);
	free(n.num);
	m += i;
	return (m);
}
