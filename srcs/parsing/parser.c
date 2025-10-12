/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:39:24 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/10/12 19:35:09 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	height_len_check(int fd, t_map *map)
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
}
bool	validate_map(char *map_name, t_map *map)
{
	(void)map_name;

	map->fd = open(map_name, O_RDONLY);
	if (map->fd < 3)
	{
		errno = EBADF;
		perror("invalid fd");
		return ;
	}
	if (!copy_map(map->fd, map));
		return ;
	flood_fill();
}
