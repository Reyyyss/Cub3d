/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrique-reis <henrique-reis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:39:24 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/10/15 18:10:45 by henrique-re      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

/* static bool	height_len_check(int fd, t_map *map)
{
	char *str;

	str = NULL;
	while (1)
	{
		str = get_next_line(fd);
		map->height++;
		if (!str || ft_strlen(str) < 3)
			return (false);
		free(str);
	}
	if (map->height < 3)
		return (false);
	return (true);
} */

static bool check_coordinates(char *str, int flag)
{
	int	fd;
	if (flag == 1)
	{
		if (!is_wspace(*str) || is_wspace(*str++))
			return (false);
		if (ft_strncmp(".xpm", str + ft_strlen(str) - 4, 4) != 0)
			return (false);
	}
	else
	{
		
	}
}

static bool check_images(t_map *map, int fd)
{
	int	i;
	char *str;

	str = NULL;
	i = -1;
	while (++i <= 6)
	{
		str = get_next_line(fd);
		if (!str)
		{
			free(str);
			continue;
		}
		//if flag == 1 then its a coordinate, if its 0 then its floor or ceiling
		if (ft_strncmp("SO", *str, 2))
			check_coordinates(*str, 1);
		else if (ft_strncmp("NO", *str, 2))
			check_coordinates(*str, 1); 
		else if (ft_strncmp("WE", *str, 2))
			check_coordinates(*str, 1);
		else if (ft_strncmp("EA", *str, 2))
			check_coordinates(*str, 1);
		else if (ft_strncmp("f", *str, 2))
			check_coordinates(*str, 0);
		else if (ft_strncmp("c", *str, 2))
			check_coordinates(*str, 0);
		else
			return (false);
		free(str);
	}
	return (true);
}

bool	validate_map_fd(char *map_name, t_map *map)
{
	(void)map_name;

	map->fd = open(map_name, O_RDONLY);
	if (map->fd < 3)
	{
		errno = EBADF;
		perror("invalid fd");
		return ;
	}
	if (!check_images(map, map->fd))
	{
	}
	flood_fill();
}
