#include "../../inc/cub3d.h"

static void	player_movement_assist(t_game *cub, int keycode,
	double *new_x, double *new_y)
{
	if (keycode == W)
	{
		*new_x += cub->player->p_dir->x;
		*new_y += cub->player->p_dir->y;
	}
	if (keycode == A)
	{
		*new_x += cub->player->p_dir->y;
		*new_y -= cub->player->p_dir->x;
	}
	if (keycode == S)
	{
		*new_x -= cub->player->p_dir->x;
		*new_y -= cub->player->p_dir->y;
	}
	if (keycode == D)
	{
		*new_x -= cub->player->p_dir->y;
		*new_y += cub->player->p_dir->x;
	}
}

static void	apply_movement(t_game *cub, double new_x, double new_y)
{
	if (!is_wall(cub, (int)new_x, (int)new_y, COLLISION_RADIUS))
	{
		cub->player->p->x = new_x;
		cub->player->p->y = new_y;
		return ;
	}
	if (!is_wall(cub, (int)new_x,
			(int)cub->player->p->y, COLLISION_RADIUS))
		cub->player->p->x = new_x;
	if (!is_wall(cub, (int)cub->player->p->x,
			(int)new_y, COLLISION_RADIUS))
		cub->player->p->y = new_y;
}

void	player_movement(int keycode, t_game *cub)
{
	double	new_x;
	double	new_y;

	new_x = cub->player->p->x;
	new_y = cub->player->p->y;
	player_movement_assist(cub, keycode, &new_x, &new_y);
	apply_movement(cub, new_x, new_y);
}

void	player_direction(int keycode, t_game *cub)
{
	if (keycode == LEFT)
	{
		cub->player->angle -= 0.05;
		if (cub->player->angle <= 0)
			cub->player->angle += 2 * M_PI;
		cub->player->p_dir->x = cos(cub->player->angle) * 5;
		cub->player->p_dir->y = sin(cub->player->angle) * 5;
	}
	else if (keycode == RIGHT)
	{
		cub->player->angle += 0.05;
		if (cub->player->angle >= 2 * M_PI)
			cub->player->angle -= 2 * M_PI;
		cub->player->p_dir->x = cos(cub->player->angle) * 5;
		cub->player->p_dir->y = sin(cub->player->angle) * 5;
	}
}
