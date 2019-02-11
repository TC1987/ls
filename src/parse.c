/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:30:00 by tcho              #+#    #+#             */
/*   Updated: 2019/02/10 19:41:31 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include "libft.h"
#include "ls.h"

void parse_args(char ***argv, unsigned char flags, t_trees *trees)
{
	struct stat buffer;
	int lstat_result;

	if (**argv == NULL)
	{
		parent_add_node(trees, ".", flags);
		return ;
	}
	while (**argv)
	{
		parent_add_node(trees, **argv, flags);
		(*argv)++;
	}
}

char *create_full_path(char *str1, char *str2)
{
	size_t	str1Length;
	size_t	str2Length;
	char	*full_path;

	str1Length = ft_strlen(str1);
	str2Length = ft_strlen(str2);
	NULL_CHECK((full_path = ft_strnew(str1Length + str2Length + 1)));
	ft_strcat(full_path, str1);
	ft_strcat(full_path, "/");
	ft_strcat(full_path, str2);
	return (full_path);
}

void parse_dir(t_node *node, unsigned char flags, int (*sorting_function)(t_node *, t_node *))
{
	DIR				*dir;
	struct dirent	*file;
	struct stat		buffer;
	t_node			*current_node;
	char			*tmp;

	if (!(dir = opendir(node->full_path)))
		return ;
	while ((file = readdir(dir)))
	{
		if (!(flags & 1 << a) && file->d_name[0] == '.')
			continue;
		tmp = create_full_path(node->full_path, file->d_name);
		lstat(tmp, &buffer);
		node->total += buffer.st_blocks;
		current_node = init_node(buffer, file->d_name, tmp);
		add_node(&(node->subtree), current_node, sorting_function);
		if ((flags & 1 << R) && S_ISDIR(buffer.st_mode) && ft_strcmp(current_node->name, ".") && ft_strcmp(current_node->name, ".."))
		{
			current_node->type = DIRECTORY;
			parse_dir(current_node, flags, sorting_function);
		}
	}
	closedir(dir);
	// By the time we get here, the current directory has been fully read and all of its contents are sorted.
}
