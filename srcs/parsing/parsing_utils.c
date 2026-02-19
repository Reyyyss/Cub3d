/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrique-reis <henrique-reis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 21:47:08 by henrique-re       #+#    #+#             */
/*   Updated: 2026/02/18 23:13:09 by henrique-re      ###   ########.fr       */
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

void	print_map(t_map *map)
{
	for (int i = 0; map->map_copy[i]; i++)
		ft_printf("row:%i      %s\n", i, map->map_copy[i]);
}

bool	get_new_zero(char **map, int x, int y, int *pos)
{
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0')
			{
				pos[0] = x;
				pos[1] = y;
				return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

void	liberator(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	parsing_exit_function(t_map *map, int fd)
{
	if (map)
		liberator(map->map);
	if (map->mlx)
	{
		free(map->mlx);
	}
	if (fd > 0)
		close (fd);
	exit(1);
}

char	*pad_line(char *line, size_t width)
{
	char	*new_line;
	size_t	i;

	new_line = malloc(width + 1);
	if (!new_line)
		return (NULL);

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < width)
	{
		new_line[i] = ' ';
		i++;
	}

	new_line[i] = '\0';
	return (new_line);
}
