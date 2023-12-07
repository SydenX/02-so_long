/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetol <jetol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 20:43:28 by jetol             #+#    #+#             */
/*   Updated: 2023/12/06 20:50:30 by jetol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	pathf_setup_h(t_node *list)
{
	t_node	exit;
	t_node	*cpy;
	int		xdiff;
	int		ydiff;

	exit = find_exit_point(list);
	cpy = list;
	while (cpy->type != NULLT)
	{
		if (cpy->type == FLOOR || cpy->type == COLLECTIBLE)
		{
			xdiff = absolute(cpy->x - exit.x);
			ydiff = absolute(cpy->y - exit.y);
			cpy->h = xdiff + ydiff;
		}
		cpy++;
	}
}

int	check_precisely(t_node current, t_node *list, int x, int y)
{
	t_node	newnode;

	newnode = get_node_at(list, x, y);
	if (newnode.x == 0 || newnode.y == 0)
		return (0);
	if (newnode.type == EXIT)
		return (1);
	if (newnode.f > 0)
		return (0);
	newnode.g = current.g + 1;
	newnode.f = newnode.h + newnode.g;
	update_node(newnode, list);
	if (newnode.type == FLOOR || newnode.type == COLLECTIBLE)
		return (check_arround(newnode, list));
	return (0);
}

int	check_arround(t_node node, t_node *list)
{
	if (check_precisely(node, list, node.x, node.y + 1) == 0
		&& check_precisely(node, list, node.x, node.y - 1) == 0
		&& check_precisely(node, list, node.x + 1, node.y) == 0
		&& check_precisely(node, list, node.x - 1, node.y) == 0)
		return (0);
	return (1);
}

void	reset_node(t_node *list)
{
	t_node	*cpy;

	cpy = list;
	while (cpy->type != NULLT)
	{
		cpy->g = 0;
		cpy->f = 0;
		cpy++;
	}
}

void	pathf_run(t_node *list)
{
	t_node	spawn;
	t_node	*cpy;
	int		lstsize;
	int		checked;

	cpy = list;
	lstsize = get_list_size(list);
	while (cpy->type != NULLT)
	{
		if (cpy->type == COLLECTIBLE || cpy->type == SPAWN)
		{
			checked = check_arround(*cpy, list);
			if (checked == 0)
				error_nopathfound(list, NULL);
			reset_node(list);
		}
		cpy++;
	}
}
