/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetol <jetol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:56:19 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/08 12:14:39 by jetol            ###   ########.fr       */
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

# define SIZE 64

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

typedef struct s_img {
	int				x;
	int				y;
	void			*img;
	t_type			type;
}	t_img;

typedef struct s_data {
	t_prog	*prog;
	t_node	*nodes;
	t_img 	*imgs;
	int		moves;
}	t_data;

//MAIN
void 	map_init(t_data *data);
//UTILS
int		collectibles_left(t_img *list);
int		rgb_to_hex(int red, int green, int blue);
int		absolute(int i);
//PATHFINDER
void	pathf_run(t_node *list);
void	pathf_setup_h(t_node *list);
int		check_arround(t_node node, t_node *list);
//NODESTYPE
t_node	*check_nodes_type(t_node *nodes, int size);
//LINESIZE
int		linesize_checks(char *reader);
//GET_SIZES
int		node_size(char *path);
int		file_chars(char *path);
int		get_fd(char *path, void *toFree, void *toFree2);
//SURROUNDED
void	error_surrounded_by_walls(void *toFree, void *toFree2);
int		surr_checks(char *reader);
int		surr_check_firstline(char *reader);
//IMAGES_1
t_img	*get_player_image(t_data *data);
t_img	*get_img_at(t_img *list, int x, int y, int isfloor);
t_img	create_image(int x, int y, t_type type, t_prog *prog);
t_img	*load_images(t_img *imgs, t_node *list, t_prog *prog);
void	*get_image(t_prog *prog, t_type type);
//ERROR_1
void	exit_error(char *error, t_prog *prog, void *toFree, void *toFree2);
void	error_notcorrectinterest(void *toFree, void *toFree2);
void	error_nopathfound(void *toFree, void *toFree2);
void	error_inputfile(void *toFree, void *toFree2);
void	error_notformatted(void *toFree, void *toFree2);
//NODE_1
t_node	create_node(char name, int x, int y);
t_node	find_exit_point(t_node *list);
t_node	find_spawn_point(t_node *list);
t_node	*get_node_at(t_node *list, int x, int y);
int		update_node(t_node node, t_node *list);
//NODE_UTILS
int		get_list_size(t_node *list);
int		get_list_xlen(t_node *list);
int		get_list_ylen(t_node *list);

#endif