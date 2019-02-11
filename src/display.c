/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:25:57 by tcho              #+#    #+#             */
/*   Updated: 2019/02/11 08:54:12 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include "ls.h"

void	print_invalid(t_node *current)
{
	if (!current)
		return ;
	print_invalid(current->left);
	printf("ls: %s: %s\n", current->name, strerror(current->type));
	print_invalid(current->right);
}

int		print_files(t_node *current, unsigned char flags)
{
	if (!current)
		return (0);
	print_files(current->left, flags);
	if (flags & 1 << l)
	{
		printf("%s %2u %s %s ", current->mode, \
				current->links, current->user, current->group);
		print_major_minor(current);
		printf("%s ", current->time);
	}
	printf("%s", current->name);
	if (flags & 1 << l && current->linkname)
		printf(" -> %s\n", current->linkname);
	else
		printf("\n");
	print_files(current->right, flags);
	return (1);
}

/*
void	print_directories(t_node *current, unsigned char flags, int print_name)
{
	if (!current)
		return ;
	print_directories(current->left, flags, print_name);
	if (print_name)
		printf("\n");
	if (print_name || current->left || current->right)
	{
		printf("%s:\n", current->name);
		print_name = 1;
	}
	if (flags & 1 << l && current->total)
		printf("total %lld\n", current->total);
	print_files(current->subtree, flags);
	print_directories(current->right, flags, print_name);
}
*/

void	print_recursive(t_node *current, unsigned char flags, int print_name)
{
	if (!current)
		return ;
	print_recursive(current->left, flags, print_name);
	if (current->type == DIRECTORY)
	{
		if (print_name)
			printf("\n");
		if (print_name || current->left || current->right)
		{
			printf("%s:\n", current->full_path ? \
					current->full_path : current->name);
			print_name = 1;
		}
		if (flags & 1 << l && current->total)
			printf("total %lld\n", current->total);
		print_files(current->subtree, flags);
		print_recursive(current->subtree, flags, print_name);
	}
	print_recursive(current->right, flags, print_name);
}

void	print_major_minor(t_node *current)
{
	if (current->device)
	{
		printf("\t%6u, ", current->major);
		current->minor ? printf("%4u ", current->minor) : printf("%4d ", 0);
	}
	else
		printf("%6lli ", current->size);
}
