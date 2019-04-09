/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:20:58 by tcho              #+#    #+#             */
/*   Updated: 2019/04/09 06:56:57 by tcho             ###   ########.fr       */
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

char	*get_linkname(char *full_path)
{
	char	*linkname;
	ssize_t	read;

	NULL_CHECK((linkname = (char *)malloc(sizeof(char) * 512)));
	if ((read = readlink(full_path, linkname, 512)) == -1)
	{
		free(linkname);
		return (NULL);
	}
	linkname[read] = '\0';
	return (linkname);
}

t_node	*init_node(struct stat buffer, char *name, char *full_path, int type, int errno_code)
{
	t_node *node;

	NULL_CHECK((node = (t_node *)malloc(sizeof(t_node))));
	node->name = ft_strdup(name);
	node->full_path = full_path;
	node->left = NULL;
	node->right = NULL;
	node->type = type;
	node->error = errno_code;
	if ((type == VALID || type == DIRECTORY) && !errno_code)
		init_properties(buffer, node, full_path);
	return (node);
}

char	*get_user(struct stat buffer)
{
	struct passwd *passwd_struct;

	passwd_struct = getpwuid(buffer.st_uid);
	if (passwd_struct)
	{
		if (passwd_struct->pw_name)
			return (ft_strdup(passwd_struct->pw_name));
		if (passwd_struct->pw_uid)
			return (ft_itoa(passwd_struct->pw_uid));
	}
	return (NULL);
}

char	*get_group(struct stat buffer)
{
	struct group *group_struct;

	group_struct = getgrgid(buffer.st_gid);
	if (group_struct)
		return (ft_strdup(group_struct->gr_name));
	return (NULL);
}

void	init_properties(struct stat buffer, t_node *node, char *full_path)
{
	node->subtree = NULL;
	node->time = time_clean(buffer);
	node->mode = get_mode(buffer);
	node->linkname = get_linkname(full_path);
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
