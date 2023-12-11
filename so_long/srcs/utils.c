/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:53:57 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/11 11:52:26 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	rgb_to_hex(int red, int green, int blue)
{
	int	hex;

	hex = red * 65536 + green * 256 + blue;
	return (hex);
}

int	absolute(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}

int	collectibles_left(t_img *list)
{
	t_img	*cpy;

	cpy = list;
	while (cpy->type != NULLT)
	{
		if (cpy->type == COLLECTIBLE)
			return (1);
		cpy++;
	}
	return (0);
}

void	move_player(int key, t_data *data)
{
	t_img	*oldimg;
	t_img	moved;

	oldimg = get_player_image(data);
	moved = *oldimg;
	if ((key == KEY_W || key == KEY_UP)
		&& is_node_free(oldimg->x, oldimg->y - 1, data) == 1)
		oldimg->y -= 1;
	else if ((key == KEY_S || key == KEY_DOWN)
		&& is_node_free(oldimg->x, oldimg->y + 1, data) == 1)
		oldimg->y += 1;
	else if ((key == KEY_A || key == KEY_LEFT)
		&& is_node_free(oldimg->x - 1, oldimg->y, data) == 1)
		oldimg->x -= 1;
	else if ((key == KEY_D || key == KEY_RIGHT)
		&& is_node_free(oldimg->x + 1, oldimg->y, data) == 1)
		oldimg->x += 1;
	if (moved.y != oldimg->y || moved.x != oldimg->x)
	{
		data->moves++;
		mlx_destroy_image(data->prog->mlx, oldimg->img);
		oldimg->img = get_image(data->prog, SPAWN);
		map_init(data);
	}
}

int	event_key_pressed(int keycode, t_data *data)
{
	if (keycode == KEY_W || keycode == KEY_A 
		|| keycode == KEY_D || keycode == KEY_S
		|| keycode == KEY_UP || keycode == KEY_RIGHT 
		|| keycode == KEY_LEFT || keycode == KEY_DOWN)
		move_player(keycode, data);
	else if (keycode == KEY_ESCAPE)
		close_window(data);
	return (1);
}
