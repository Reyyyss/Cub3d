#include "../../inc/cub3d.h"

void	my_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	init_connection(t_game *cub)
{
	cub->mlx = mlx_init();
	if (!cub->mlx)
	{
		free(cub->img);
		printf(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
}

void	init_window(t_game *cub)
{
	cub->win = mlx_new_window(cub->mlx, WIDTH, HEIGHT, "cub3d");
	if (!cub->win)
	{
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		free(cub->img);
		printf(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
}

void	init_image(t_game *cub)
{
	cub->img->img = mlx_new_image(cub->mlx, WIDTH, HEIGHT);
	if (!cub->img->img)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		mlx_destroy_display(cub->mlx);
		free(cub->mlx);
		free(cub->img);
		printf(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	cub->img->width = WIDTH;
	cub->img->height = HEIGHT;
	cub->img->addr = mlx_get_data_addr(cub->img->img, &cub->img->bpp,
			&cub->img->line_len, &cub->img->endian);
}

void	init_mlx(t_game *cub)
{
	if (!cub)
		return ;
	cub->mlx = NULL;
	cub->win = NULL;
	cub->img = NULL;
	cub->player = NULL;
	cub->img = malloc(sizeof(t_image));
	if (!cub->img)
	{
		printf(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	cub->minimap_visible = 1;
	cub->instructions_visible = 0;
	init_connection(cub);
	init_window(cub);
	init_image(cub);
	if (!load_textures(cub))
	{
		printf(ERROR_MESSAGE);
		exit(EXIT_FAILURE);
	}
	init_player(cub);
	init_rays(cub);
	init_events(cub);
}
