/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:25:57 by tcho              #+#    #+#             */
/*   Updated: 2019/02/07 05:48:10 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include "ls.h"

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

void print_directories(t_node *current)
{
	if (!current)
		return ;
	print_directories(current->left);
	print_files(current->subtree);
	print_directories(current->right);
}

void print_recursive(t_node *root)
{
	if (!root)
		return ;
	print_recursive(root->left);
	if (root->subtree)
	{
		printf("\n%s:\n", root->name);
		print_directories(root);  // Prints subtree in order.
		print_recursive(root->subtree);
	}
	print_recursive(root->right);
}
