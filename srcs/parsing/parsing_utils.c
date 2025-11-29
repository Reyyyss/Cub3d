/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:36:53 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/11/29 16:59:16 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	*ft_free(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	return (free(str), NULL);
}

static void	fd_error(char *error_message)
{
		errno = EBADF;
		perror(error_message);
}

static void	skip_coords(int fd)
{
	int	i;
	char *str;

	str = NULL;
	i = 0;
	while (i <= 5)
	{
		str = get_next_line(fd);
		if (!str)
			return ;
		if (ft_strncmp("\n", str, 1) == 0)
		{
			free(str);
			continue;
		}
		free(str);
		i++;
	}
}

t_map	*map_copy(int fd, char *map_name, t_map *map)
{
	int	i;

	i = 0;
	while (get_next_line(fd))
		i++;
	if (i < 3)
		return (NULL);
	close(fd);
	fd = open(map_name, O_RDONLY);
	if (fd < 3)
		return (fd_error("invalid fd"), NULL);
	skip_coords(fd);
	map = ft_do_map(fd, map, map_name);
	return (map);
}

bool	flood_fill(t_map *map, int x, int y)
{
	if (x < 0 || y < 0 || map->map_copy[y][x] == '1' || map->map_copy[y][x] == 'W')
		return ;
	if (map->map_copy[y][x] == 'C')
		//add a list of assets to add that you found a collectible
	if (map->map_copy[y][x] == 'E')
		//add a list of assets to add that you reached the exit
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
	flood_fill(map, x + 1, y);
	flood_fill(map, x + 1, y);
	return (map);
}