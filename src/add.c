/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:31:33 by tcho              #+#    #+#             */
/*   Updated: 2019/03/15 22:41:21 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include "ls.h"
#include "libft.h"

void	add_node(t_node **root, t_node *node, int (*cmp)(t_node *, t_node *))
{
	if (*root == NULL)
		*root = node;
	else if (cmp(*root, node) > 0)
	{
		if ((*root)->left == NULL)
			(*root)->left = node;
		else
			add_node(&(*root)->left, node, cmp);
	}
	else
	{
		if ((*root)->right == NULL)
			(*root)->right = node;
		else
			add_node(&(*root)->right, node, cmp);
	}
}

void	parent_add_node(t_trees *trees, char *name, unsigned char flags)
{
	struct stat	buffer;
	t_node		*node;
	int			(*cmp)(t_node *, t_node *);

	cmp = get_cmp(flags);
	if (lstat(name, &buffer) < 0)
	{
		node = init_node(buffer, name, name, INVALID, errno);
		add_node(&(trees->invalid), node, cmp);
	}
	else if (S_ISDIR(buffer.st_mode) == 0)
	{
		node = init_node(buffer, name, name, VALID, 0);
		add_node(&(trees->valid), node, cmp);
	}
	else
	{
		node = init_node(buffer, name, name, DIRECTORY, 0);
		add_node(&(trees->directory), node, cmp);
		parse_dir(node, flags, cmp);
	}
}
