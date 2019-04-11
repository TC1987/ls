/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_flags.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:34:05 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 00:34:06 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	getflags(t_flags *s, char **format)
{
	int		i;

	i = 0;
	while (i != 5)
		(s->flags)[i++] = 0;
	while (**format == '#' || **format == ' ' || **format == '-'
			|| **format == '+' || **format == '0')
	{
		if (**format == '#')
			(s->flags)[0]++;
		if (**format == ' ')
			(s->flags)[1]++;
		if (**format == '-')
			(s->flags)[2]++;
		if (**format == '+')
			(s->flags)[3]++;
		if (**format == '0')
			(s->flags)[4]++;
		(*format)++;
	}
}

void	getflags2(t_flags *s, char **format)
{
	int		i;

	i = 0;
	while (i != 5)
		(s->flags2)[i++] = 0;
	if (**format == 'h' && *((*format) + 1) == 'h')
	{
		(s->flags2)[0]++;
		(*format)++;
	}
	else if (**format == 'h')
		(s->flags2)[1]++;
	else if (**format == 'l' && *((*format) + 1) == 'l')
	{
		(s->flags2)[2]++;
		(*format)++;
	}
	else if (**format == 'l')
		(s->flags2)[3]++;
	else if (**format == 'L')
		(s->flags2)[4]++;
	if (**format == 'h' || **format == 'l' || **format == 'L')
		(*format)++;
}

char	*conversion(char c, va_list *argptr, t_flags *s, int *i)
{
	if (c == 'c')
		return (print_c(argptr, s, i));
	else if (c == 's')
		return (print_s(argptr, s));
	else if (c == 'p')
		return (print_p(argptr, s));
	else if (c == 'd' || c == 'i')
		return (print_d_i(argptr, s));
	else if (c == 'o')
		return (print_o_u_x(argptr, s, 8, 0));
	else if (c == 'u')
		return (print_o_u_x(argptr, s, 10, 0));
	else if (c == 'x')
		return (print_o_u_x(argptr, s, 16, 0));
	else if (c == 'X')
		return (print_o_u_x(argptr, s, 16, 'X'));
	else if (c == 'f' || c == 'F')
		return (print_f(argptr, s));
	else if (c == '%')
		return (print_perc(s, c));
	else
		return (print_perc(s, c));
}

void	getwidth(va_list *argptr, t_flags *s, char **format)
{
	if (**format == '*')
	{
		s->widthflag = 1;
		s->minwidth = va_arg(*argptr, int);
		(*format)++;
	}
	else if (ft_isdigit(**format))
	{
		s->widthflag = 1;
		s->minwidth = ft_atoi(*format);
		while (**format <= '9' && **format >= '0')
			(*format)++;
	}
	else
	{
		s->widthflag = 0;
	}
}

void	getprecision(va_list *argptr, t_flags *s, char **format)
{
	if (**format != '.')
	{
		s->precisionflag = 0;
	}
	else
	{
		(*format)++;
		s->precisionflag = 1;
		if (ft_isdigit(**format))
		{
			s->precision = ft_atoi(*format);
			while (**format <= '9' && **format >= '0')
				(*format)++;
		}
		else if (**format == '*')
		{
			s->precision = va_arg(*argptr, int);
			(*format)++;
		}
		else
		{
			s->precision = 0;
		}
	}
}
