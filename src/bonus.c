/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 07:33:31 by tcho              #+#    #+#             */
/*   Updated: 2019/04/12 00:01:26 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"
#include "b_printf.h"

void	print_dirnames_only(t_node *current, unsigned char flags)
{
	if (!current)
		return ;
	print_dirnames_only(current->left, flags);
	if (!current->error)
	{
		if (flags & 1 << l)
		{
			b_printf("%s  %u  %s ", current->mode, current->links,
					current->user);
			if (!(flags & 1 << o))
				b_printf("%s ", current->group);
			print_major_minor(current);
			b_printf("\t%s ", current->time);
		}
		if (flags & 1 << p && current->type == DIRECTORY)
			b_printf("%s/", current->name);
		else
			b_printf("%s", current->name);
		if (flags & 1 << l && current->linkname)
			b_printf(" -> %s\n", current->linkname);
		else
			b_printf("\n");
	}
	print_dirnames_only(current->right, flags);
}
