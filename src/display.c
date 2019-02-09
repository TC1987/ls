/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:25:57 by tcho              #+#    #+#             */
/*   Updated: 2019/02/09 03:47:17 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include "ls.h"

void print_invalid(t_node *current)
{
	if (!current)
		return ;
	print_invalid(current->left);
	printf("ls: %s: No such file or directory\n", current->name);
	print_invalid(current->right);
}

void print_files(t_node *current, unsigned char flags)
{
	if (!current)
		return ;
	print_files(current->left, flags);
	if (flags & 1 << l)
	{
		printf("%s %2u %s %s ", current->mode, current->links, current->user, current->group);
		print_major_minor(current);
		printf("%s ", current->time);
	}
	printf("%s", current->name);
	current->linkname ? printf(" -> %s\n", current->linkname) : printf("\n");
	print_files(current->right, flags);
}

void print_files_reverse(t_node *current)
{
	if (!current)
		return ;
	print_files_reverse(current->right);
	printf("%s\n", current->name);
	print_files_reverse(current->left);
}

void print_directories(t_node *current, int print_name, unsigned char flags)
{
	if (!current)
		return ;
	print_directories(current->left, 1, flags);
	if (print_name)
		printf("\n");
	if (print_name || current->left || current->right)
		printf("%s:\n", current->name);
	if (flags & 1 << l && current->total)
		printf("total %lld\n", current->total);
	print_files(current->subtree, flags);
	print_directories(current->right, 1, flags);
}

void print_recursive(t_node *current, int print_name, unsigned char flags)
{
	if (!current)
		return ;
	print_recursive(current->left, 1, flags);
	if (current->type == DIRECTORY)
	{
		if (print_name)
			printf("\n");
		if (print_name || current->left || current->right)
			printf("%s:\n", current->full_path ? current->full_path: current->name);
		if (flags & 1 << l && current->total)
			printf("total %lld\n", current->total);
		print_files(current->subtree, flags);
		print_recursive(current->subtree, 1, flags);
	}
	print_recursive(current->right, 1, flags);
}

void print_major_minor(t_node *current)
{
	if (current->device)
	{
		printf("\t%6u, ", current->major);
		current->minor ? printf("%4u ", current->minor) : printf("%4d ", 0);
	}
	else
		printf("%6lli ", current->size);
}
