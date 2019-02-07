/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 04:08:26 by tcho              #+#    #+#             */
/*   Updated: 2019/02/07 04:58:06 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <libft.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "ls.h"

// Using add_file_node for a directory's contents, even if it's a directory.
// For printing, use function pointers.
// 2. Need to append full path for recursive calls.

int error(char *message, int code)
{
	printf("%s\n", message);
	return (code);
}

int main(int argc, char *argv[])
{
	unsigned char flags;
	t_trees *trees;

	flags = 0;
	trees = init_tree();
	if (!check_flags(&argv, &flags))
		return error("ls: illegal option\nusage: ls [-lartR] [file ...]", 0);
	parse_args(&argv, flags, trees);

	if (flags & 1 << R)
		display_recursive(trees->directory);

	printf("----- INVALID -----\n");
	display_files(trees->invalid);
	printf("----- VALID -----\n");	
	display_files(trees->valid);
	printf("----- DIRECTORY -----\n");
	display_directories(trees->directory);
	//	printf("--------------------------\n");
	//	display_files_reverse(trees->invalid);
	//	display_files_reverse(trees->valid);

	// parse_dir(flags);

	// free(&head);
}
