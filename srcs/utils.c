/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetol <jetol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:53:57 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/06 11:55:19 by jetol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int rgb_to_hex(int red, int green, int blue)
{
    int hex;

	hex = red*65536+green*256+blue;
    return (hex);
}

int		absolute(int i)
{
	if (i < 0)
		return (-i);
	return (i);
}
