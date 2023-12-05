/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surrounded.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtollena <jtollena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:32:00 by jtollena          #+#    #+#             */
/*   Updated: 2023/12/05 16:57:46 by jtollena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

void	error_surrounded_by_walls(void)
{
	if (lastline)
		free(lastline);
	exit_error("Error, map must be surrounded by walls.", NULL);
}

int	surr_check_firstline(char *reader)
{
	int	i;
	int	line;

	i = 0;
	line = 0;
	while (reader[i])
	{
		if (reader[i] == '\n')
		{
			if (reader[i + 1] != '1' || reader[i - 1] != '1')
				error_surrounded_by_walls();
			line++;
		}
		else if (reader[i] == 0)
			break ;
		else if (line == 0 && reader[i] != '1')
			error_surrounded_by_walls();
		i++;
	}
	return (1);
}

int	surr_checks(char *reader)
{
	int	i;
	int	line;

	i = ft_strlen(reader) - 1;
	line = 0;
	while (reader[i])
	{
		if (reader[i] == '\n')
		{
			if (reader[i + 1] != '1' || reader[i - 1] != '1')
				error_surrounded_by_walls();
			line++;
		}
		else if (reader[i] == 0)
			break ;
		else if (line == 0 && reader[i] != '1')
			error_surrounded_by_walls();
		i--;
	}
	return (surr_check_firstline(reader));
}
