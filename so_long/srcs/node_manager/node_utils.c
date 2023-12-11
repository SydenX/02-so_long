/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:13:16 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/11 13:33:20 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	get_list_size(t_node *list)
{
	t_node	*cpy;
	int		i;

	i = 0;
	cpy = list;
	while (cpy->type != NULLT)
	{
		i++;
		cpy++;
	}
	return (i);
}

int	get_list_xlen(t_node *list)
{
	t_node	*cpy;
	int		lastx;

	lastx = 0;
	cpy = list;
	while (cpy->type != NULLT)
	{
		if (cpy->x > lastx)
			lastx = cpy->x;
		cpy++;
	}
	return (lastx + 1);
}

int	get_list_ylen(t_node *list)
{
	t_node	*cpy;
	int		lasty;

	lasty = 0;
	cpy = list;
	while (cpy->type != NULLT)
	{
		if (cpy->y > lasty)
			lasty = cpy->y;
		cpy++;
	}
	return (lasty + 1);
}

int	is_node_free(int x, int y, t_data *data)
{
	t_node	*node;
	t_img	*img;

	node = get_node_at(data->nodes, x, y);
	if (node->type == FLOOR || node->type == SPAWN)
		return (1);
	if (node->type == EXIT && !collectibles_left(data->imgs))
		exit_win("You have reached the exit with all mushrooms ! GG",
			data, " -= VICTORY =-");
	if (node->type == COLLECTIBLE)
	{
		img = get_img_at(data->imgs, x, y, 0);
		img->type = FLOOR;
		mlx_destroy_image(data->prog->mlx, img->img);
		img->img = get_image(data->prog, FLOOR);
		return (1);
	}
	if (node->type == WALL)
		return (0);
	return (0);
}
