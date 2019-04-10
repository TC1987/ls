/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forbidden.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:12:59 by tcho              #+#    #+#             */
/*   Updated: 2019/04/10 05:44:45 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen(s1) +
						ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		DIR *dir_stream;
		struct dirent *file;
		int lstat_result;
		char *full_path;

		dir_stream = opendir(argv[1]);
		while ((file = readdir(dir_stream)))
		{
			full_path = ft_strjoin(argv[1], "/");
			full_path = ft_strjoin(full_path, file->d_name);
			lstat_result = lstat(full_path);
			if (lstat_result == -1)
				printf("ERROR\n");
		}
		closedir(dir_stream);
	}
}
