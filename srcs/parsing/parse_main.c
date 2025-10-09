/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:20:26 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/10/09 19:23:01 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		return (ft_printf("2 arguments expected\n"), 1);
	if (ft_strncmp(".cub", argv[1] + ft_strlen(argv[1]) - 4, 4) != 0)
		return (ft_printf("Map name should end with .cub\n"), 1);
}
