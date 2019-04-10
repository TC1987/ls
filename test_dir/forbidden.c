/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forbidden.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 05:12:59 by tcho              #+#    #+#             */
/*   Updated: 2019/04/10 05:27:07 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		DIR *dir_stream;
		struct dirent *file;

		dir_stream = opendir(argv[1]);
		while ((file = readdir(dir_stream)))
			printf("%s\n", file->d_name);
		closedir(dir_stream);
	}
}
