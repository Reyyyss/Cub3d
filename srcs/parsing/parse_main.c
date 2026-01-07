/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrique-reis <henrique-reis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:20:26 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/12/07 14:11:11 by henrique-re      ###   ########.fr       */
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
	if (!validate_map(argv[1], map))
		return (1);
}
