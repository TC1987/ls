/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:25:57 by tcho              #+#    #+#             */
/*   Updated: 2019/02/08 18:15:23 by tcho             ###   ########.fr       */
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
	printf("%s\n", current->name);
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
	print_files(current->subtree, flags);
	print_directories(current->right, 1, flags);
}

void print_recursive(t_node *root, int print_name, unsigned char flags)
{
	if (!root)
		return ;
	print_recursive(root->left, 1, flags);
	if (root->type == DIRECTORY)
	{
		if (print_name)
			printf("\n");
		if (print_name || root->left || root->right)
			printf("%s:\n", root->full_path ? root->full_path: root->name);
		print_files(root->subtree, flags);
		print_recursive(root->subtree, 1, flags);
	}
	print_recursive(root->right, 1, flags);
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
