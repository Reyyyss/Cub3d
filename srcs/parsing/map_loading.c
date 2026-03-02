/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:12:38 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/25 12:12:39 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	count_remaining_lines(t_game *cub, int fd)
{
	char	*line;
	int		len;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_strtrim_nl(line);
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		len = ft_strlen(line);
		if (len > cub->map_cols)
			cub->map_cols = len;
		cub->map_rows++;
		free(line);
	}
	return (cub->map_rows > 0);
}

static void	skip_header_lines(int fd)
{
	char	*line;
	int		header_count;

	header_count = 0;
	while (header_count < 6)
	{
		line = get_next_line(fd);
		if (!line)
			return ;
		ft_strtrim_nl(line);
		if (line[0] != '\0')
			header_count++;
		free(line);
	}
}

static int	fill_map_rows(t_game *cub, int fd)
{
	char	*line;
	int		i;

	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		ft_strtrim_nl(line);
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		cub->map[i] = pad_line(line, cub->map_cols);
		free(line);
		if (!cub->map[i])
			return (0);
		i++;
	}
	cub->map[i] = NULL;
	return (1);
}

int	load_map(t_game *cub, char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (parsing_error("Cannot open file"), 0);
	skip_header_lines(fd);
	cub->map = malloc(sizeof(char *) * (cub->map_rows + 1));
	if (!cub->map)
		return (close(fd), 0);
	if (!fill_map_rows(cub, fd))
		return (close(fd), 0);
	close(fd);
	return (1);
}

int	count_map_dimensions(t_game *cub, int fd)
{
	return (count_remaining_lines(cub, fd));
}
