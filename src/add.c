/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:31:33 by tcho              #+#    #+#             */
/*   Updated: 2019/02/07 06:01:47 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <string.h>
#include "ls.h"
#include "libft.h"

t_node *add_node(t_node **root, t_node *node)
{
	if (*root == NULL)
		return *root = node;
	else if (ft_strcmp((*root)->name, node->name) > 0)
	{
		if ((*root)->left == NULL)
			return (*root)->left = node;
		add_node(&(*root)->left, node);
	}
	else
	{
		if ((*root)->right == NULL)
			return (*root)->right = node;
		add_node(&(*root)->right, node);
	}
	return (node);
}

// Directories need to have all contents (files and subdirectories) in one tree.
void parent_add_node(t_trees *trees, char *name, unsigned char flags)
{
	struct stat buffer;
	int lstat_result;
	t_node *node;

	lstat_result = lstat(name, &buffer);
	node = init_node(buffer, name);

	if (lstat_result < 0)
		add_node(&(trees->invalid), node);
	else if (S_ISDIR(buffer.st_mode) == 0)
		add_node(&(trees->valid), node);
	else
	{
		add_node(&(trees->directory), node);
		node->is_dir = 1;
		parse_dir(node, flags);
	}
}
