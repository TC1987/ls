/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:33:47 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 00:33:48 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		a;
	int		b;
	int		i;
	char	*alloc;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	if ((alloc = (char *)malloc(sizeof(char) * (a + b + 1))) == NULL)
		return (NULL);
	while (i < a)
	{
		alloc[i] = s1[i];
		i++;
	}
	while (i < a + b)
	{
		alloc[i] = s2[i - a];
		i++;
	}
	alloc[i] = '\0';
	return (alloc);
}
