/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:56:14 by jetol             #+#    #+#             */
/*   Updated: 2023/12/07 15:43:12 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

t_node	create_node(char name, int x, int y)
{
	t_node	new;

	new.x = x;
	new.y = y;
    new.f = 0;
    new.g = 0;
	if (name == '1')
		new.type = WALL;
	else if (name == '0')
		new.type = FLOOR;
	else if (name == 'P')
    {
        new.f = 10000;
		new.type = SPAWN;
    }
	else if (name == 'E')
		new.type = EXIT;
	else if (name == 'C')
		new.type = COLLECTIBLE;
	else if (name == 1)
		new.type = NULLT;
	else
		new.type = 0;
	return (new);
}

t_node	find_exit_point(t_node *list)
{
	t_node	*cpy;

	cpy = list;
	while (cpy->type != NULLT)
	{
		if (cpy->type == EXIT)
			return (*cpy);
		cpy++;
	}
	return (*cpy);
}

t_node	find_spawn_point(t_node *list)
{
	t_node	*cpy;

	cpy = list;
	while (cpy->type != NULLT)
	{
		if (cpy->type == SPAWN)
			return (*cpy);
		cpy++;
	}
	return (*cpy);
}
t_node	*get_node_at(t_node *list, int x, int y)
{
	t_node	*cpy;
	int		i;

	i = 0;
	cpy = list;
	while (cpy->type != NULLT)
	{
		if (cpy->x == x && cpy->y == y)
            return (&list[i]);
		i++;
		cpy++;
	}
	return (list);
}

int	update_node(t_node node, t_node *list)
{
	t_node	*cpy;

	cpy = list;
	while (cpy->type != NULLT)
	{
		if (cpy->x == node.x && cpy->y == node.y)
        {
            *cpy = node;
            return (1);
        }
		cpy++;
	}
	return (0);
}

int	get_list_size(t_node *list)
{
	t_node	*cpy;
    int     i;

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
    int     lastx;

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
    int     lasty;

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
