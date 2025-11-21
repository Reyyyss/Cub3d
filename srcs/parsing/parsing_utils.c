/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:36:53 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/11/21 17:29:46 by hcarrasq         ###   ########.fr       */
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

static t_map *ft_do_map(int fd, t_map *map, char *map_name)
{
	char 	*str;
	int		i;

	i = 0;
	str = NULL;
	while ((str = get_next_line(fd)) != NULL)
		i++;
	map->map_copy = ft_calloc(i, sizeof(char *));
	map->map = ft_calloc(i, sizeof(char *));
	if (!map->map_copy || !map->map)
		return (NULL);
	i = 0;
	close(fd);
	fd = open(map_name, O_RDONLY);
	if (fd < 3)
		return (fd_error("invalid fd"), NULL);
	skip_coords(fd);
	while ((str = get_next_line(fd)) != NULL)
	{
		if (ft_strncmp("\n", str, 1) == 0)
		{
			free(str);
			continue;
		}
		ft_strlcpy(map->map[i], str, ft_strlen(str));
		ft_strlcpy(map->map_copy[i], str, ft_strlen(str));
		free(str);
		i++;
	}
	ft_printf("map copy:%s\n\n", map->map_copy);
	ft_printf("original map:%s\n\n", map->map);
	return (map);
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
