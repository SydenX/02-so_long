/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/07 11:31:08 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"
/* IDEAS- Faire un pathfinding A*
*  Lors de la lecture du fichier, créer une structure "node" qui contient ses coordonneés X et Y, ainsi que son type (mur, sol, point de départ, etc..), avec la donnée H de l'algo (Distance par rapport a la sortie), G = 0 et F = H
*  Mettre chaque élément créé (node) dans une liste de node
*  Ensuite on va pouvoir lire cette liste pour trouver les points que l'on souhaite, on va pouvoir créer notre algo.
*  H = Distance a vol d'oiseau vers la sortie, G = Distance réelle parcourue jusque ce point, F = Addition de H + G
*  A chaque node, on va check toutes les nodes autour de celle actuelle (current), on va check si la node est accéssible (elle ne doit pas etre la meme que la current et elle ne doit pas etre un mur)
*  Ensuite on calcule le G et le F de cette node,
*  On va alors pouvoir changer la node current avec la node qui a le plus petit F
*  A chaque avancée on doit inscrire la node current dans une liste seulement si il y a un croisement a celle ci (cad 2 chemins possibles),
*  Si on tombe sur un mur, cela va nous permettre de stopper la progression et de repartir sur la derniere node ou il y a un croisement.
*  
*/

int	close_window(int keycode, t_prog *prog)
{
	if (keycode == KEY_ESCAPE)
	{
		mlx_clear_window(prog->mlx, prog->win);
		mlx_destroy_window(prog->mlx, prog->win);
		exit(0);
	}
	return (1);
}

int	move_player(int keycode, t_data *data)
{
	if (keycode == KEY_W)
	{
		// mlx_destroy_image(data->prog.mlx, data->img);
		mlx_put_image_to_window(data->prog.mlx, data->prog.win, data->img, (data->x) * SIZE, (data->y - 1) * SIZE);
	}
	return (1);
}

/* Perfoming checks on file, is file readable?
*  Is map surrunded by walls?
*  Are each line at the same size?
*  Is there only 1 starting point, one exit and at least 1 collectibles?

TODO Valid path ?
TODO Handling the right error message as specified in the subject

*/

int	do_map_checks(int fd, char *reader)
{
	close(fd);
	linesize_checks(reader);
	surr_checks(reader);
	return (0);
}

t_node	*read_map(int fd, int fc, char *reader, t_node *list)
{
	int		readable;
	int		i;
	int		j;
	int		y;

	readable = 1;
	i = -1;
	j = 0;
	y = 0;
	readable = read(fd, reader, fc);
	if (readable == -1)
		error_inputfile((void *)reader, (void *)list);
	fc = do_map_checks(fd, reader);
	while (reader[++i])
	{
		if (reader[i] != '\n')
			list[j++] = create_node(reader[i], fc++, y);
		else
		{
			y++;
			fc = 0;
		}
	}
	list[j] = create_node(1, 0, 0);
	return (free(reader), check_nodes_type(list, j));
}

void	map_init(t_node *list, t_prog prog)
{
	int img_width;
	int img_height;
	t_node	*cpy;

	cpy = list;
	void *imgFloor = mlx_xpm_file_to_image(prog.mlx, "img/Grass.xpm", &img_width, &img_height);
	void *imgMegaTree = mlx_xpm_file_to_image(prog.mlx, "img/MegaTree.xpm", &img_width, &img_height);
	void *imgMushroom = mlx_xpm_file_to_image(prog.mlx, "img/Mushroom.xpm", &img_width, &img_height);
	void *imgBush = mlx_xpm_file_to_image(prog.mlx, "img/Bush.xpm", &img_width, &img_height);
	void *imgExit = mlx_xpm_file_to_image(prog.mlx, "img/Exit.xpm", &img_width, &img_height);
	void *imgPlayer = mlx_xpm_file_to_image(prog.mlx, "img/Ruin.xpm", &img_width, &img_height);
	if (imgFloor == NULL)
		close_window(KEY_ESCAPE, &prog);
	int	i = 1;
	while (cpy->type != NULLT)
	{
		mlx_put_image_to_window(prog.mlx, prog.win, imgFloor, cpy->x * SIZE, cpy->y * SIZE);
		if (cpy->type == WALL)
		{
			if ((cpy->h * cpy->x) % 3 == 0)
				mlx_put_image_to_window(prog.mlx, prog.win, imgBush, cpy->x * SIZE, cpy->y * SIZE);
			else
				mlx_put_image_to_window(prog.mlx, prog.win, imgMegaTree, cpy->x * SIZE, cpy->y * SIZE);
		}
		else if (cpy->type == EXIT)
			mlx_put_image_to_window(prog.mlx, prog.win, imgExit, cpy->x * SIZE, cpy->y * SIZE);
		else if (cpy->type == COLLECTIBLE)
			mlx_put_image_to_window(prog.mlx, prog.win, imgMushroom, cpy->x * SIZE, cpy->y * SIZE);
		else if (cpy->type == SPAWN)
			mlx_put_image_to_window(prog.mlx, prog.win, imgPlayer, cpy->x * SIZE, cpy->y * SIZE);
		//else if (cpy->type == FLOOR)
		cpy++;
	}
	t_data	data;

	data.prog = prog;
	data.img = &imgPlayer;
	data.y = 2;
	data.x = 12;
	mlx_key_hook(prog.win, move_player, &data);
}

int	main(int argc, char **argv)
{
	int fileChars = file_chars(argv[1]);
	char *reader = malloc((fileChars + 1) * sizeof(char));
	if (!reader)
		exit_error("Failed malloc allocation", NULL, NULL, NULL);
	reader[fileChars] = 0;
	t_node *list = malloc((node_size(argv[1]) + 1) * sizeof(t_node));
	if (!list)
	{
		free(reader);
		exit_error("Failed malloc allocation", NULL, NULL, NULL);
	}
	list = read_map(get_fd(argv[1], (void *)list, (void *)reader), fileChars, reader, list);
	pathf_setup_h(list);
	pathf_run(list);
	
	t_prog prog;
	// Creating a window with specified size and title
	prog.mlx = mlx_init();
	if (prog.mlx == NULL)
		return (0);
	prog.win = mlx_new_window(prog.mlx, get_list_xlen(list) * SIZE, get_list_ylen(list) * SIZE, "test");
	if (prog.mlx == NULL)
		return (0);
	mlx_key_hook(prog.win, close_window, &prog);
	map_init(list, prog);	
	// listening to any events
	mlx_loop(prog.mlx);
	return argc;
}
