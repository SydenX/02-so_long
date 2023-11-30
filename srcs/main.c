/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2023/11/30 15:23:54 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
#include <stdio.h>

int main()
{
    // Creating a window with specified size and title
    void    *mlx = mlx_init();
    void    *win = mlx_new_window(mlx, 640, 360, "test");

    // drawing pixels at location with a rgb color!
    mlx_pixel_put(mlx, win, 640/2, 360/2, rgb_to_hex(255, 0, 0));

    // listening to any events
    mlx_loop(mlx);
    return 0;
}