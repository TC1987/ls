/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:31:33 by tcho              #+#    #+#             */
/*   Updated: 2019/02/11 21:00:36 by tcho             ###   ########.fr       */
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
		{
			(*root)->left = node;
			return ;
		}
		add_node(&(*root)->left, node, cmp);
	}
	else
	{
		if ((*root)->right == NULL)
		{
			(*root)->right = node;
			return ;
		}
		add_node(&(*root)->right, node, cmp);
	}
}

int     determine_type(struct stat buffer, int lstat_value)
{
	if (lstat_value < 0)
		return errno;
	else if (S_ISDIR(buffer.st_mode) == 0)
		return VALID;
	else
		return DIRECTORY;
}

void	parent_add_node(t_trees *trees, char *name, unsigned char flags)
{
	struct stat	buffer;
	int			(*cmp)(t_node *, t_node *);
	t_node		*node;
	int             lstat_value;

	cmp = get_sorting_function(flags);
	lstat_value = determine_type(buffer, lstat(name, &buffer));
	node = init_node(buffer, name, name, lstat_value);
	if (lstat_value == DIRECTORY)
	{
		add_node(&(trees->directory), node, cmp);
		parse_dir(node, flags, cmp);
	}
	else if (lstat_value == VALID)
		add_node(&(trees->valid), node, cmp);
	else
		add_node(&(trees->invalid), node, cmp);
}
