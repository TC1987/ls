/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:33:58 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 00:34:00 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char		*alloc;
	size_t		i;

	i = 0;
	alloc = (char *)malloc(size + 1);
	if (alloc == NULL)
		return (NULL);
	while (i <= size)
	{
		alloc[i] = '\0';
		i++;
	}
	return (alloc);
}
