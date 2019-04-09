/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctime.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 04:58:31 by tcho              #+#    #+#             */
/*   Updated: 2019/04/09 06:05:09 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if (argc == 2)
	{
		struct stat buffer;
		struct tm *tm_struct;
		char *file_time;

		lstat(argv[1], &buffer);
		file_time = ctime(&buffer.st_mtime);
		tm_struct = localtime(&buffer.st_mtime);
		printf("%s", file_time);
		printf("%ld\n", time(NULL) - buffer.st_mtime);

		printf("----------------------------\n");

		printf("%d\n", tm_struct->tm_sec);
	}
}
