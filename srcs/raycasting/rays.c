#include "../../inc/cub3d.h"

static void	set_vertical_side(t_game *cub, int r)
{
	if (cub->ray[r]->r_angle < M_PI / 2
		|| cub->ray[r]->r_angle > 3 * M_PI / 2)
		cub->ray[r]->side = TEX_E;
	else
		cub->ray[r]->side = TEX_W;
	cub->ray[r]->hit_vertical = 1;
}

static void	set_horizontal_side(t_game *cub, int r)
{
	if (cub->ray[r]->r_angle > 0 && cub->ray[r]->r_angle < M_PI)
		cub->ray[r]->side = TEX_S;
	else
		cub->ray[r]->side = TEX_N;
	cub->ray[r]->hit_vertical = 0;
}

static t_dpoint	*get_nearest_intersection(t_game *cub, int r,
				t_dpoint *vertical, t_dpoint *horizontal)
{
	double		dist_v;
	double		dist_h;

	if (vertical)
		dist_v = distance(cub->ray[r]->r0, vertical);
	else
		dist_v = INFINITY;
	if (horizontal)
		dist_h = distance(cub->ray[r]->r0, horizontal);
	else
		dist_h = INFINITY;
	if (dist_v < dist_h)
	{
		set_vertical_side(cub, r);
		return (vertical);
	}
	set_horizontal_side(cub, r);
	return (horizontal);
}

void	cast_rays(t_game *cub)
{
	int			r;
	t_dpoint	*vertical_point;
	t_dpoint	*horizontal_point;
	t_dpoint	*nearest_point;

	r = 0;
	while (r < WIDTH)
	{
		cub->ray[r]->r_angle = calculate_ray_angle(cub, r);
		cub->ray[r]->r0->x = cub->player->p->x;
		cub->ray[r]->r0->y = cub->player->p->y;
		vertical_point = check_vertical_line(cub, r);
		horizontal_point = check_horizontal_line(cub, r);
		nearest_point = get_nearest_intersection(cub, r,
				vertical_point, horizontal_point);
		if (nearest_point)
		{
			cub->ray[r]->r->x = nearest_point->x;
			cub->ray[r]->r->y = nearest_point->y;
			draw_line(cub, YELLOW, r);
		}
		free(vertical_point);
		free(horizontal_point);
		r++;
	}
}
