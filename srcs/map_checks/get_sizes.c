/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sizes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jetol <jetol@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:12:20 by jetol             #+#    #+#             */
/*   Updated: 2023/12/06 11:14:41 by jetol            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "head.h"

int	node_size(char *path)
{
	char	reader[1];
	int		readable;
	int		fd;
	int		wc;

	wc = 0;
	readable = 1;
	fd = open(path, O_RDONLY, 0);
	if (fd <= 0)
		error_inputfile();
	while (readable > 0)
	{
		readable = read(fd, reader, 1);
		if (readable == -1)
			error_inputfile();
		if (reader[0] == '1' || reader[0] == '0' || reader[0] == 'P'
			|| reader[0] == 'E' || reader[0] == 'C')
			wc++;
		else if (reader[0] != '\n' && reader[0] != 0)
			error_notformatted();
	}
	close(fd);
	return (wc + 1);
}

int	file_chars(char *path)
{
	char	reader[1];
	int		readable;
	int		fd;
	int		wc;

	wc = 0;
	readable = 1;
	fd = open(path, O_RDONLY, 0);
	if (fd <= 0)
		error_inputfile();
	while (readable > 0)
	{
		readable = read(fd, reader, 1);
		if (readable == -1)
			error_inputfile();
		wc++;
	}
	close(fd);
	return (wc);
}

int	get_fd(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY, 0);
	if (fd <= 0)
		error_inputfile();
	return (fd);
}
