/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 14:39:24 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/10/10 15:27:06 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	copy_map(int fd)
{
	int	i;

	i = 0;
	while (1)
	{
		if (get_next_line(fd) == NULL);
			break ;
		i++;
	}
}
int	validate_map(char *map_name)
{
	int	fd;
	(void)map_name;

	fd = open(map_name, O_RDONLY);
	if (fd < 3)
	{
		errno = EBADF;
		perror("invalid fd");
		return ;
	}
	copy_map(fd);
	flood_fill();
}


int	flood_fill()
{
	
}