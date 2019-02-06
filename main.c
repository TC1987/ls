/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 04:08:26 by tcho              #+#    #+#             */
/*   Updated: 2019/02/06 02:23:12 by tcho             ###   ########.fr       */
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

int error(char *message, int code)
{
	printf("%s\n", message);
	return (code);
}

int update_flag(char f, unsigned char *flags)
{
	if (f == 'l')
		return *flags |= 1 << l;
	if (f == 'a')
		return *flags |= 1 << a;
	if (f == 'r')
		return *flags |= 1 << r;
	if (f == 't')
		return *flags |= 1 << t;
	if (f == 'R')
		return *flags |= 1 << R;
	return (0);
}

int check_flags(char ***argv, unsigned char *flags)
{
	while (*(++(*argv)) && ***argv == '-')
		while (*(++(**argv)))
			if (!update_flag(***argv, flags))
				return (0);
	return (1);
}

// Need to ft_strdup here or should I do it in the function that calls this function and then pass the name?
t_node *init_node(struct stat buffer, char *name)
{
    t_node *node;

    if (!(node = (t_node *)malloc(sizeof(t_node))))
        return NULL;
	/*
   	if (index)
    {
        node->time = time_clean(ft_strdup(ctime(&buffer.st_mtime)), buffer.st_mtime);
		node->nanoseconds = buffer.st_mtimespec.tv_nsec;
        node->mode = get_mode();
        node->group = ft_strdup(getgrgid(g_buffer.st_gid)->gr_name);
        node->user = ft_strdup(getpwuid(g_buffer.st_uid)->pw_name);
        node->size = buffer.st_size;
        node->links = buffer.st_nlink;
        node->numtime = buffer.st_mtime;
		node->linkname = NULL;
		node->device = buffer.st_rdev;
		node->major = major(buffer.st_rdev);
		node->minor = minor(buffer.st_rdev);
	}
	*/
    node->name = ft_strdup(name);
	node->left = NULL;
	node->right = NULL;
	node->subtree = NULL;
    return (node);
}

t_trees *init_tree()
{
	t_trees *tree;

	MALLOC_CHECK((tree = malloc(sizeof(t_trees))));
	tree->invalid = NULL;
	tree->valid = NULL;
	tree->directory = NULL;
	return (tree);
}

// Adding to either the invalid or valid tree.
t_node *add_file_node(t_node **current, t_node *node)
{
	if (*current == NULL)
		return *current = node;
	if (ft_strcmp((*current)->name, node->name) > 0)
	{
		if ((*current)->left == NULL)
			return (*current)->left = node;
		add_file_node(&(*current)->left, node);
	}
	else
	{
		if ((*current)->right == NULL)
			return (*current)->right = node;
		add_file_node(&(*current)->right, node);
	}
	return (node);
}

// Adding to the directory tree.
void add_directory_node(t_node **root, t_node *node, unsigned char flags)
{
	static int create_sub = 0;

	if (*root == NULL)
		*root = node;
	else if (ft_strcmp((*root)->name, node->name) > 0)
	{
		if ((*root)->left == NULL)
			(*root)->left = node;
		else
			add_directory_node(&(*root)->left, node, flags);
	}
	else
	{
		if ((*root)->right == NULL)
			(*root)->right = node;
		else
			add_directory_node(&(*root)->right, node, flags);
	}
	if (create_sub == 0)
	{
		create_sub = 1;
		parse_dir(node, flags);
	}
}

void add_node(t_trees *trees, char *name, unsigned char flags)
{
	struct stat buffer;
	int lstat_result;

	lstat_result = lstat(name, &buffer);

	if (lstat_result < 0)
		add_file_node(&(trees->invalid), init_node(buffer, name));
	else if (S_ISDIR(buffer.st_mode) == 0)
		add_file_node(&(trees->valid), init_node(buffer, name));
	else
		add_directory_node(&(trees->directory), init_node(buffer, name), flags);
}

void parse_args(char ***argv, unsigned char flags, t_trees *trees)
{
	struct stat buffer;
	int lstat_result;

	if (**argv == NULL)
	{
		add_node(trees, ".", flags);
		return ;
	}
	while (**argv)
	{
		add_node(trees, **argv, flags); 
		(*argv)++;
	}
}

void parse_dir(t_node *node, unsigned char flags)
{
	DIR				*dir;
	struct dirent	*file;

	dir = opendir(".");
	node->subtree = init_tree();
	while ((file = readdir(dir)))
	{
		if (!(flags & a) && file->d_name[0] == '.')
			continue;
		add_node(node->subtree, file->d_name, flags);
	}

	closedir(dir);
}

void display(t_node *current)
{
	if (!current)
		return ;
	display(current->left);
	printf("%s\n", current->name);
	display(current->right);
}

void display_reverse(t_node *current)
{
	if (!current)
		return ;
	display_reverse(current->right);
	printf("%s\n", current->name);
	display_reverse(current->left);
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
	
	printf("----- VALID -----\n");	
	display(trees->directory->subtree->valid);
	printf("----- DIRECTORY -----\n");
	display(trees->directory->subtree->directory);
	// printf("--------------------------\n");
	// display_reverse(trees->directory->subtree->valid);
	// display_reverse(trees->directory->subtree->directory);
	
	// parse_dir(flags);

	// free(&head);
}
