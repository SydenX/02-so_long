/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linesize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetol <jetol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:56:10 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/06 15:02:41 by jetol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	linesize_checks(char *reader)
{
	int	i;
	int	fline;
	int	newline;

	i = 0;
	fline = 0;
	while (reader[i] != '\n')
	{
		fline++;
		if (reader[++i] == 0)
			exit_error("Error, the map format is not correct.", NULL, NULL, NULL);
	}
	while (reader[i] != 0)
	{
		i++;
		newline = 0;
		while (reader[i] != '\n' && reader[i] != 0)
		{
			newline++;
			i++;
		}
		if (newline != fline)
			exit_error("Error, map lines are not with the same size.", NULL, NULL, NULL);
	}
	return (1);
}
