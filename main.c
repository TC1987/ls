/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 04:08:26 by tcho              #+#    #+#             */
/*   Updated: 2019/02/08 02:37:07 by tcho             ###   ########.fr       */
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
// How to determine if a node is a directory or not for printing? Currently doing node->is_dir = 1 which is ghetto. How else to determine if directory node?


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

	printf("----- INVALID -----\n");
	print_invalid(trees->invalid);
	printf("----- VALID -----\n");	
	print_files(trees->valid);
	printf("----- DIRECTORY -----\n");
	if (flags & 1 << R)
		print_recursive(trees->directory);
	else
		print_directories(trees->directory);
	// free();
}
