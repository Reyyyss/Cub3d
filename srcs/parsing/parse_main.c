/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 19:01:22 by henrique-re       #+#    #+#             */
/*   Updated: 2026/02/20 19:06:15 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int argc, char **argv)
{
	t_map	*map;

	map = NULL;
	if (argc != 2)
		return (ft_printf("2 arguments expected\n"), 1);
	if (ft_strncmp(".cub", argv[1] + ft_strlen(argv[1]) - 4, 4) != 0)
		return (ft_printf("Map name should end with .cub\n"), 1);
	map = initialize_data(map);
	if (!map)
		return (1);
	map = initialize_values(map, argv[1]);
	if (!map)
		return (1);
	map = load_map(map, argv[1]);
	if (!map)
		return (1);
	print_map(map);
	map = map_checker(map);
	if (!map)
		return (1);
	print_map(map);
}
