/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:39:24 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/10/23 18:10:00 by hcarrasq         ###   ########.fr       */
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

static bool	check_colors(char **str)
{
	int		i;
	int		l;

	l = -1;
	i = -1;
	while (str[++i])
	{
		printf("%s\n", str[i]);
		if (i > 3)
			return (false);
		while (str[i][++l])
		{
			if (!ft_isdigit(str[i][l]))
				return (ft_free(str), false);
		}
		if (atoi(str[i]) > 255 || atoi(str[i]) < 0)
		{
			printf("atoi: ");
			return (false);
		}
	}
	return (true);
}

static bool check_coordinates(char *str)
{
	char	**splited;
	char	**splited_comma;
	int	i;

	i = 0;
	if (!is_wspace(str[1]) || !ft_isdigit(str[2]))
	{
		printf("os espacos tao mal: ");
		return (false);
	}
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

static bool check_coords(char *str, t_map *map)
{
	char	**splited;
	int	i;
	int	fd;

	i = 0;
	if (!is_wspace(str[1]) || !ft_isdigit(str[2]))
		return (printf("os espacos tao mal: "), false);
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

static bool check_images(t_map *map, int fd)
{
	int	i;
	char *str;

	str = NULL;
	i = 0;
	while (i <= 2)
	{
		str = get_next_line(fd);
		if (!str)
			return (false);
		printf("%s\n", str);
		if (ft_strncmp("\n", str, 1) == 0)
		{
			free(str);
			continue;
		}
		else if (ft_strncmp("SO", str, 2) == 0)
			check_coords(str, map);
		else if (ft_strncmp("NO", str, 2) == 0)
			check_coords(str, map); 
		else if (ft_strncmp("WE", str, 2) == 0)
			check_coords(str, map);
		else if (ft_strncmp("EA", str, 2) == 0)
			check_coords(str, map);
		else if (ft_strncmp("f", str, 1) == 0)
			check_coordinates(str);
		else if (ft_strncmp("c", str, 1) == 0)
			check_coordinates(str);
		else
			return (false);
		free(str);
		i++;
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
		return (false);
	}
	if (!check_images(map, map->fd))
	{
		printf("deu coco\n");
		return (false);
	}
	return (true);
}
