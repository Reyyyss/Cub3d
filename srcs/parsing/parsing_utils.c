/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:36:53 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/10/29 12:18:40 by hcarrasq         ###   ########.fr       */
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

int	map_copy(int fd, char *map_name)
{
	int	i;

	while (get_next_line(fd))
		i++;
	if (i < 3)
		return (NULL);
	close(fd);
	fd = open(map_name, O_RDONLY);
	if (fd < 3)
	{
		errno = EBADF;
		perror("invalid fd");
		return (NULL);
	}
	skip_till_map(fd_to_copy)
}
