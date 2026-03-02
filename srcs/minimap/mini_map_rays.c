/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_rays.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:12:06 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/25 12:12:07 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	minimap_ray_target(t_game *cub, t_minimap *mm, int r, t_rect *dst)
{
	if (!cub->ray[r] || !cub->ray[r]->r)
		return (0);
	dst->x = mm->x + (int)(cub->ray[r]->r->x * mm->sx);
	dst->y = mm->y + (int)(cub->ray[r]->r->y * mm->sy);
	return (1);
}

static void	draw_ray_pixels(t_game *cub, t_minimap *mm,
			t_dpoint pos, t_dpoint inc)
{
	int	steps;
	int	i;

	steps = calculate_steps(inc.x, inc.y);
	if (steps == 0)
		return ;
	inc.x /= steps;
	inc.y /= steps;
	i = 0;
	while (i <= steps)
	{
		if (pos.x >= mm->x && pos.x < mm->x + mm->w
			&& pos.y >= mm->y && pos.y < mm->y + mm->h)
			my_mlx_pixel_put(cub->img, (int)pos.x, (int)pos.y, CYAN);
		pos.x += inc.x;
		pos.y += inc.y;
		i++;
	}
}

static void	draw_one_ray(t_game *cub, t_minimap *mm, t_dpoint p, int r)
{
	t_rect		target;
	t_dpoint	delta;

	if (!minimap_ray_target(cub, mm, r, &target))
		return ;
	delta.x = target.x - p.x;
	delta.y = target.y - p.y;
	draw_ray_pixels(cub, mm, p, delta);
}

void	draw_minimap_rays(t_game *cub, t_minimap *mm)
{
	t_dpoint	p;
	int			r;

	r = WIDTH / 2;
	p.x = mm->x + cub->player->p->x * mm->sx;
	p.y = mm->y + cub->player->p->y * mm->sy;
	draw_one_ray(cub, mm, p, r);
}
