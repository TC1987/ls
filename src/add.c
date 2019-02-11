/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:31:33 by tcho              #+#    #+#             */
/*   Updated: 2019/02/11 07:25:17 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include "ls.h"
#include "libft.h"

t_node	*add_node(t_node **root, t_node *node, int (*sorting_function)(t_node *, t_node *))
{
	if (*root == NULL)
		return (*root = node);
	else if (sorting_function(*root, node) > 0)
	{
		if ((*root)->left == NULL)
			return ((*root)->left = node);
		return (add_node(&(*root)->left, node, sorting_function));
	}
	else
	{
		if ((*root)->right == NULL)
			return ((*root)->right = node);
		return (add_node(&(*root)->right, node, sorting_function));
	}
}

void	parent_add_node(t_trees *trees, char *name, unsigned char flags)
{
	int			errno_code;
	int			lstat_result;
	t_node		*node;
	struct stat	buffer;
	int			(*sorting_function)(t_node *, t_node *);

	sorting_function = get_sorting_function(flags);
	if ((lstat_result = lstat(name, &buffer)) < 0)
	{
		node = init_node(buffer, name, name, errno);
		add_node(&(trees->invalid), node, ft_lexcmp);
	}
	else if (S_ISDIR(buffer.st_mode) == 0)
	{
		node = init_node(buffer, name, name, VALID);
		add_node(&(trees->valid), node, sorting_function);
	}
	else
	{
		node = init_node(buffer, name, name, DIRECTORY);
		add_node(&(trees->directory), node, sorting_function);
		parse_dir(node, flags, sorting_function);
	}
}
