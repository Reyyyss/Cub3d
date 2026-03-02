/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:03:02 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/25 12:13:05 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	set_horizontal_start(t_game *cub, int r, double tang)
{
	if (cub->ray[r]->r_angle > M_PI && cub->ray[r]->r_angle < 2 * M_PI)
	{
		cub->ray[r]->r->y = ((int)(cub->player->p->y / MAP_S_H)
				* MAP_S_H) - 0.0001;
		cub->ray[r]->r->x = (cub->player->p->y - cub->ray[r]->r->y) * tang
			+ cub->player->p->x;
		cub->ray[r]->offset->y = -MAP_S_H;
		cub->ray[r]->offset->x = -cub->ray[r]->offset->y * tang;
		return (1);
	}
	else if (cub->ray[r]->r_angle < M_PI && cub->ray[r]->r_angle > 0)
	{
		cub->ray[r]->r->y = ((int)(cub->player->p->y / MAP_S_H) * MAP_S_H)
			+ MAP_S_H;
		cub->ray[r]->r->x = (cub->player->p->y - cub->ray[r]->r->y) * tang
			+ cub->player->p->x;
		cub->ray[r]->offset->y = MAP_S_H;
		cub->ray[r]->offset->x = -cub->ray[r]->offset->y * tang;
		return (1);
	}
	return (0);
}

static int	set_vertical_start(t_game *cub, int r, double tang)
{
	if (cub->ray[r]->r_angle > (M_PI / 2)
		&& cub->ray[r]->r_angle < (3 * M_PI / 2))
	{
		cub->ray[r]->r->x = ((int)(cub->player->p->x / MAP_S_W) * MAP_S_W)
			- 0.0001;
		cub->ray[r]->r->y = (cub->player->p->x - cub->ray[r]->r->x) * tang
			+ cub->player->p->y;
		cub->ray[r]->offset->x = -MAP_S_W;
		cub->ray[r]->offset->y = -cub->ray[r]->offset->x * tang;
		return (1);
	}
	else if (cub->ray[r]->r_angle < (M_PI / 2)
		|| cub->ray[r]->r_angle > (3 * M_PI / 2))
	{
		cub->ray[r]->r->x = ((int)(cub->player->p->x / MAP_S_W) * MAP_S_W)
			+ MAP_S_W;
		cub->ray[r]->r->y = (cub->player->p->x - cub->ray[r]->r->x) * tang
			+ cub->player->p->y;
		cub->ray[r]->offset->x = MAP_S_W;
		cub->ray[r]->offset->y = -cub->ray[r]->offset->x * tang;
		return (1);
	}
	return (0);
}

static t_dpoint	*alloc_point_from_ray(t_game *cub, int r)
{
	t_dpoint	*pt;

	pt = malloc(sizeof(t_dpoint));
	if (!pt)
		return (NULL);
	pt->x = cub->ray[r]->r->x;
	pt->y = cub->ray[r]->r->y;
	return (pt);
}

t_dpoint	*check_horizontal_line(t_game *cub, int r)
{
	double	angle;
	double	tang;

	angle = cub->ray[r]->r_angle;
	if (fabs(sin(angle)) < 0.000001)
		return (NULL);
	tang = -cos(angle) / sin(angle);
	if (!set_horizontal_start(cub, r, tang))
		return (NULL);
	step_ray(cub, r);
	return (alloc_point_from_ray(cub, r));
}

t_dpoint	*check_vertical_line(t_game *cub, int r)
{
	double	angle;
	double	tang;

	angle = cub->ray[r]->r_angle;
	if (fabs(cos(angle)) < 0.000001)
		return (NULL);
	tang = -sin(angle) / cos(angle);
	if (!set_vertical_start(cub, r, tang))
		return (NULL);
	step_ray(cub, r);
	return (alloc_point_from_ray(cub, r));
}
