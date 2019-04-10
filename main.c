/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 04:08:26 by tcho              #+#    #+#             */
/*   Updated: 2019/04/10 04:45:08 by tcho             ###   ########.fr       */
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

// -Rl /Library/Scripts/42/
// Printing directories where you don't have permission is fucked.
// Printing -R is fucked. No space between files and directories list.
// For printing, use function pointers.
// How to determine if a node is a directory or not for printing? Currently doing node->is_dir = 1 which is ghetto. How else to determine if directory node?
// Print symbolic links.

int error(char *message, int code)
{
	printf("%s\n", message);
	return (code);
}

int main(int argc, char *argv[])
{
	unsigned char flags;
	t_trees *trees;
	int print_name;

	argc = 0;
	flags = 0;
	if (!(trees = init_tree()))
		return (0);
	if (!check_flags(&argv, &flags))
		return error("ls: illegal option\nusage: ls [-lartR] [file ...]", 0);
	parse_args(&argv, flags, trees);
	print_invalid(trees->invalid);
	print_name = print_files(trees->valid, flags);
	if (flags & 1 << R)
		print_recursive(trees->directory, flags, print_name, print_name);
	else
		print_directories(trees->directory, flags, print_name, print_name);
	// free();
}
