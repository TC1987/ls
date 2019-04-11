/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:31:33 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 07:28:18 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include "ls.h"
#include "libft.h"

void	add_node(t_node **root, t_node *node,
		int (*cmp)(t_node *, t_node *))
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

t_func	*get_cmp(unsigned char flags)
{
	if (flags & 1 << r && flags & 1 << t)
		return (ft_timecmp_r);
	else if (flags & 1 << r)
		return (ft_lexcmp_r);
	else if (flags & 1 << t)
		return (ft_timecmp);
	else
		return (ft_lexcmp);
}

void	parent_add_node(t_trees *trees, char *name, unsigned char flags)
{
	struct stat	buffer;
	t_node		*node;
	int			(*cmp)(t_node *, t_node *);

	cmp = get_cmp(flags);
	if (lstat(name, &buffer) == -1)
	{
		node = init_node(buffer, name, INVALID, errno);
		node->name = ft_strdup(name);
		add_node(&(trees->invalid), node, cmp);
	}
	else if (!S_ISDIR(buffer.st_mode))
	{
		node = init_node(buffer, name, VALID, 0);
		node->name = ft_strdup(name);
		add_node(&(trees->valid), node, cmp);
	}
	else
	{
		node = init_node(buffer, name, DIRECTORY, 0);
		node->name = ft_strdup(name);
		add_node(&(trees->directory), node, cmp);
		if (!(flags & 1 << d))
			parse_dir(node, flags, cmp);
	}
}
