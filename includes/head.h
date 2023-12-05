/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   head.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:56:19 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/05 17:13:23 by jtollena         ###   ########.fr       */
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

# define SIZE 16

typedef enum e_type {
	FLOOR,
	WALL,
	SPAWN,
	EXIT,
	COLLECTIBLE
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
void	 exit_error(char *error, t_prog *prog);
void	 error_surrounded_by_walls(char *lastline);
int		surr_checks(char *reader);
int		surr_check_firstline(char *reader);
int		rgb_to_hex(int red, int green, int blue);
void	ft_nodeadd_back(t_node **list, t_node *new);

#endif