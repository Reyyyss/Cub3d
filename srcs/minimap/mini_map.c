#include "../../inc/cub3d.h"

static void	draw_minimap_tile(t_game *cub, t_rect t, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < t.h)
	{
		x = 0;
		while (x < t.w)
		{
			if (y == 0 || x == 0)
				my_mlx_pixel_put(cub->img, t.x + x, t.y + y, RED);
			else
				my_mlx_pixel_put(cub->img, t.x + x, t.y + y, color);
			x++;
		}
		y++;
	}
}

static void	init_minimap(t_minimap *mm, t_game *cub)
{
	mm->w = WIDTH / 4;
	mm->h = HEIGHT / 4;
	mm->x = 8;
	mm->y = HEIGHT - mm->h - 8;
	mm->tw = mm->w / cub->map_cols;
	mm->th = mm->h / cub->map_rows;
	if (mm->tw < 1)
		mm->tw = 1;
	if (mm->th < 1)
		mm->th = 1;
	mm->sx = (double)mm->tw / MAP_S_W;
	mm->sy = (double)mm->th / MAP_S_H;
}

static void	draw_minimap_tiles(t_game *cub, t_minimap *mm)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < cub->map_rows)
	{
		x = 0;
		while (x < cub->map_cols)
		{
			if (cub->map[y][x] == '1')
				color = PINK;
			else if (cub->map[y][x] == ' ')
				color = BLACK;
			else
				color = ORANGE;
			draw_minimap_tile(cub, (t_rect){mm->x + x * mm->tw,
				mm->y + y * mm->th, mm->tw, mm->th}, color);
			x++;
		}
		y++;
	}
}

void	draw_2dmap(t_game *cub)
{
	t_minimap	mm;

	if (!cub->minimap_visible)
		return ;
	init_minimap(&mm, cub);
	draw_minimap_tiles(cub, &mm);
	draw_minimap_rays(cub, &mm);
	draw_minimap_player(cub, &mm);
}
