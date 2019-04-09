/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 17:38:22 by tcho              #+#    #+#             */
/*   Updated: 2019/04/09 07:16:44 by tcho             ###   ########.fr       */
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

char	*get_mode(struct stat buffer)
{
	char	*mode;
	int		n;

	n = 1;
	if (!(mode = (char *)malloc(sizeof(char) * 11)))
		return (NULL);
	mode[n++] = (buffer.st_mode & S_IRUSR) ? 'r' : '-';
	mode[n++] = (buffer.st_mode & S_IWUSR) ? 'w' : '-';
	mode[n++] = (buffer.st_mode & S_IXUSR) ? 'x' : '-';
	mode[n++] = (buffer.st_mode & S_IRGRP) ? 'r' : '-';
	mode[n++] = (buffer.st_mode & S_IWGRP) ? 'w' : '-';
	mode[n++] = (buffer.st_mode & S_IXGRP) ? 'x' : '-';
	mode[n++] = (buffer.st_mode & S_IROTH) ? 'r' : '-';
	mode[n++] = (buffer.st_mode & S_IWOTH) ? 'w' : '-';
	mode[n++] = (buffer.st_mode & S_IXOTH) ? 'x' : '-';
	mode[n] = '\0';
	mode = get_extra(mode, buffer);
	return (mode);
}

char	*get_extra(char *mode, struct stat buffer)
{
	if (!mode)
		return (NULL);
	if (buffer.st_mode & S_ISUID)
		mode[3] = mode[3] == '-' ? 'S' : 's';
	if (buffer.st_mode & S_ISGID)
		mode[6] = mode[6] == '-' ? 'S' : 's';
	if (buffer.st_mode & S_ISVTX)
		mode[9] = mode[9] == '-' ? 'T' : 't';
	mode = get_first(mode, buffer);
	return (mode);
}

char	*get_first(char *mode, struct stat buffer)
{
	if (S_ISBLK(buffer.st_mode))
		mode[0] = 'b';
	else if (S_ISCHR(buffer.st_mode))
		mode[0] = 'c';
	else if (S_ISDIR(buffer.st_mode))
		mode[0] = 'd';
	else if (S_ISLNK(buffer.st_mode))
		mode[0] = 'l';
	else if (S_ISSOCK(buffer.st_mode))
		mode[0] = 's';
	else if (S_ISFIFO(buffer.st_mode))
		mode[0] = 'P';
	else
		mode[0] = '-';
	return (mode);
}

char	*time_clean(struct stat buffer)
{
	char *dst_time;
	char *time_string;

	time_string = ctime(&buffer.st_mtime);
	if (!time_string || !(dst_time = ft_strnew(12)))
		return (NULL);
	if ((time(NULL) - buffer.st_mtime) < 15778800)
		ft_strncat(dst_time, time_string + 4, 12);
	else
	{
		ft_strncat(dst_time, time_string + 4, 7);
		ft_strncat(dst_time, time_string + 20, 4);
	}
	return (dst_time);
}
