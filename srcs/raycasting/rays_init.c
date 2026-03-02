/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:13:08 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/25 12:13:09 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	alloc_ray_or_exit(t_ray **ray)
{
	*ray = malloc(sizeof(t_ray));
	if (!*ray)
	{
		printf(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
}

static void	alloc_ray_points_or_exit(t_ray *ray)
{
	ray->r = malloc(sizeof(t_dpoint));
	ray->r0 = malloc(sizeof(t_dpoint));
	ray->offset = malloc(sizeof(t_dpoint));
	ray->inc = malloc(sizeof(t_dpoint));
	if (!ray->r || !ray->r0 || !ray->inc || !ray->offset)
	{
		printf(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
}

static void	init_ray_defaults(t_ray *ray, int dof)
{
	ray->dof = dof;
	ray->r_angle = M_PI / 2;
	ray->r->x = 0.0;
	ray->r->y = 0.0;
	ray->r0->x = 0.0;
	ray->r0->y = 0.0;
	ray->offset->x = MAP_S_W;
	ray->offset->y = MAP_S_H;
	ray->inc->x = 0.0;
	ray->inc->y = 0.0;
	ray->steps = 0;
	ray->side = TEX_N;
	ray->hit_vertical = 0;
}

void	init_rays(t_game *cub)
{
	int		r;
	int		dof;

	if (!cub)
		return ;
	dof = cub->map_rows + cub->map_cols;
	r = 0;
	while (r < WIDTH)
	{
		alloc_ray_or_exit(&cub->ray[r]);
		alloc_ray_points_or_exit(cub->ray[r]);
		init_ray_defaults(cub->ray[r], dof);
		r++;
	}
}
