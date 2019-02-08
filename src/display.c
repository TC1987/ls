/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:25:57 by tcho              #+#    #+#             */
/*   Updated: 2019/02/08 04:13:23 by tcho             ###   ########.fr       */
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

void print_files(t_node *current)
{
	if (!current)
		return ;
	print_files(current->left);
	printf("%s\n", current->name);
	print_files(current->right);
}

void print_files_reverse(t_node *current)
{
	if (!current)
		return ;
	print_files_reverse(current->right);
	printf("%s\n", current->name);
	print_files_reverse(current->left);
}

void print_directories(t_node *current, int print_name)
{
	if (!current)
		return ;
	print_directories(current->left, 1);
	if (print_name)
		printf("\n%s:\n", current->name);
	print_files(current->subtree);
	print_directories(current->right, 1);
}

void print_recursive(t_node *root)
{
	if (!root)
		return ;
	print_recursive(root->left);
	if (root->type == DIRECTORY)
	{
		printf("%s:\n", root->full_path ? root->full_path: root->name);
		print_files(root->subtree);
		printf("\n");
		print_recursive(root->subtree);
	}
	print_recursive(root->right);
}
