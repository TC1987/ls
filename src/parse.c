/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:30:00 by tcho              #+#    #+#             */
/*   Updated: 2019/02/11 23:30:43 by tcho             ###   ########.fr       */
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

void parse_subtree(t_node *subtree, unsigned char flags, int (*sorting_function)(t_node *, t_node *))
{
	if (!subtree)
		return ;
	parse_subtree(subtree->left, flags, sorting_function);
	parse_dir(subtree, flags, sorting_function);
	parse_subtree(subtree->right, flags, sorting_function);	
}

// For errno.
#include <string.h>
#include <errno.h>

void parse_dir(t_node *node, unsigned char flags, int (*cmp)(t_node *, t_node *))
{
	DIR				*dir_stream;
	struct dirent	*file;
	struct stat		buffer;
	t_node			*current_node;
	char			*tmp;
	int				recurse;

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
		tmp = create_full_path(node->full_path, file->d_name);


		if (lstat(tmp, &buffer) < 0)
			current_node = init_node(buffer, file->d_name, tmp, INVALID, errno);
		else if (S_ISDIR(buffer.st_mode) == 0)
			current_node = init_node(buffer, file->d_name, tmp, VALID, 0);
		else
			current_node = init_node(buffer, file->d_name, tmp, DIRECTORY, 0);
		
		node->total += buffer.st_blocks;
		add_node(&(node->subtree), current_node, cmp);
		if ((flags & 1 << R) && S_ISDIR(buffer.st_mode) && ft_strcmp(current_node->name, ".") && ft_strcmp(current_node->name, ".."))
				recurse = 1;
	}
	closedir(dir_stream);

	if (flags & 1 << R && recurse)
		parse_subtree(node->subtree, flags, cmp);
}





/*
// Need to check and see folder permissions. Error with /Library/Scripts/42.
// Need to check a folder that has some folders that are inaccessible.
void parse_dir(t_node *node, unsigned char flags, int (*sorting_function)(t_node *, t_node *))
{
	DIR				*dir;
	struct dirent	*file;
	struct stat		buffer;
	t_node			*current_node;
	char			*tmp;
	int				has_dir;
	int				lstat_value;

	has_dir = 0;
	// If it can't open, means user does not have permissions to open directory, is an invalid path, or is a file.
	if (!(dir = opendir(node->full_path)))
	{
		node->error = errno;
		return ;
	}
	while ((file = readdir(dir)))
	{
		if (!(flags & 1 << a) && file->d_name[0] == '.')
			continue;
		tmp = create_full_path(node->full_path, file->d_name);
		lstat_value = lstat(tmp, &buffer);
		if (lstat_value < 0)
		{
			current_node = init_node(buffer, file->d_name, tmp, INVALID, errno);
			add_node(&(node->subtree), current_node, sorting_function);
		}
		else
		{
			node->total += buffer.st_blocks;
			current_node = init_node(buffer, file->d_name, tmp, VALID, 0);
			add_node(&(node->subtree), current_node, sorting_function);
			if ((flags & 1 << R) && S_ISDIR(buffer.st_mode) && \
					ft_strcmp(current_node->name, ".") && ft_strcmp(current_node->name, ".."))
				has_dir = 1;
		}
	}
	closedir(dir);

	if (flags & 1 << R && has_dir)
		parse_subtree(node->subtree, flags, sorting_function);
}
*/
