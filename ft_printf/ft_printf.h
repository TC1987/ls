/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:33:34 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 00:33:36 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>

typedef struct		s_flags
{
	int				*flags;
	int				*flags2;
	int				widthflag;
	int				minwidth;
	int				precisionflag;
	int				precision;
}					t_flags;

typedef struct		s_str
{
	char			*sign;
	char			*mid;
	char			*num;
	char			*temp;
}					t_str;

int					ft_printf(const char *format, ...);
char				*get_arg(va_list *argptr, char **format, int *i);
void				getflags(t_flags *s, char **format);
void				getflags2(t_flags *s, char **format);
char				*conversion(char c, va_list *argptr, t_flags *s, int *i);
void				getwidth(va_list *argptr, t_flags *s, char **format);
void				getprecision(va_list *argptr, t_flags *s, char **format);
char				*uitoa_base(unsigned long long int num,
					int base, char flag);
char				*print_o_u_x(va_list *argptr, t_flags *s,
					int base, char flag);
int					power(int n, int i);
char				*ftoa(long double f, int n);
char				*print_f(va_list *argptr, t_flags *s);
char				*print_perc(t_flags *s, char l);
char				*ft_stradd(char *a, char *b);
char				*create_str(unsigned int size, char c);
char				*print_c(va_list *argptr, t_flags *s, int *k);
char				*print_s(va_list *argptr, t_flags *s);
char				*itoa_base(long long int num, int base, int flag);
char				*print_d_i(va_list *argptr, t_flags *s);
char				*print_p(va_list *argptr, t_flags *s);

#endif
