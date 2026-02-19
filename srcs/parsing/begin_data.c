/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrique-reis <henrique-reis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:07:07 by henrique-re       #+#    #+#             */
/*   Updated: 2026/02/18 12:39:44 by henrique-re      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	fd_error(char *error_message)
{
	errno = EBADF;
	perror(error_message);
}

static size_t get_width(char *line)
{
	static size_t len;
	size_t	new_len;
	int i;

	i = 0;
	new_len = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (len == 0)
		len = i;
	else
	{
		new_len = i;
		if (new_len > len)
			len = new_len;
	}
	return (len);
}

t_map *initialize_data(t_map *m)
{
	m = malloc(sizeof(t_map));
	if (!m)
		return (ft_printf("Error allocanting the memory for map\n"), NULL);
	m->assets.exit_reached = 0;
	m->assets.player = 0;
	m->height = 0;
	m->width = 0;
	m->fd = 0;
	m->map = NULL;
	m->map_copy = NULL;
	m->mlx = NULL;
	return (m);
}

t_map *initialize_values(t_map *map, char *map_name)
{
	char *str;
	int	fd;

	fd = open(map_name, O_RDONLY);
	if (fd < 3)
		return (fd_error("invalid fd"), NULL);
	str = NULL;
	if (!check_images(map, fd, 0))
			return (ft_printf("Header is Wrong\n"), NULL);
	while ((str = get_next_line(fd)) != NULL)
	{
		if (str[0] == '\n')
		{
			free(str);
			continue;
		}
		map->width = get_width(str);
		map->height++;
		free(str);
	}
	return (map);
}
