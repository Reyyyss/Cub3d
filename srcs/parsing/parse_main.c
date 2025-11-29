/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:20:26 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/11/29 17:06:53 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	t_map *map;
	if (argc != 2)
		return (ft_printf("2 arguments expected\n"), 1);
	if (ft_strncmp(".cub", argv[1] + ft_strlen(argv[1]) - 4, 4) != 0)
		return (ft_printf("Map name should end with .cub\n"), 1);
	map = malloc(sizeof(t_map));
	if (!map)
		return (ft_printf("Error allocanting the memory for map\n"), 1);
	map = initialize_values(map);
	if (!map)
		return (1);
	if (!validate_map_fd(argv[1], map))
		return (1);
}
