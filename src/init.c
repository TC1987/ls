/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:20:58 by tcho              #+#    #+#             */
/*   Updated: 2019/02/09 03:31:20 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include "ls.h"
#include "libft.h"

char *get_linkname(struct stat buffer, char *full_path)
{
	ssize_t read;
	char *linkname;

	NULL_CHECK((linkname = (char *)malloc(sizeof(char) * 512)));
	if ((read = readlink(full_path, linkname, 512)) == -1)
	{
		free(linkname);
		return (NULL);
	}
	linkname[read] = '\0';
	return (linkname);
}

// Need to ft_strdup here or should I do it in the function that calls this function and then pass the name?
t_node *init_node(struct stat buffer, char *name, char *full_path)
{
    t_node *node;

    NULL_CHECK((node = (t_node *)malloc(sizeof(t_node))));
	node->time = time_clean(ft_strdup(ctime(&buffer.st_mtime)), buffer.st_mtime);
	node->nanoseconds = buffer.st_mtimespec.tv_nsec;
	node->mode = get_mode(buffer);
	node->group = ft_strdup(getgrgid(buffer.st_gid)->gr_name);
	node->user = ft_strdup(getpwuid(buffer.st_uid)->pw_name);
	node->size = buffer.st_size;
	node->links = buffer.st_nlink;
	node->numtime = buffer.st_mtime;
	node->linkname = get_linkname(buffer, full_path);
	node->device = buffer.st_rdev;
	node->major = major(buffer.st_rdev);
	node->minor = minor(buffer.st_rdev);
	node->name = ft_strdup(name);
	node->full_path = full_path;
	node->total = 0;
	node->left = NULL;
	node->right = NULL;
	node->subtree = NULL;
	node->type = NONE;
    return (node);
}

t_trees *init_tree()
{
	t_trees *tree;

	NULL_CHECK((tree = malloc(sizeof(t_trees))));
	tree->invalid = NULL;
	tree->valid = NULL;
	tree->directory = NULL;
	return (tree);
}
