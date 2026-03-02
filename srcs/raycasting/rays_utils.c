/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:05:07 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/25 12:05:08 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	step_ray(t_game *cub, int r)
{
	int	i;

	i = 0;
	while (i < cub->ray[r]->dof)
	{
		if (is_wall(cub, (int)cub->ray[r]->r->x, (int)cub->ray[r]->r->y, 0))
			break ;
		cub->ray[r]->r->x += cub->ray[r]->offset->x;
		cub->ray[r]->r->y += cub->ray[r]->offset->y;
		i++;
	}
}

double	calculate_ray_angle(t_game *cub, int r)
{
	double	camera_distance;
	double	horizontal_offset;
	double	target_x;
	double	target_y;
	double	angle;

	camera_distance = 64.0;
	horizontal_offset = -30.0 + (60.0 * r) / (WIDTH - 1);
	target_x = cub->player->p->x
		+ camera_distance * cos(cub->player->angle)
		- horizontal_offset * sin(cub->player->angle);
	target_y = cub->player->p->y
		+ camera_distance * sin(cub->player->angle)
		+ horizontal_offset * cos(cub->player->angle);
	angle = atan2(target_y - cub->player->p->y,
			target_x - cub->player->p->x);
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}
