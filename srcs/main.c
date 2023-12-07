/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/07 15:41:59 by jtollena         ###   ########.fr       */
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

t_img	*get_player_image(t_data *data)
{
	t_img 	*cpy;
	int		i;

	i = 0;
	cpy = data->imgs;
	while (cpy->type != NULLT)
	{
		if (cpy->type == SPAWN)
			return (&data->imgs[i]);
		i++;
		cpy++;
	}
	return (data->imgs);
}

int	is_node_free(int x, int y, t_data *data)
{
	t_node	*node;

	node = get_node_at(data->nodes, x, y);
	if (node->type == FLOOR)
		return (1);
	if (node->type == COLLECTIBLE)
	{
		data->nodes->type = FLOOR;
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
	if (key == KEY_W && is_node_free(oldimg->x, oldimg->y - 1, data) == 1)
		oldimg->y -= 1;
	else if (key == KEY_S && is_node_free(oldimg->x, oldimg->y + 1, data) == 1)
		oldimg->y += 1;
	else if (key == KEY_A && is_node_free(oldimg->x - 1, oldimg->y, data) == 1)
		oldimg->x -= 1;
	else if (key == KEY_D && is_node_free(oldimg->x + 1, oldimg->y, data) == 1)
		oldimg->x += 1;
	mlx_destroy_image(data->prog->mlx, oldimg->img);
	oldimg->img = get_image(data->prog, SPAWN);
	map_init(data);
}

int	event_key_pressed(int keycode, t_data *data)
{
	t_img	*oldimg;

	if (keycode == KEY_W || keycode == KEY_A || keycode == KEY_D || keycode == KEY_S)
		move_player(keycode, data);
	else if (keycode == KEY_ESCAPE)
		close_window(data);
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

void	*get_image(t_prog *prog, t_type type)
{
	int img_width;
	int img_height;

	if (type == WALL)
		return (mlx_xpm_file_to_image(prog->mlx, "img/MegaTree.xpm", &img_width, &img_height));
	if (type == WALL)
		return (mlx_xpm_file_to_image(prog->mlx, "img/Bush.xpm", &img_width, &img_height));
	if (type == COLLECTIBLE)
		return (mlx_xpm_file_to_image(prog->mlx, "img/Mushroom.xpm", &img_width, &img_height));
	if (type == EXIT)
		return (mlx_xpm_file_to_image(prog->mlx, "img/Exit.xpm", &img_width, &img_height));
	if (type == SPAWN)
		return (mlx_xpm_file_to_image(prog->mlx, "img/Ruin.xpm", &img_width, &img_height));
	if (type == NULLT)
		return (NULL);
	return (mlx_xpm_file_to_image(prog->mlx, "img/Grass.xpm", &img_width, &img_height));
}

t_img	create_image(int x, int y, t_type type, t_prog *prog)
{
	t_img	new;
	new.x = x;
	new.y = y;
	new.type = type;
	new.img = get_image(prog, type);
	return (new);
}

t_img	*load_images(t_img *imgs, t_node *list, t_prog *prog)
{
	t_node *cpy;
	int		i;

	cpy = list;
	i = 0;
	while (cpy->type != NULLT)
	{
		imgs[i++] = create_image(cpy->x, cpy->y, FLOOR, prog);
		cpy++;
	}
	cpy = list;
	while (cpy->type != NULLT)
	{
		imgs[i++] = create_image(cpy->x, cpy->y, cpy->type, prog);
		cpy++;
	}
	imgs[i] = create_image(0, 0, NULLT, prog);
	return (imgs);
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
