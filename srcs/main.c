/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/05 14:15:23 by jtollena         ###   ########.fr       */
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
*  A chaque avancée on doit inscrire la node current dans une liste (bonus lst de la libft) seulement si il y a un croisement a celle ci (cad 2 chemins possibles),
*  Si on tombe sur un mur, cela va nous permettre de stopper la progression et de repartir sur la derniere node ou il y a un croisement.
*  
*/

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

void    error_inputfile(char *lastline)
{
	if (lastline)
		free(lastline);
	exit_error("Error while reading the input file.", NULL);
}

char	*setup_lastline(int lineln, char *lastline)
{
	if (lineln == 1)
	{
		lastline = malloc((lineln + 1) * sizeof(char));
		if (lastline == NULL)
			exit_error("Memory allocation error.", NULL);
		lastline[lineln] = 0;
	}
	return (lastline);
}

int	error_linesizediffer(int newlineln, int lineln, char *lastline)
{
	if (newlineln != lineln)
	{
		free(lastline);
		exit_error("Error, file is not correctly formatted, lines size differ.", NULL);
	}
	return (0);
}

void error_surrounded_by_walls(char *lastline)
{
	free(lastline);
	exit_error("Error, file is not correctly formatted, map must be surrounded by walls.", NULL);
}

int free_lastline(char *lastline, int *needs)
{
	int i2 = 0;
	while (lastline[i2] != 0)
	{
		if (lastline[i2++] != '1')
			error_surrounded_by_walls(lastline);
	}
	free(lastline);
	return (1);
}

void	error_notformatted(char *lastline)
{
	free(lastline);
	exit_error("Error, file is not correctly formatted.", NULL);
}

void	error_minimalpoints(char *lastline)
{
	free(lastline);
	exit_error("Error, your map doesn't contains the minimals interest points.", NULL);
}

t_node	create_node(char name)
{
	t_node	new;

	// new = malloc(sizeof(t_node));
	if (name == '1')
		new.type = WALL;
	else if (name == '0')
		new.type = FLOOR;
	else if (name == 'P')
		new.type = SPAWN;
	else if (name == 'E')
		new.type = EXIT;
	else if (name == 'C')
		new.type = COLLECTIBLE;
	else if (name != 0 && name != '\n')
		new.type = -1;
	return (new);
}

void	check_nodes(t_node *nodes, int size, char *lastline)
{
	t_node cpy;
	int	spawn;
	int	exit;
	int	collectible; 
	int i;

	i = 0;
	spawn = 0; 
	exit = 0;
	collectible = 0;
	cpy = nodes[i++];
	while (i < size)
	{
		if (cpy.type == -1)
			error_notformatted(lastline);
		if (cpy.type == SPAWN)
			spawn++;
		if (cpy.type == EXIT)
			exit++;
		if (cpy.type == COLLECTIBLE)
			collectible++;
		cpy = nodes[i++];
	}
	if (spawn != 1 || exit != 1 || collectible < 1)
		error_minimalpoints(lastline);
}

int create_list(char *path)
{
	char	reader[1];
	int		readable;
	int		fd;
	int		wc;

	wc = 0;
	readable = 0;
	fd = open(path, O_RDONLY, 0);
	if (fd <= 0)
		exit_error("Error while trying to read the input filepath.", NULL);
	while (readable > 0)
	{
		readable = read(fd, reader, 1);
		if (readable == -1)
			error_inputfile(NULL);
		if (reader[0] == '1' || reader[0] == '0' || reader[0] == 'P' || reader[0] == 'E' || reader[0] == 'C')
			wc++;
	}
	close(fd);
	return (wc);
}

int read_map(char *path, int lineln, int firstln, int readable, int size)
{
	char	reader[1];
	int		newlineln;
	char	*lastline;
	t_node  list[size];
	int 	i;
	int		fd;

	fd = open(path, O_RDONLY, 0);
	if (fd <= 0)
		exit_error("Error while trying to read the input filepath.", NULL);
	i = 0;
	newlineln = 0;
	while (readable > 0)
	{
		readable = read(fd, reader, 1);
		if (readable == -1)
			error_inputfile(lastline);
		if (readable > 0 && (reader[0] == '1' || reader[0] == '0' || reader[0] == 'P' || reader[0] == 'E' || reader[0] == 'C'))
		{
			if (firstln == 0)
			{
				lineln++;
				lastline = setup_lastline(lineln, lastline);
			}
			 else
				lastline[newlineln] = reader[0];
			newlineln++;
		}
		if (reader[0] == '\n' || readable == 0){
			firstln++;
			newlineln = error_linesizediffer(newlineln, lineln, lastline);
			if (readable == 0)
				break;
		}
		if ((firstln == 0 && reader[0] != '1') || (newlineln == 1 && reader[0] != '1') || (newlineln == lineln && reader[0] != '1'))
			error_surrounded_by_walls(lastline);
		list[i++] = create_node(reader[0]);
	}
	check_nodes(list, i, lastline);
	return (free_lastline(lastline, NULL));
}

int main(int argc, char **argv)
{
	read_map(argv[1], 0, 0, 1, create_list(argv[1]));
	
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
