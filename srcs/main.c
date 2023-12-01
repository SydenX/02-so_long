/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/01 12:28:13 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int close_window(int keycode, t_prog *prog)
{
    if (keycode == KEY_ESCAPE)
    {
        mlx_clear_window(prog->mlx, prog->win);
        mlx_destroy_window(prog->mlx, prog->win);
    }
    return (0);
}

int main()
{
    t_prog prog;
    // Creating a window with specified size and title
    prog.mlx = mlx_init();
    if (prog.mlx == NULL)
        return (0);
    prog.win = mlx_new_window(prog.mlx, 1920/2, 1080/2, "test");
    if (prog.mlx == NULL)
        return (0);

    // drawing pixels at location with a rgb color!
    mlx_pixel_put(prog.mlx, prog.win, 640/2, 360/2, rgb_to_hex(255, 0, 0));
    mlx_key_hook(prog.win, close_window, &prog);
    int img_width;
    int img_height;
    void *img = mlx_xpm_file_to_image(prog.mlx, "img/grass.xpm", &img_width, &img_height);
    if (img == NULL)
        return (close_window(KEY_ESCAPE, &prog), 0);
    mlx_put_image_to_window(prog.mlx, prog.win, img, 0, 0);
    ft_printf("%d %d", img_height, img_width);
    // listening to any events
    mlx_loop(prog.mlx);
    return 0;
}