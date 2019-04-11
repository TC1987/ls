/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:30:00 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 06:56:23 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <string.h>
#include <errno.h>
#include "libft.h"
#include "ls.h"

void	parse_args(char ***argv, unsigned char flags, t_trees *trees)
{
	if (**argv == NULL)
		parent_add_node(trees, ".", flags);
	else
	{
		while (**argv)
		{
			parent_add_node(trees, **argv, flags);
			(*argv)++;
		}
	}
}

char	*create_full_path(char *str1, char *str2)
{
	size_t	str1length;
	size_t	str2length;
	char	*full_path;

	str1length = ft_strlen(str1);
	str2length = ft_strlen(str2);
	NULL_CHECK((full_path = ft_strnew(str1length + str2length + 1)));
	ft_strcat(full_path, str1);
	if (full_path[str1length - 1] != '/')
		ft_strcat(full_path, "/");
	ft_strcat(full_path, str2);
	return (full_path);
}

void	parse_subtree(t_node *subtree, unsigned char flags,
		int (*sorting_function)(t_node *, t_node *))
{
	if (!subtree)
		return ;
	parse_subtree(subtree->left, flags, sorting_function);
	if (subtree->full_path[ft_strlen(subtree->full_path) - 1] == '.')
		return ;
	parse_dir(subtree, flags, sorting_function);
	parse_subtree(subtree->right, flags, sorting_function);
}

t_node	*init_and_add(t_node *node, char *name, char *full_path,
		int (*cmp)(t_node *, t_node *))
{
	struct stat		buffer;
	t_node			*current_node;

	if (lstat(full_path, &buffer) == -1)
		current_node = init_node(buffer, full_path, INVALID, errno);
	else if (!S_ISDIR(buffer.st_mode))
		current_node = init_node(buffer, full_path, VALID, 0);
	else
		current_node = init_node(buffer, full_path, DIRECTORY, 0);
	current_node->name = ft_strdup(name);
	if (ft_strequ(name, "..") || ft_strequ(name, "."))
		current_node->display = 0;
	add_node(&(node->subtree), current_node, cmp);
	node->total += buffer.st_blocks;
	return (current_node);
}

void	parse_dir(t_node *node, unsigned char flags,
		int (*cmp)(t_node *, t_node *))
{
	DIR				*dir_stream;
	struct dirent	*file;
	int				recurse;
	char			*full_path;
	t_node			*current_node;

	recurse = 0;
	if (node->type != DIRECTORY)
		return ;
	if (!(dir_stream = opendir(node->full_path)))
	{
		node->error = errno;
		return ;
	}
	while ((file = readdir(dir_stream)))
	{
		if (!(flags & 1 << a) && file->d_name[0] == '.')
			continue;
		full_path = create_full_path(node->full_path, file->d_name);
		current_node = init_and_add(node, file->d_name, full_path, cmp);
		if ((flags & 1 << R) && !ft_strequ(file->d_name, ".") &&
				!ft_strequ(file->d_name, ".."))
			parse_dir(current_node, flags, cmp);
	}
	closedir(dir_stream);
}
