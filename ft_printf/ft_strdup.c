/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 00:33:41 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 00:33:42 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	int		size;

	size = 0;
	while (s1[size] != '\0')
		size++;
	dup = (char *)malloc(sizeof(char) * (size + 1));
	if (dup == NULL)
	{
		return (NULL);
	}
	size = 0;
	while (s1[size] != '\0')
	{
		dup[size] = s1[size];
		size++;
	}
	dup[size] = s1[size];
	return (dup);
}
