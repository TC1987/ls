/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:31:33 by tcho              #+#    #+#             */
/*   Updated: 2019/02/11 09:23:47 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include "ls.h"
#include "libft.h"

t_node	*add_node(t_node **root, t_node *node, int (*cmp)(t_node *, t_node *))
{
	if (*root == NULL)
		return (*root = node);
	else if (cmp(*root, node) > 0)
	{
		if ((*root)->left == NULL)
			return ((*root)->left = node);
		return (add_node(&(*root)->left, node, cmp));
	}
	else
	{
		if ((*root)->right == NULL)
			return ((*root)->right = node);
		return (add_node(&(*root)->right, node, cmp));
	}
}

void	parent_add_node(t_trees *trees, char *name, unsigned char flags)
{
	int			errno_code;
	struct stat	buffer;
	int			(*cmp)(t_node *, t_node *);
	t_node		*node;

	cmp = get_sorting_function(flags);
	if (lstat(name, &buffer) < 0)
		node = add_node(&(trees->invalid), \
				init_node(buffer, name, name, errno), ft_lexcmp);
	else if (S_ISDIR(buffer.st_mode) == 0)
		node = add_node(&(trees->valid), \
				init_node(buffer, name, name, VALID), cmp);
	else
	{
		node = add_node(&(trees->directory), \
				init_node(buffer, name, name, DIRECTORY), cmp);
		parse_dir(node, flags, cmp);
	}
}
