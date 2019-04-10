/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:13:52 by tcho              #+#    #+#             */
/*   Updated: 2019/04/10 02:19:12 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "ls.h"

int	update_flag(char f, unsigned char *flags)
{
	if (f == 'l')
		return (*flags |= 1 << l);
	if (f == 'a')
		return (*flags |= 1 << a);
	if (f == 'r')
		return (*flags |= 1 << r);
	if (f == 't')
		return (*flags |= 1 << t);
	if (f == 'R')
		return (*flags |= 1 << R);
	return (0);
}

int	check_flags(char ***argv, unsigned char *flags)
{
	while (*(++(*argv)) && ***argv == '-')
		while (*(++(**argv)))
			if (!update_flag(***argv, flags))
				return (0);
	return (1);
}
