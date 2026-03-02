/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:12:00 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/27 15:08:38 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_events(t_game *cub)
{
	mlx_hook(cub->win, KeyPress, KeyPressMask, key_press, cub);
	mlx_hook(cub->win, DestroyNotify, StructureNotifyMask,
		close_handler, cub);
}

int	key_press(int keycode, t_game *cub)
{
	if (keycode == ESC)
		close_handler(cub);
	if (keycode == W || keycode == A || keycode == S || keycode == D)
		player_movement(keycode, cub);
	if (keycode == RIGHT || keycode == LEFT)
		player_direction(keycode, cub);
	if (keycode == M)
		cub->minimap_visible = !cub->minimap_visible;
	if (keycode == I)
		cub->instructions_visible = !cub->instructions_visible;
	re_render(cub);
	return (0);
}

void	free_parsing_data(t_game *cub)
{
	int	i;

	i = 0;
	if (!cub)
    	return;
	while (i < 4)
	{
		if (cub->tex_paths[i])
			free(cub->tex_paths[i]);
		i++;
	}
	if (cub->map)
	{
		i = 0;
		while (cub->map[i])
		{	
			if (cub->map[i])
				free(cub->map[i]);
			i++;
		}
		free(cub->map);
	}
}

int	close_handler(t_game *cub)
{
	int	r;

	r = -1;
	while (++r < 4)
		if (cub->wall_tex[r].img)
			mlx_destroy_image(cub->mlx, cub->wall_tex[r].img);
	mlx_destroy_image(cub->mlx, cub->img->img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	free(cub->mlx);
	free(cub->img);
	free(cub->player->p);
	free(cub->player->p_dir);
	free(cub->player);
	r = -1;
	while (++r < WIDTH)
	{
		free(cub->ray[r]->r);
		free(cub->ray[r]->r0);
		free(cub->ray[r]->offset);
		free(cub->ray[r]->inc);
		free(cub->ray[r]);
	}
	free_parsing_data(cub);
	exit(EXIT_SUCCESS);
}
