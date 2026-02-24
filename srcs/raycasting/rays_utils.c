#include "../../inc/cub3d.h"

void	step_ray(t_game *cub, int r)
{
	int	i;

	i = 0;
	while (i < cub->ray[r]->dof)
	{
		if (is_wall(cub, (int)cub->ray[r]->r->x, (int)cub->ray[r]->r->y, 0))
			break ;
		cub->ray[r]->r->x += cub->ray[r]->offset->x;
		cub->ray[r]->r->y += cub->ray[r]->offset->y;
		i++;
	}
}

// double	calculate_ray_angle(t_game *cub, int r)
// {
// 	double	angle;
// 	double	fov_rad;
// 	double	ray_offset;

// 	fov_rad = deg_to_rad(FOV);
// 	angle = cub->player->angle - fov_rad / 2.0 + fov_rad * r / (double)WIDTH;
// 	// ray_offset = -fov_rad / 2.0 + (fov_rad * r) / (double)(WIDTH - 1);
// 	// angle = cub->player->angle + ray_offset;
// 	while (angle < 0)
// 		angle += 2 * M_PI;
// 	while (angle >= 2 * M_PI)
// 		angle -= 2 * M_PI;
// 	return (angle);
// }

double calculate_ray_angle(t_game *cub, int r)
{
    double  camera_distance = 64.0;  // Virtual plane distance from player, full tile
    double  horizontal_offset;
    double  target_x, target_y;
    double  angle;
    
    // Spread rays across the virtual plane (horizontally)
    horizontal_offset = -30.0 + (60.0 * r) / (WIDTH - 1);  // -30 to +30
    // Create a point on the camera plane
    target_x = cub->player->p->x 
               + camera_distance * cos(cub->player->angle)
               - horizontal_offset * sin(cub->player->angle);
    
    target_y = cub->player->p->y 
               + camera_distance * sin(cub->player->angle)
               + horizontal_offset * cos(cub->player->angle);
    // Calculate angle from player to this point on the plane
    angle = atan2(target_y - cub->player->p->y,
                  target_x - cub->player->p->x);
    while (angle < 0)
        angle += 2 * M_PI;
    while (angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    
    return (angle);
}
