/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetol <jetol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/06 15:32:09 by jetol            ###   ########.fr       */
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
	return (check_nodes_type(list, j));
}

void	pathf_setup_H(t_node *list)
{
	t_node	exit;
	t_node	*cpy;
	int		xDiff;
	int		yDiff;

	exit = find_exit_point(list);
	cpy = list;
	while (cpy->type != NULLT)
	{
		if (cpy->type == FLOOR || cpy->type == COLLECTIBLE)
		{
			xDiff = absolute(cpy->x - exit.x);
			yDiff = absolute(cpy->y - exit.y);
			cpy->h = xDiff + yDiff;
		}
		cpy++;
	}
}

int	check_precisely(t_node current, t_node *list, int x, int y)
{
	t_node newnode;

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
		&& check_precisely(node , list, node.x - 1, node.y) == 0)
		return (0);
	return (1);
}

void	pathf_run(t_node *list)
{
	t_node 	spawn;
	int		lstsize;

	spawn = find_spawn_point(list);
	lstsize = get_list_size(list);
	printf("%d", check_arround(spawn, list));
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
	pathf_setup_H(list);
	pathf_run(list);
	// printf("\nx: %d \ny: %d \ndist: %d", list->x, list->y, list->h);

	
	// t_prog prog;
	// // Creating a window with specified size and title
	// prog.mlx = mlx_init();
	// if (prog.mlx == NULL)
	// 	return (0);
	// prog.win = mlx_new_window(prog.mlx, 1920/4, 1080/4, "test");
	// if (prog.mlx == NULL)
	// 	return (0);

	// mlx_key_hook(prog.win, close_window, &prog);
	// int img_width;
	// int img_height;
	// void *imgFloor = mlx_xpm_file_to_image(prog.mlx, "img/grass.xpm", &img_width, &img_height);
	// void *imgWallUp = mlx_xpm_file_to_image(prog.mlx, "img/wall_up.xpm", &img_width, &img_height);
	// if (imgFloor == NULL || imgWallUp == NULL)
	// 	return (close_window(KEY_ESCAPE, &prog), 0);
	// int i = 0;
	// int j = -SIZE;
	// int line = 0;
	// while (i < argc)
	// {
	// 	if (argv[i][0] == 'n'){
	// 		line += SIZE;
	// 		j = -SIZE;  
	// 	} else if (argv[i][0] == 'X')
	// 		mlx_put_image_to_window(prog.mlx, prog.win, imgWallUp, j, line);
	// 	else if (argv[i][0] == '0')
	// 		mlx_put_image_to_window(prog.mlx, prog.win, imgFloor, j, line);
	// 	j += SIZE;
	// 	i++;
	// }
	
	// // listening to any events
	// mlx_loop(prog.mlx);
	return argc;
}
