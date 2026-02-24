#include "../../inc/cub3d.h"

int	get_tex_x(t_game *cub, int r, t_image *tex)
{
	double	pos;
	double	wall_hit;
	int		tex_x;

	if (cub->ray[r]->hit_vertical == 1)
	{
		wall_hit = cub->ray[r]->r->y;
		pos = fmod(wall_hit, MAP_S_H) / MAP_S_H;
	}
	else
	{
		wall_hit = cub->ray[r]->r->x;
		pos = fmod(wall_hit, MAP_S_W) / MAP_S_W;
	}
	if (pos < 0)
		pos += 1.0;
	if (cub->ray[r]->side == TEX_W || cub->ray[r]->side == TEX_N)
		pos = 1.0 - pos;
	tex_x = (int)(pos * (double)tex->width);
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	if (tex_x < 0)
		tex_x = 0;
	return (tex_x);
}

int	clamp_tex_y(t_image *tex, double tex_pos)
{
	int	tex_y;

	tex_y = (int)tex_pos;
	if (tex_y >= tex->height)
		tex_y = tex->height - 1;
	if (tex_y < 0)
		tex_y = 0;
	return (tex_y);
}

int	get_start_y(int wall_top)
{
	if (wall_top < 0)
		return (0);
	return (wall_top);
}

int	get_end_y(int wall_bottom)
{
	if (wall_bottom >= HEIGHT)
		return (HEIGHT - 1);
	return (wall_bottom);
}
