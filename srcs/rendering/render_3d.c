#include "../../inc/cub3d.h"

static double	get_perpendicular_distance(t_game *cub, int r)
{
	double	distance;
	double	angle_diff;

	if (!cub->ray[r] || !cub->ray[r]->r || !cub->ray[r]->r0)
		return (INFINITY);
	distance = sqrt(pow(cub->ray[r]->r->x - cub->ray[r]->r0->x, 2)
			+ pow(cub->ray[r]->r->y - cub->ray[r]->r0->y, 2));
	if (distance == 0)
		return (INFINITY);
	angle_diff = cub->ray[r]->r_angle - cub->player->angle;
	return (distance * cos(angle_diff));
}

static void	draw_sky_floor(t_game *cub, int x, int wall_top, int wall_bottom)
{
	int	y;

	y = 0;
	while (y < wall_top)
	{
		my_mlx_pixel_put(cub->img, x, y, cub->ceiling_color);
		y++;
	}
	y = wall_bottom;
	while (y < HEIGHT)
	{
		my_mlx_pixel_put(cub->img, x, y, cub->floor_color);
		y++;
	}
}

static void	draw_wall_texture(t_game *cub, t_wall_draw *wd)
{
	int		y;
	double	tex_pos;
	int		tex_y;
	char	*src;

	if (wd->wall_top < 0)
		y = 0;
	else
		y = wd->wall_top;
	while (y < wd->wall_bottom && y < HEIGHT)
	{
		tex_pos = (double)(y - wd->wall_top) * wd->step;
		tex_y = (int)tex_pos;
		if (tex_y >= wd->tex->height)
			tex_y = wd->tex->height - 1;
		if (tex_y < 0)
			tex_y = 0;
		src = wd->tex->addr + tex_y * wd->tex->line_len
			+ wd->tex_x * (wd->tex->bpp / 8);
		my_mlx_pixel_put(cub->img, wd->x, y, *(unsigned int *)src);
		y++;
	}
}

static void	draw_wall_slice(t_game *cub, int r, int wall_height, int x)
{
	t_wall_draw	wd;

	if (wall_height <= 0)
		wall_height = 1;
	wd.wall_top = (HEIGHT / 2) - (wall_height / 2);
	wd.wall_bottom = (HEIGHT / 2) + (wall_height / 2);
	wd.tex = &cub->wall_tex[cub->ray[r]->side];
	wd.tex_x = get_tex_x(cub, r, wd.tex);
	wd.step = (double)wd.tex->height / (double)wall_height;
	wd.x = x;
	draw_sky_floor(cub, x, get_start_y(wd.wall_top),
		get_end_y(wd.wall_bottom));
	draw_wall_texture(cub, &wd);
}

void	render_3d(t_game *cub)
{
	int		r;
	double	perp_distance;
	int		wall_height;

	r = 0;
	while (r < WIDTH)
	{
		if (!cub->ray[r])
		{
			r++;
			continue ;
		}
		perp_distance = get_perpendicular_distance(cub, r);
		if (perp_distance > 0 && perp_distance < INFINITY)
			wall_height = (int)((MAP_S_H * HEIGHT) / perp_distance);
		else
			wall_height = 0;
		if (wall_height > HEIGHT * 5)
			wall_height = HEIGHT * 5;
		draw_wall_slice(cub, r, wall_height, r);
		r++;
	}
}

