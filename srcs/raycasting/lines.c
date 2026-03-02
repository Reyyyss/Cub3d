/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:12:59 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/25 12:13:00 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_line_pixels(t_game *cub, int color, int r)
{
	double	x;
	double	y;
	int		i;

	x = cub->ray[r]->r0->x;
	y = cub->ray[r]->r0->y;
	i = 0;
	while (i <= cub->ray[r]->steps)
	{
		if ((int)x >= 0 && (int)x < WIDTH / 2
			&& (int)y >= 0 && (int)y < HEIGHT)
			my_mlx_pixel_put(cub->img, (int)x, (int)y, color);
		x += cub->ray[r]->inc->x;
		y += cub->ray[r]->inc->y;
		i++;
	}
}

void	draw_line(t_game *cub, int color, int r)
{
	double		dx;
	double		dy;

	dx = cub->ray[r]->r->x - cub->ray[r]->r0->x;
	dy = cub->ray[r]->r->y - cub->ray[r]->r0->y;
	cub->ray[r]->steps = calculate_steps(dx, dy);
	if (cub->ray[r]->steps == 0)
	{
		if ((int)cub->ray[r]->r0->x >= 0 && (int)cub->ray[r]->r0->x < WIDTH / 2
			&& (int)cub->ray[r]->r0->y >= 0 && (int)cub->ray[r]->r0->y < HEIGHT)
			my_mlx_pixel_put(cub->img, (int)cub->ray[r]->r0->x,
				(int)cub->ray[r]->r0->y, color);
		return ;
	}
	cub->ray[r]->inc->x = (double)dx / cub->ray[r]->steps;
	cub->ray[r]->inc->y = (double)dy / cub->ray[r]->steps;
	draw_line_pixels(cub, color, r);
}
