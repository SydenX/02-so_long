/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/01 16:16:08 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int close_window(int keycode, t_prog *prog)
{
    if (keycode == KEY_ESCAPE)
    {
        mlx_clear_window(prog->mlx, prog->win);
        mlx_destroy_window(prog->mlx, prog->win);
        exit(0);
    }
    return (1);
}

void exit_error(char *error, t_prog *prog)
{
    if (prog != NULL)
    {
        if (prog->mlx != NULL && prog->win != NULL){
            mlx_clear_window(prog->mlx, prog->win);
            mlx_destroy_window(prog->mlx, prog->win);
        }
    }
    ft_printf("%s\n", error);
    exit(0);
}

/* Perfoming checks on file, is file readable?
*  Is map surrunded by walls?
*  Are each line at the same size?
*  Is there only 1 starting point, one exit and at least 1 collectibles?

TODO Valid path ?
TODO Handling the right error message as specified in the subject

*/
int read_map(char *path)
{
    int fd = open(path, O_RDONLY, 0);
    if (fd <= 0)
        exit_error("Error while trying to read the input filepath.", NULL);
    char reader[1];
    int readable = 1;

    int firstln = 0;
    int lineln = 0;
    int newlineln = 0;
    char    *lastline;
    int needs[3];
    while (readable > 0)
    {
        readable = read(fd, reader, 1);
        if (readable == -1)
        {
            if (lastline)
                free(lastline);
            exit_error("Error while reading the input file.", NULL);
        }
        if (readable > 0 && (reader[0] == '1' || reader[0] == '0' || reader[0] == 'P' || reader[0] == 'E' || reader[0] == 'C'))
        {
            if (firstln == 0){
                lineln++;
                lastline = malloc((lineln + 1) * sizeof(char));
                if (lastline == NULL)
                    exit_error("Memory allocation error.", NULL);
                lastline[lineln] = 0;
            } else
                lastline[newlineln] = reader[0];
            newlineln++;
        }
        if (reader[0] == '\n' || readable == 0){
            firstln++;
            if (newlineln != lineln)
            {
                free(lastline);
                exit_error("Error, file is not correctly formatted, lines size differ.", NULL);
            }
            newlineln = 0;
            if (readable == 0)
                break;
        }
        if ((firstln == 0 && reader[0] != '1') || (newlineln == 1 && reader[0] != '1')
            || (newlineln == lineln && reader[0] != '1'))
        {
            free(lastline);
            exit_error("Error, file is not correctly formatted, map must be surrounded by walls.", NULL);
        }
        if (reader[0] == '1')
            ft_printf("");
        else if (reader[0] == '0')
            ft_printf("");
        else if (reader[0] == 'P')
            needs[0]++;
        else if (reader[0] == 'E')
            needs[1]++;
        else if (reader[0] == 'C')
            needs[2]++;
        else if (reader[0] == '\n')
            ft_printf("");
        else
        {
            free(lastline);
            exit_error("Error, file is not correctly formatted.", NULL);
        }
    }
    int i2 = 0;
    while (lastline[i2] != 0)
    {
        if (lastline[i2++] != '1')
        {
            free(lastline);
            exit_error("Error, file is not correctly formatted, map must be surrounded by walls.", NULL);
        }
    }
    free(lastline);
    if (needs[0] != 1 || needs[1] != 1 || needs[2] < 1)
        exit_error("Error, your map doesn't contains the minimals interest points.", NULL);
    ft_printf("\n");
    return (1);
}

int main(int argc, char **argv)
{
    read_map(argv[1]);
    
    t_prog prog;
    // Creating a window with specified size and title
    prog.mlx = mlx_init();
    if (prog.mlx == NULL)
        return (0);
    prog.win = mlx_new_window(prog.mlx, 1920/4, 1080/4, "test");
    if (prog.mlx == NULL)
        return (0);

    mlx_key_hook(prog.win, close_window, &prog);
    int img_width;
    int img_height;
    void *imgFloor = mlx_xpm_file_to_image(prog.mlx, "img/grass.xpm", &img_width, &img_height);
    void *imgWallUp = mlx_xpm_file_to_image(prog.mlx, "img/wall_up.xpm", &img_width, &img_height);
    if (imgFloor == NULL || imgWallUp == NULL)
        return (close_window(KEY_ESCAPE, &prog), 0);
    int i = 0;
    int j = -SIZE;
    int line = 0;
    while (i < argc)
    {
        if (argv[i][0] == 'n'){
            line += SIZE;
            j = -SIZE;  
        } else if (argv[i][0] == 'X')
            mlx_put_image_to_window(prog.mlx, prog.win, imgWallUp, j, line);
        else if (argv[i][0] == '0')
            mlx_put_image_to_window(prog.mlx, prog.win, imgFloor, j, line);
        j += SIZE;
        i++;
    }
    
    // listening to any events
    mlx_loop(prog.mlx);
    return argc;
}