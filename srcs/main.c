/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetol <jetol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/07 19:09:46 by jetol            ###   ########.fr       */
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

int	close_window(t_data *data)
{

	mlx_clear_window(data->prog->mlx, data->prog->win);
	mlx_destroy_window(data->prog->mlx, data->prog->win);
	free(data->imgs);
	free(data->nodes);
	free(data->prog->mlx);
	exit(0);
	return (1);
}

int	is_node_free(int x, int y, t_data *data)
{
	t_node	*node;
	t_img	*img;

	node = get_node_at(data->nodes, x, y);
	if (node->type == FLOOR || node->type == SPAWN)
		return (1);
	if (node->type == EXIT && !collectibles_left(data->imgs))
		close_window(data);
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

void	move_player(int key, t_data *data)
{
	t_img	*oldimg;

	oldimg = get_player_image(data);
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
	mlx_destroy_image(data->prog->mlx, oldimg->img);
	oldimg->img = get_image(data->prog, SPAWN);
	map_init(data);
}

int	event_key_pressed(int keycode, t_data *data)
{
	t_img	*oldimg;

	if (keycode == KEY_W || keycode == KEY_A 
		|| keycode == KEY_D || keycode == KEY_S
		|| keycode == KEY_UP || keycode == KEY_RIGHT 
		|| keycode == KEY_LEFT || keycode == KEY_DOWN)
		move_player(keycode, data);
	else if (keycode == KEY_ESCAPE)
		close_window(data);
	return (1);
}

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

void map_init(t_data *data)
{
	t_img	*cpy;
	t_img	*loadafter;

	cpy = data->imgs;
	mlx_clear_window(data->prog->mlx, data->prog->win);
	while (cpy->type != NULLT)
	{
		if (cpy->type == SPAWN)
			loadafter = cpy;
		else
			mlx_put_image_to_window(data->prog->mlx, data->prog->win, cpy->img, cpy->x * SIZE, cpy->y * SIZE);
		cpy++;
	}
	mlx_put_image_to_window(data->prog->mlx, data->prog->win, loadafter->img, loadafter->x * SIZE, loadafter->y * SIZE);
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
	prog.win = mlx_new_window(prog.mlx, get_list_xlen(list) * SIZE, get_list_ylen(list) * SIZE, "So Looongg v0.1 by Syden_");
	if (prog.mlx == NULL)
		return (0);
	t_img *imgs = malloc(((node_size(argv[1]) * 2) + 1) * sizeof(t_node));
	if (!imgs)
		exit_error("Failed malloc allocation", &prog, list, reader);
	imgs = load_images(imgs, list, &prog);
	
	t_data data;
	data.prog = &prog;
	data.imgs = imgs;
	data.nodes = list;

	map_init(&data);
	mlx_hook(prog.win, 17, 0, &close_window, &data);
	mlx_hook(prog.win, 2, 0, &event_key_pressed, &data);
	// listening to any events
	mlx_loop(prog.mlx);
	return argc;
}
