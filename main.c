/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 04:08:26 by tcho              #+#    #+#             */
/*   Updated: 2019/02/11 07:11:45 by tcho             ###   ########.fr       */
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

// For printing, use function pointers.
// How to determine if a node is a directory or not for printing? Currently doing node->is_dir = 1 which is ghetto. How else to determine if directory node?
// Print symbolic links.

int error(char *message, int code)
{
	printf("%s\n", message);
	return (code);
}

int (*get_sorting_function(unsigned char flags))(t_node *, t_node *)
{
	if (flags & 1 << r && flags & 1 << t)
		return (ft_timecmp_r);
	else if (flags & 1 << r)
		return (ft_lexcmp_r);
	else if (flags & 1 << t)
		return (ft_timecmp);
	else
		return (ft_lexcmp);
}

int main(int argc, char *argv[])
{
	unsigned char flags;
	int error_code;
	t_trees *trees;
	int print_name;

	flags = 0;
	if (!(trees = init_tree()))
		return (0);
	if (!check_flags(&argv, &flags))
		return error("ls: illegal option\nusage: ls [-lartR] [file ...]", 0);
	parse_args(&argv, flags, trees);
	print_invalid(trees->invalid);
	print_name = print_files(trees->valid, flags);
	if (flags & 1 << R)
		print_recursive(trees->directory, flags, print_name);
	else
		print_directories(trees->directory, flags, print_name);
	// free();
}
