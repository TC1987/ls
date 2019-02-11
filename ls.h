/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 01:20:41 by tcho              #+#    #+#             */
/*   Updated: 2019/02/11 07:48:56 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
#define LS_H

#include <sys/stat.h>

#define NULL_CHECK(x) if ((x) == NULL) return NULL

typedef struct s_node t_node;
typedef struct s_trees t_trees;

struct	s_node {
	char			*name;
	char			*full_path;
	t_node			*left;
	t_node			*right;
	t_node			*subtree;
	char			*time;
	char			*mode;
	char			*linkname;
	char			*group;
	char			*user;
	long long		size;
	unsigned short	links;
	long long		total;
	long			numtime;
	long			nanoseconds;
	unsigned int	device;
	unsigned int	major;
	unsigned int	minor;
	int	type;
};

struct	s_trees {
	t_node	*invalid;
	t_node	*valid;
	t_node	*directory;
};

enum e_flags { l, a, r, t, R };
enum e_type { NONE, VALID, INVALID, DIRECTORY };

int		error(char *message, int code);
int		update_flag(char f, unsigned char *flags);
int		check_flags(char ***argv, unsigned char *flags);
t_node	*init_node(struct stat buffer, char *name, char *full_path, int type);
t_trees	*init_tree(void);
void	init_properties(struct stat buffer, t_node *node, char *full_path);
t_node	*add_node(t_node **root, t_node *node, int (*cmp)(t_node *, t_node *));
void	parent_add_node(t_trees *trees, char *name, unsigned char flags);
void	parse_args(char ***argv, unsigned char flags, t_trees *trees);
void	parse_dir(t_node *node, unsigned char flags, int (*sorting_function)(t_node *, t_node *));
void	print_invalid(t_node *current);
int		print_files(t_node *current, unsigned char flags);
void	print_directories(t_node *current, unsigned char flags, int print_name);
void	print_recursive(t_node *current, unsigned char flags, int print_name);

// long_format.c
char	*get_mode(struct stat buffer);
char	*get_extra(char *mode, struct stat buffer);
char	*get_first(char *mode, struct stat buffer);
char	*time_clean(char *src_time, long numtime);
void	print_major_minor(t_node *current);

// compare.c
int		ft_timecmp(t_node *n1, t_node *n2);
int		ft_timecmp_r(t_node *n1, t_node *n2);
int		ft_lexcmp(t_node *n1, t_node *n2);
int		ft_lexcmp_r(t_node *n1, t_node *n2);

// main.c
int		(*get_sorting_function(unsigned char flags))(t_node *, t_node *);

#endif
