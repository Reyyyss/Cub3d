/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrique-reis <henrique-reis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:59:54 by henrique-re       #+#    #+#             */
/*   Updated: 2026/02/19 16:57:14 by henrique-re      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	flood_fill(t_map *map, int x, int y, int *pos)
{
	if (x < 0 || x >= (int)map->width || y < 0 || y >= (int)map->height)
		return ;
	if (!map->map_copy[y])
		return ;
	if (map->map_copy[y][x] == ' ' || map->map_copy[y][x] == '\n')
	{
		liberator(map->map_copy);
		parsing_exit_function(map, -1);
	}
	if (map->map_copy[y][x] == '.' || map->map_copy[y][x] == '1')
		return ;
	map->map_copy[y][x] = '.';
	flood_fill(map, y + 1, x, pos);
	flood_fill(map, y - 1, x, pos);
	flood_fill(map, y, x + 1, pos);
	flood_fill(map, y, x - 1, pos);
	if (get_new_zero(map->map_copy, x, y, pos))
		flood_fill(map, pos[0], pos[1], pos);
}
static bool	checking_next_tile(char forward, char behind, char below, char above)
{
	if (!forward || !behind || !below || !above)
		return (false);
	if (above == ' ' || above == '\n' || above == '\0')
		return (false);
	if (below == ' ' || below == '\n' || below == '\0')
		return (false);
	if (forward == ' ' || forward == '\n' || forward == '\0')
		return (false);
	if (behind == ' ' || behind == '\n' || behind == '\0')
		return (false);
	return (true);
}
static t_map	*checking_surrounds(t_map *map)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < map->height && map->map[y])
	{
		x = 0;
	
		while (x < map->width && map->map[y][x] && map->map[y][x] != '\n')
		{
			if (map->map[y][x] == '0'
				|| map->map[y][x] == 'N'
				|| map->map[y][x] == 'S'
				|| map->map[y][x] == 'E'
				|| map->map[y][x] == 'W')
			{
				if (map->map[y][x] == 'N'
				|| map->map[y][x] == 'S' || map->map[y][x] == 'E' || map->map[y][x] == 'W')
				{
					map->assets.player++;
					map->assets.player_x = x;
					map->assets.player_y = y;
					map->assets.player_direction = map->map[y][x];
					if (map->assets.player > 1)
						return (NULL);
				}
				if (y == 0 || y == map->height - 1
					|| x == 0 || x == map->width - 1)
					return (NULL);
				if (!checking_next_tile(map->map[y][x + 1], map->map[y][x - 1], map->map[y + 1][x], map->map[y - 1][x]))
					return (NULL);
			}
			else if (char_checker("10NSEW\n\0", map->map[y][x]) == false && map->map[y][x] != ' '){
				ft_printf("wrong char positions x:%d y:%d", x, y);
				ft_printf("wrong char:%c", map->map[y][x]);
				return (NULL);
			}
			
			x++;
		}
		y++;
	}
	return (map);
}

t_map	*map_checker(t_map	*map)
{
	int	pos[2];

	pos[0] = 0;
	pos[1] = 0;
	get_new_zero(map->map, pos[0], pos[1], pos);
	ft_printf("0 was found at x=%d y=%d\n", pos[0], pos[1]);
	map = checking_surrounds(map);
	if (!map)
		return (ft_printf("Your map building is wrong\n"), NULL);
	flood_fill(map, pos[0], pos[1], pos);
	return (map);
}
