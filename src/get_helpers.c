/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 02:43:30 by tcho              #+#    #+#             */
/*   Updated: 2019/04/10 03:06:01 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
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
