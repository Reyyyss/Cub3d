/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 21:47:08 by henrique-re       #+#    #+#             */
/*   Updated: 2026/02/20 19:04:58 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	char_checker(const char *s, int c)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	while (i > 0)
	{
		if (s[i] == (unsigned char)c)
			return (true);
		i--;
	}
	if (s[i] == (unsigned char)c)
		return (true);
	return (false);
}

void	*ft_free(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	return (free(str), NULL);
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
