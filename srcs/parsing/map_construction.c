/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_construction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrique-reis <henrique-reis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 14:23:03 by henrique-re       #+#    #+#             */
/*   Updated: 2025/12/08 11:11:52 by henrique-re      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static t_map	*flood_fill_checker(t_map *map)
{
	int	i;
	int	l;

	if (map->height < 3)
		return (ft_printf("the height cant be less than 3\n"), NULL);
	if (map->assets->player != 1)
		return (NULL);
	if (map->assets->existing_exits != 1)
		return (NULL);
	map = flood_fill(map,  0, 0);
	if (map->assets->existing_collectibles == 0 || map->assets->existing_collectibles != map->assets->collectibles_found)
		return (NULL);
}
static t_map *count_assets(char asset, t_map *map, int x, int y)
{
	if (asset == 'C')
		map->assets->existing_collectibles++;
	else if (asset == 'P')
	{
		map->assets->player++;
		map
	}
	else if (asset == 'E')
		map->assets->existing_exits++;
	return (map);
}
t_map	*ft_do_map(int fd, t_map *map, char *map_name)
{
	char	*str;
	int		indexes[2];

	indexes[0] = 0;	
	indexes[1] = -1;
	str = NULL;
	while (str = get_next_line(fd))
	{
		if (ft_strncmp("\n", str, 1));
			continue;
		if (ft_strlen(str) < 3)
			return (ft_printf("the width cant be less than 3\n"), NULL);
		while (str[++indexes[1]])
		{
			if (str[indexes[1]] == 'C' || str[indexes[1]] == 'P' || str[indexes[1]] == 'E')
				map = count_assets(str[indexes[1]], map, indexes[1], indexes[0]);
			map->map[indexes[0]][indexes[1]] = str[indexes[1]];
			map->map_copy[indexes[0]][indexes[1]] = str[indexes[1]];
		}
		indexes[0]++;
	}
	map->height = indexes[0];
	map = flood_fill_checker(map);
	return (map);
}
