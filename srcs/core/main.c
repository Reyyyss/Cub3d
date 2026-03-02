/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:11:55 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/25 12:11:56 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	re_render(t_game *cub)
{
	int	i;

	if (!cub || !cub->img)
		return ;
	i = 0;
	while (i < HEIGHT * cub->img->line_len)
	{
		cub->img->addr[i] = 0;
		i++;
	}
	cast_rays(cub);
	render_3d(cub);
	draw_2dmap(cub);
	draw_instructions(cub);
}

int	main(int argc, char **argv)
{
	t_game	cub;

	if (argc != 2)
	{
		parsing_error("Wrong number of arguments");
		return (1);
	}
	if (!parse_cub_file(&cub, argv[1]))
	{
		free_parsing_data(&cub);
		return (1);
	}
	init_mlx(&cub);
	re_render(&cub);
	mlx_loop(cub.mlx);
	return (0);
}
