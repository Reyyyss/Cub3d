/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 17:33:38 by henrique-re       #+#    #+#             */
/*   Updated: 2026/02/20 19:13:21 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	check_colors(char **str)
{
	int		i;
	int		l;

	i = -1;
	while (str[++i])
	{
		if (i > 2)
			return (false);
		l = -1;
		while (str[i][++l])
		{
			if (!ft_isdigit(str[i][l]))
				return (ft_free(str), false);
		}
		if (atoi(str[i]) > 255 || atoi(str[i]) < 0)
			return (false);
	}
	return (true);
}

static bool	check_coordinates(char *str)
{
	char	**splited;
	char	**splited_comma;
	int		i;

	i = 0;
	if (!is_wspace(str[1]) || !ft_isdigit(str[2]))
		return (printf("The spaces are wrong\n"), false);
	splited = ft_split(str, ' ');
	if (!splited)
		return (false);
	while (splited[i])
		i++;
	if (i > 2)
		return (false);
	splited_comma = ft_split(splited[1], ',');
	if (!splited_comma)
		return (ft_free(splited), false);
	if (!check_colors(splited_comma))
		return (free(splited), false);
	return (true);
}

static bool	check_coords(char *str, t_map *map)
{
	char	**splited;
	int		i;
	int		fd;

	i = 0;
	if (!is_wspace(str[2]) || is_wspace(str[3]))
		return (printf("The spaces are wrong\n"), false);
	splited = ft_split(str, ' ');
	if (!splited)
		return (false);
	while (splited[i])
		i++;
	if (i >= 2)
		return (false);
	if (ft_strncmp(".xpm", splited[1] + ft_strlen(splited[2]) - 4, 2) != 0)
		return (false);
	fd = open(splited[2], O_RDONLY);
	if (fd < 0)
		return (ft_free(splited), false);
	if (!mlx_xpm_file_to_image(map->mlx, splited[2], NULL, NULL))
		return (ft_free(splited), false);
	return (true);
}

bool	check_images(t_map *map, int fd, int header_index)
{
	char	*str;

	str = NULL;
	while (header_index <= 5)
	{
		str = get_next_line(fd);
		if (!str)
			return (false);
		if (ft_strncmp("\n", str, 1) == 0)
		{
			free(str);
			continue ;
		}
		else if (ft_strncmp("SO", str, 2) == 0)
			check_coords(str, map);
		else if (ft_strncmp("NO", str, 2) == 0)
			check_coords(str, map);
		else if (ft_strncmp("WE", str, 2) == 0)
			check_coords(str, map);
		else if (ft_strncmp("EA", str, 2) == 0)
			check_coords(str, map);
		else if (ft_strchr("FC", str[0]))
			check_coordinates(str);
		else
			return (false);
		free(str);
		header_index++;
	}
	return (true);
}
