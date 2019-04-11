/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:20:58 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 05:17:07 by tcho             ###   ########.fr       */
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
#include <uuid/uuid.h>
#include "ls.h"
#include "libft.h"

t_node	*init_node(struct stat buffer,
		char *full_path, int type, int errno_code)
{
	t_node *node;

	NULL_CHECK((node = (t_node *)malloc(sizeof(t_node))));
	node->name = NULL;
	node->full_path = full_path;
	node->left = NULL;
	node->right = NULL;
	node->type = type;
	node->error = errno_code;
	node->display = 1;
	if ((type == VALID || type == DIRECTORY) && !errno_code)
		init_properties(buffer, node);
	return (node);
}

void	init_properties(struct stat buffer, t_node *node)
{
	node->subtree = NULL;
	node->time = time_clean(buffer);
	node->mode = get_mode(buffer);
	node->linkname = get_linkname(node->full_path);
	node->group = get_group(buffer);
	node->user = get_user(buffer);
	node->size = buffer.st_size;
	node->links = buffer.st_nlink;
	node->total = 0;
	node->numtime = buffer.st_mtime;
	node->nanoseconds = buffer.st_mtimespec.tv_nsec;
	node->device = buffer.st_rdev;
	node->major = major(buffer.st_rdev);
	node->minor = minor(buffer.st_rdev);
}

t_trees	*init_tree(void)
{
	t_trees *tree;

	NULL_CHECK((tree = malloc(sizeof(t_trees))));
	tree->invalid = NULL;
	tree->valid = NULL;
	tree->directory = NULL;
	return (tree);
}
