/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:25:57 by tcho              #+#    #+#             */
/*   Updated: 2019/02/06 19:28:04 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include "ls.h"

void display_files(t_node *current)
{
	if (!current)
		return ;
	display_files(current->left);
	printf("%s\n", current->name);
	display_files(current->right);
}

void display_files_reverse(t_node *current)
{
	if (!current)
		return ;
	display_files_reverse(current->right);
	printf("%s\n", current->name);
	display_files_reverse(current->left);
}

void display_directories(t_node *current)
{
	if (!current)
		return ;
	display_directories(current->left);
	display_files(current->subtree);
	display_directories(current->right);
}

void display_recursive(t_node *root)
{
	if (!root)
		return ;
	display_recursive(root->left);
	printf("%s\n", root->name);
	display_recursive(root->subtree);
	display_recursive(root->right);
}
