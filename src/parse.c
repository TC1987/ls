/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:30:00 by tcho              #+#    #+#             */
/*   Updated: 2019/03/16 00:28:15 by tcho             ###   ########.fr       */
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

void parse_args(char ***argv, unsigned char flags, t_trees *trees)
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

#include <stdio.h>

char *create_full_path(char *str1, char *str2)
{
	size_t	str1Length;
	size_t	str2Length;
	char	*full_path;

	str1Length = ft_strlen(str1);
	str2Length = ft_strlen(str2);
	NULL_CHECK((full_path = ft_strnew(str1Length + str2Length + 1)));
	ft_strcat(full_path, str1);
	if (full_path[str1Length - 1] != '/')
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

void parse_dir(t_node *node, unsigned char flags, int (*cmp)(t_node *, t_node *))
{
	DIR				*dir_stream;
	struct dirent	*file;
	struct stat		buffer;
	t_node			*current_node;
	char			*tmp;
	int				recurse;
	t_node 			*tmp_tree;

	recurse = 0;
	tmp_tree = NULL;
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
		
		lstat(tmp, &buffer);	
		if (S_ISDIR(buffer.st_mode) == 0)
			current_node = init_node(buffer, file->d_name, tmp, VALID, 0);
		else
			current_node = init_node(buffer, file->d_name, tmp, DIRECTORY, 0);

		add_node(&(node->subtree), current_node, cmp);
		
		node->total += buffer.st_blocks;

		if ((flags & 1 << R) && ft_strcmp(current_node->name, ".") && ft_strcmp(current_node->name, ".."))
			recurse = 1;
	}
	
	closedir(dir_stream);
	
	if (recurse)
		parse_subtree(node->subtree, flags, cmp);
}
