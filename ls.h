/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcho <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 01:20:41 by tcho              #+#    #+#             */
/*   Updated: 2019/02/06 03:50:30 by tcho             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
#define LS_H

#define MALLOC_CHECK(x) if ((x) == NULL) return NULL

typedef struct s_node t_node;
typedef struct s_trees t_trees;

struct	s_node {
	char	*name;
	t_node	*left;
	t_node	*right;
	t_node	*subtree;
};

struct	s_trees {
	t_node	*invalid;
	t_node	*valid;
	t_node	*directory;
};

enum e_flags { l, a, r, t, R };

int		error(char *message, int code);
int		update_flag(char f, unsigned char *flags);
int		check_flags(char ***argv, unsigned char *flags);
t_node	*init_node(struct stat buffer, char *name);
t_trees	*init_tree();
void	add_node(t_node **root, t_node *node);
void	parent_add_node(t_trees *trees, char *name, unsigned char flags);
void	parse_args(char ***argv, unsigned char flags, t_trees *trees);
void	parse_dir(t_node *node, unsigned char flags);

#endif
