#include "../../inc/cub3d.h"

static double	get_start_angle(char dir)
{
	if (dir == 'N')
		return (3 * M_PI / 2);
	if (dir == 'S')
		return (M_PI / 2);
	if (dir == 'E')
		return (0);
	if (dir == 'W')
		return (M_PI);
	return (M_PI / 2);
}

void	init_player(t_game *cub)
{
	if (!cub)
		return ;
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
	{
		printf(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	cub->player->p = malloc(sizeof(t_dpoint));
	cub->player->p_dir = malloc(sizeof(t_dpoint));
	if (!cub->player->p || !cub->player->p_dir)
	{
		printf(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	cub->player->size = 9;
	cub->player->p->x = cub->player_start_col * MAP_S_W + (MAP_S_W / 2);
	cub->player->p->y = cub->player_start_row * MAP_S_H + (MAP_S_H / 2);
	cub->player->color = BLUE;
	cub->player->angle = get_start_angle(cub->player_start_dir);
	cub->player->p_dir->x = cos(cub->player->angle) * 5;
	cub->player->p_dir->y = sin(cub->player->angle) * 5;
}

void	draw_player(t_game *cub)
{
	int	px;
	int	py;
	int	x;
	int	y;

	if (!cub || !cub->player || !cub->img)
		return ;
	y = 0;
	while (y < cub->player->size)
	{
		x = 0;
		while (x < cub->player->size)
		{
			px = (int)cub->player->p->x - (cub->player->size / 2) + x;
			py = (int)cub->player->p->y - (cub->player->size / 2) + y;
			if (px >= 0 && px < WIDTH / 2 && py >= 0 && py < HEIGHT)
				my_mlx_pixel_put(cub->img, px, py, cub->player->color);
			x++;
		}
		y++;
	}
}
