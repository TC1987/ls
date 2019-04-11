/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_printf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/12 22:09:59 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 05:58:25 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef B_PRINTF_H
# define B_PRINTF_H

# include <stdarg.h>

int	ft_pc(int c);
int	ft_ps(char *str);
int	ft_ia(int num);
int	ft_uitoa(unsigned long num, unsigned long base);
int	ft_operation(va_list argptr, char c);
int ft_is_space(const char *restrict format, int i);
int	b_printf(const char *restrict format, ...);

#endif
