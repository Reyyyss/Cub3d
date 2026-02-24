#include "../../inc/cub3d.h"

static void	draw_player_square(t_game *cub, int px, int py, int size)
{
	int	i;
	int	j;

	i = -size / 2;
	while (i <= size / 2)
	{
		j = -size / 2;
		while (j <= size / 2)
		{
			my_mlx_pixel_put(cub->img, px + i, py + j, cub->player->color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_player(t_game *cub, t_minimap *mm)
{
	int		px;
	int		py;
	double	sx;
	double	sy;

	sx = mm->tw / (double)MAP_S_W;
	sy = mm->th / (double)MAP_S_H;
	px = mm->x + (int)(cub->player->p->x * sx);
	py = mm->y + (int)(cub->player->p->y * sy);
	draw_player_square(cub, px, py, 4);
}

static int	check_wall_point(t_game *cub, int px, int py)
{
	int	map_x;
	int	map_y;

	if (px < 0 || py < 0
		|| px >= cub->map_cols * MAP_S_W
		|| py >= cub->map_rows * MAP_S_H)
		return (1);
	map_x = px / MAP_S_W;
	map_y = py / MAP_S_H;
	if (map_x >= cub->map_cols || map_y >= cub->map_rows)
		return (1);
	if (cub->map[map_y][map_x] != '0')
		return (1);
	return (0);
}

int	is_wall(t_game *cub, int pixel_x, int pixel_y, int offset)
{
	int	dx;
	int	dy;

	dy = -offset;
	while (dy <= offset)
	{
		dx = -offset;
		while (dx <= offset)
		{
			if (check_wall_point(cub, pixel_x + dx, pixel_y + dy))
				return (1);
			dx++;
		}
		dy++;
	}
	return (0);
}
