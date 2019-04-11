/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:34:11 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 00:34:13 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char		*itoa_base(long long int num, int base, int flag)
{
	char			alloc[50];
	char			*res;
	int				i;
	int				neg;

	neg = 1;
	res = (flag == 0) ? "0123456789abcdef" : "0123456789ABCDEF";
	if (num == 0)
		return (ft_strdup("0"));
	i = 48;
	alloc[49] = '\0';
	if (num < 0)
		neg = -1;
	while (num != 0)
	{
		alloc[i--] = res[neg * (num % base)];
		num /= base;
	}
	return (ft_strdup(&(alloc[++i])));
}

char		*create_str(unsigned int size, char c)
{
	char			*temp;
	unsigned int	i;

	i = 0;
	temp = ft_strnew(size);
	while (i < size)
	{
		temp[i] = c;
		i++;
	}
	return (temp);
}

char		*ft_stradd(char *a, char *b)
{
	char			*temp;

	if (a != NULL && b != NULL)
	{
		temp = ft_strjoin(a, b);
		free(a);
		free(b);
	}
	else
	{
		if (a == NULL)
			temp = b;
		else
			temp = a;
	}
	return (temp);
}
