/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 01:20:41 by tcho              #+#    #+#             */
/*   Updated: 2019/04/10 05:10:10 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include <sys/stat.h>

# define NULL_CHECK(x) if ((x) == NULL) return NULL

typedef	struct s_node	t_node;
typedef struct s_trees	t_trees;
typedef int	(t_func)(t_node *, t_node *);

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
	int				type;
	int				error;
};

struct	s_trees {
	t_node	*invalid;
	t_node	*valid;
	t_node	*directory;
};

enum	e_flags { l, a, r, t, R };
enum	e_type { NONE, INVALID, VALID, DIRECTORY };
enum	e_bools { FALSE, TRUE };

int		error(char *message, int code);
int		update_flag(char f, unsigned char *flags);
int		check_flags(char ***argv, unsigned char *flags);
t_node	*init_node(struct stat buffer, char *full_path, int type, int error);
t_trees	*init_tree(void);
void	init_properties(struct stat buffer, t_node *node);
void	add_node(t_node **root, t_node *node, int (*cmp)(t_node *, t_node *));
void	parent_add_node(t_trees *trees, char *name, unsigned char flags);
void	parse_args(char ***argv, unsigned char flags, t_trees *trees);
void	parse_dir(t_node *node, unsigned char flags,
			int (*sorting_function)(t_node *, t_node *));
void	print_invalid(t_node *current);
int		print_files(t_node *current, unsigned char flags);
int		print_directories(t_node *current, unsigned char flags, int print_name,
			int print_newline);
int		print_recursive(t_node *c, unsigned char flags, int p_name, int p_line);
char	*get_mode(struct stat buffer);
char	*get_extra(char *mode, struct stat buffer);
char	*get_first(char *mode, struct stat buffer);
char	*time_clean(struct stat buffer);
void	print_major_minor(t_node *current);
int		ft_timecmp(t_node *n1, t_node *n2);
int		ft_timecmp_r(t_node *n1, t_node *n2);
int		ft_lexcmp(t_node *n1, t_node *n2);
int		ft_lexcmp_r(t_node *n1, t_node *n2);
char	*get_linkname(char *full_path);
char	*get_user(struct stat buffer);
char	*get_group(struct stat buffer);

#endif
