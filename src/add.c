/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:31:33 by tcho              #+#    #+#             */
/*   Updated: 2019/02/11 09:57:25 by tcho             ###   ########.fr       */
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

void	parent_add_node(t_trees *trees, char *name, unsigned char flags)
{
	int			errno_code;
	int			lstat_value;
	struct stat	buffer;
	int			(*cmp)(t_node *, t_node *);
	t_node		*node;

	cmp = get_sorting_function(flags);
	node = init_node(buffer, name, name, NONE);
	if (lstat(name, &buffer) < 0)
	{
		node->type = INVALID;
		add_node(&(trees->invalid), node, ft_lexcmp);
	}
	else if (S_ISDIR(buffer.st_mode) == 0)
	{
		node->type = VALID;
		add_node(&(trees->valid), node, cmp);
	}
	else
	{
		node->type = DIRECTORY;
		add_node(&(trees->directory), node, cmp);
		parse_dir(node, flags, cmp);
	}
}
