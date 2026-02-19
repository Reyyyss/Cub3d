/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loading.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrique-reis <henrique-reis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 18:04:25 by henrique-re       #+#    #+#             */
/*   Updated: 2026/02/18 22:38:46 by henrique-re      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub.h"

static t_map	*allocation_for_map(t_map *map)
{
	map->map = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map)
		return(ft_printf("Error Allocating memory for the map\n"), NULL);
	map->map_copy = malloc(sizeof(char *) * (map->height + 1));
	if (!map->map_copy)
	{
		free(map->map);
		return(ft_printf("Error Allocating memory for the map copy\n"), NULL);
	}
	return (map);
}

static void	skip_coords(int fd)
{
	int	i;
	char *str;

	str = NULL;
	i = 0;
	while (i < 6)
	{
		str = get_next_line(fd);
		if (!str)
			return ;
		if (str[0] == '\n')
		{
			free(str);
			continue;
		}
		free(str);
		i++;
	}
}

t_map	*load_map(t_map *map, char *map_name)
{
	int	fd;
	char *str;
	int	i;

	i = 0;
	str = NULL;
	fd = open(map_name, O_RDONLY);
	if (fd < 3)
		return (fd_error("invalid fd"), NULL);
	map = allocation_for_map(map);
	if (!map)
		return (NULL);
	skip_coords(fd);
	while ((str = get_next_line(fd)) != NULL)
	{
		if (str[0] == '\n')
		{
			free(str);
			continue;
		}
		map->map[i] = pad_line(str, map->width);
		map->map_copy[i] = pad_line(str, map->width);
		free(str);
		i++;
	}
	map->map[i] = NULL;
	map->map_copy[i] = NULL;
	close(fd);
	return (map);
}
