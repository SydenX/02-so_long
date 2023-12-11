/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:49:43 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/11 12:34:02 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	close_window(t_data *data)
{
	t_img	*imgsc;

	imgsc = data->imgs;
	while (imgsc->type != NULLT)
	{
		mlx_destroy_image(data->prog->mlx, imgsc->img);
		imgsc++;
	}
	free(imgsc->img);
	free(data->imgs);
	mlx_clear_window(data->prog->mlx, data->prog->win);
	mlx_destroy_window(data->prog->mlx, data->prog->win);
	free(data->nodes);
	free(data->prog->mlx);
	exit(0);
	return (1);
}

t_node	*get_list(char **argv, char *reader, int fileChars)
{
	t_node	*list;

	list = malloc((node_size(argv[1]) + 1) * sizeof(t_node));
	if (!list)
	{
		free(reader);
		exit_error("Failed malloc allocation", NULL, NULL, NULL);
	}
	list = read_map(get_fd(argv[1], (void *)list, (void *)reader),
			fileChars, reader, list);
	pathf_setup_h(list);
	pathf_run(list);
	return (list);
}

t_prog	get_prog(t_node *list)
{
	t_prog	prog;

	prog.mlx = mlx_init();
	if (prog.mlx == NULL)
		exit_error("Failed malloc allocation", NULL, list, NULL);
	prog.win = mlx_new_window(prog.mlx, get_list_xlen(list) * SIZE,
			get_list_ylen(list) * SIZE, "So Long by Syden_");
	if (prog.win == NULL)
		exit_error("Failed malloc allocation", NULL, prog.mlx, list);
	return (prog);
}

t_img	*get_img(char **argv, t_node *list, t_prog *prog)
{
	t_img	*imgs;

	imgs = malloc(((node_size(argv[1]) * 2) + 1) * sizeof(t_node));
	if (!imgs)
		exit_error("Failed malloc allocation", prog, list, NULL);
	imgs = load_images(imgs, list, prog);
	return (imgs);
}

int	main(int argc, char **argv)
{
	int		filechars;
	char	*reader;
	t_prog	prog;
	t_data	data;

	if (argc != 2)
		exit_error("You must put a map path as argument.", NULL, NULL, NULL);
	filechars = file_chars(argv[1]);
	reader = malloc((filechars + 1) * sizeof(char));
	if (!reader)
		exit_error("Failed malloc allocation", NULL, NULL, NULL);
	reader[filechars] = 0;
	data.nodes = get_list(argv, reader, filechars);
	prog = get_prog(data.nodes);
	data.prog = &prog;
	data.imgs = get_img(argv, data.nodes, data.prog);
	data.moves = 0;
	map_init(&data);
	mlx_hook(data.prog->win, 2, 0, &event_key_pressed, &data);
	mlx_hook(data.prog->win, 17, 0, &close_window, &data);
	mlx_loop(data.prog->mlx);
	return (argc);
}
