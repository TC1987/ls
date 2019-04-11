/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 04:08:26 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 00:32:03 by tcho             ###   ########.fr       */
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
#include "ft_printf.h"

// -Rl /Library/Scripts/42/
// Printing directories where you don't have permission is fucked.

int	error(char *message, int code)
{
	ft_printf("%s\n", message);
	return (code);
}

int	main(int argc, char *argv[])
{
	unsigned char	flags;
	t_trees			*trees;
	int				print_name;

	argc = 0;
	flags = 0;
	if (!(trees = init_tree()))
		return (0);
	if (!check_flags(&argv, &flags))
		return (error("ls: illegal option\nusage: ls [-lartR] [file ...]", 0));
	parse_args(&argv, flags, trees);
	print_invalid(trees->invalid);
	print_name = print_files(trees->valid, flags);
	if (flags & 1 << R)
		print_recursive(trees->directory, flags, print_name, print_name);
	else
		print_directories(trees->directory, flags, print_name, print_name);
}
