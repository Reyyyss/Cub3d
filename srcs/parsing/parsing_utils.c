/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:36:53 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/11/10 10:01:56 by hcarrasq         ###   ########.fr       */
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

static void	skip_coords(int fd, char *map_name)
{
	int	i;
	char *str;

	str = NULL;
	i = 0;
	while (i <= 5)
	{
		str = get_next_line(fd);
		if (!str)
			return (false);
		if (ft_strncmp("\n", str, 1) == 0)
		{
			free(str);
			continue;
		}
		else if ((ft_strncmp("SO", str, 2) == 0) 
			|| (ft_strncmp("NO", str, 2) == 0))
			;
		else if ((ft_strncmp("WE", str, 2) == 0)
			|| (ft_strncmp("EA", str, 2) == 0))
			;
		else if ((ft_strncmp("F", str, 1) == 0)
			|| (ft_strncmp("C", str, 1) == 0))
			;
		else
			return (false);
		free(str);
		i++;
	}
}

int	map_copy(int fd, char *map_name)
{
	int	i;

	i = 0;
	while (get_next_line(fd))
		i++;
	if (i < 3)
		return (-1);
	close(fd);
	fd = open(map_name, O_RDONLY);
	if (fd < 3)
	{
		errno = EBADF;
		perror("invalid fd");
		return (-1);
	}
	skip_coords(fd, map_name);
	return (0);
}
