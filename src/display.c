/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 19:25:57 by tcho              #+#    #+#             */
/*   Updated: 2019/04/11 06:04:28 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "ls.h"
#include "ft_printf.h"
#include "b_printf.h"

int g_print_name = 0;

void	print_invalid(t_node *current)
{
	if (!current)
		return ;
	g_print_name = 1;
	print_invalid(current->left);
	printf("ls: %s: %s\n", current->name, strerror(current->error));
	print_invalid(current->right);
}

int		print_files(t_node *current, unsigned char flags)
{
	if (!current)
		return (0);
	print_files(current->left, flags);
	if (!current->error)
	{
		g_print_name = 1;
		if (flags & 1 << l)
		{
			b_printf("%s  %u  %s  %s  ", current->mode, current->links,
					current->user, current->group);
			print_major_minor(current);
			b_printf("\t%s ", current->time);
		}
		b_printf("%s\t", current->name);
		if (flags & 1 << l && current->linkname)
			printf(" -> %s\n", current->linkname);
		else
			printf("\n");
	}
	print_files(current->right, flags);
	return (1);
}

int		print_directories(t_node *current, unsigned char flags,
		int print_name, int print_newline)
{
	if (!current)
		return (print_newline);
	if (print_name || current->left || current->right)
		print_name = 1;
	print_newline = print_directories(current->left, flags, print_name,
			print_newline);
	if (print_newline)
		printf("\n");
	print_newline = 1;
	if (print_name || current->left || current->right || g_print_name)
		printf("%s:\n", current->name);
	if (flags & 1 << l && current->total)
		printf("total %lld\n", current->total);
	if (current->error)
		printf("ls: %s: %s\n", current->name, strerror(current->error));
	else
		print_files(current->subtree, flags);
	print_newline = print_directories(current->right, flags, print_name,
			print_newline);
	return (print_newline);
}

int		print_recursive(t_node *c, unsigned char flags, int p_name, int p_line)
{
	if (!c)
		return (p_line);
	if (p_name || c->left || c->right)
		p_name = 1;
	p_line = print_recursive(c->left, flags, p_name, p_line);
	if (c->type == DIRECTORY && c->display)
	{
		if (p_line)
			printf("\n");
		p_line = 1;
		if (p_name || c->left || c->right)
			printf("%s:\n", c->full_path ? c->full_path : c->name);
		if (flags & 1 << l && c->subtree && !c->error)
			printf("total %lld\n", c->total);
		if (c->error && !(flags & 1 << l) && !(flags & 1 << R))
			printf("ls: %s: %s\n", c->name, strerror(c->error));
		else
			print_files(c->subtree, flags);
		p_line = print_recursive(c->subtree, flags, p_name, p_line);
	}
	p_line = print_recursive(c->right, flags, p_name, p_line);
	return (p_line);
}

void	print_major_minor(t_node *current)
{
	if (current->device || current->mode[0] == 'c' || current->mode[0] == 'b')
	{
		b_printf("%u, ", current->major);
		b_printf("%u\t ", current->minor);
	}
	else
		b_printf("%d\t ", current->size);
}
