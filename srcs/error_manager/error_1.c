/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetol <jetol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:10:07 by jetol             #+#    #+#             */
/*   Updated: 2023/12/06 11:14:44 by jetol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	exit_error(char *error, t_prog *prog)
{
	if (prog != NULL)
	{
		if (prog->mlx != NULL && prog->win != NULL)
		{
			mlx_clear_window(prog->mlx, prog->win);
			mlx_destroy_window(prog->mlx, prog->win);
		}
	}
	ft_printf("Error\n%s\n", error);
	exit(0);
}

void	error_inputfile(void)
{
	exit_error("Unable to read the input file.", NULL);
}

void	error_notformatted(void)
{
	exit_error("File is not correctly formatted.", NULL);
}
