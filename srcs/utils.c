/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:53:57 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/07 16:20:02 by jtollena         ###   ########.fr       */
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
