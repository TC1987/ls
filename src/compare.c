/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:17:44 by tcho              #+#    #+#             */
/*   Updated: 2019/02/11 02:57:18 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ls.h"

int ft_timecmp(t_node *n1, t_node *n2)
{
	if (n1->numtime == n2->numtime)
	{
		if (n1->nanoseconds < n2->nanoseconds)
			return (1);
		else if (n1->nanoseconds == n2->nanoseconds)
			return ft_lexcmp(n1, n2);
	}
	else if (n1->numtime < n2->numtime)
		return (1);
	return (0);
}

int ft_timecmp_r(t_node *n1, t_node *n2)
{
	if (n1->numtime == n2->numtime)
	{
		if (n1->nanoseconds > n2->nanoseconds)
			return (1);
		else if (n1->nanoseconds == n2->nanoseconds)
			return ft_lexcmp_r(n1, n2);
	}
	else if (n1->numtime > n2->numtime)
		return (1);
	return (0);
}

int ft_lexcmp(t_node *n1, t_node *n2)
{
	char *str1;
	char *str2;

	str1 = n1->name;
	str2 = n2->name;

	return (ft_strcmp(str1, str2));
}

int ft_lexcmp_r(t_node *n1, t_node *n2)
{
	return (ft_lexcmp(n1, n2) * -1);
}
