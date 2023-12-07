/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetol <jetol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:56:19 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/06 20:49:33 by jetol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_H
# define HEAD_H

# include "keymap.h"
# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
#include <stdio.h>

# define SIZE 16

typedef enum e_type {
	FLOOR,
	WALL,
	SPAWN,
	EXIT,
	COLLECTIBLE,
	NULLT
}	t_type;

typedef struct s_prog {
	void	*mlx;
	void	*win;
}	t_prog;

typedef struct s_node {
	int				x;
	int				y;
	int				h;
	int				g;
	int				f;
	t_type			type;
}	t_node;

t_node	*check_nodes_type(t_node *nodes, int size);
int		linesize_checks(char *reader);
void	exit_error(char *error, t_prog *prog, void *toFree, void *toFree2);
void	error_surrounded_by_walls(void *toFree, void *toFree2);
void	error_notcorrectinterest(void *toFree, void *toFree2);
void	error_nopathfound(void *toFree, void *toFree2);
int		surr_checks(char *reader);
int		surr_check_firstline(char *reader);
int		rgb_to_hex(int red, int green, int blue);
int		absolute(int i);
void	ft_nodeadd_back(t_node **list, t_node *new);
void	error_inputfile(void *toFree, void *toFree2);
void	error_notformatted(void *toFree, void *toFree2);
int		node_size(char *path);
int		file_chars(char *path);
int		get_fd(char *path, void *toFree, void *toFree2);
t_node	create_node(char name, int x, int y);
t_node	find_exit_point(t_node *list);
t_node	find_spawn_point(t_node *list);
t_node	get_node_at(t_node *list, int x, int y);
int		get_list_size(t_node *list);
int		check_arround(t_node node, t_node *list);
int		update_node(t_node node, t_node *list);
void	pathf_run(t_node *list);
void	pathf_setup_h(t_node *list);

#endif