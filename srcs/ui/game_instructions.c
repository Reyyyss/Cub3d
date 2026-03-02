/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_instructions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:13:27 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/25 12:13:28 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	draw_bg_rect(t_game *cub, t_rect r)
{
	int	x;
	int	y;

	y = r.y;
	while (y < r.y + r.h && y < HEIGHT)
	{
		x = r.x;
		while (x < r.x + r.w && x < WIDTH)
		{
			if (x >= 0 && y >= 0)
				my_mlx_pixel_put(cub->img, x, y, 0x99000000);
			x++;
		}
		y++;
	}
}

static void	draw_instructions_keys(t_game *cub, int x, int y)
{
	mlx_string_put(cub->mlx, cub->win, x, y, LIGHT_GRAY,
		"W  -  Move forward");
	mlx_string_put(cub->mlx, cub->win, x, y + 20, LIGHT_GRAY,
		"S  -  Move backward");
	mlx_string_put(cub->mlx, cub->win, x, y + 40, LIGHT_GRAY,
		"A  -  Strafe left");
	mlx_string_put(cub->mlx, cub->win, x, y + 60, LIGHT_GRAY,
		"D  -  Strafe right");
	mlx_string_put(cub->mlx, cub->win, x, y + 90, LIGHT_GRAY,
		"<  -  Look left");
	mlx_string_put(cub->mlx, cub->win, x, y + 110, LIGHT_GRAY,
		">  -  Look right");
	mlx_string_put(cub->mlx, cub->win, x, y + 140, LIGHT_GRAY,
		"M  -  Toggle minimap");
	mlx_string_put(cub->mlx, cub->win, x, y + 160, LIGHT_GRAY,
		"I  -  Toggle this menu");
	mlx_string_put(cub->mlx, cub->win, x, y + 180, LIGHT_GRAY,
		"ESC - Quit");
	mlx_string_put(cub->mlx, cub->win, x, y + 200, BLACK,
		"Any question ask");
	mlx_string_put(cub->mlx, cub->win, x, y + 210, BLACK,
		"the developers :)");
}

static void	draw_instructions_text(t_game *cub)
{
	int	x;
	int	y;

	x = WIDTH - 210;
	y = 10;
	draw_bg_rect(cub, (t_rect){x - 10, y - 5, 220, 230});
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img->img, 0, 0);
	x = WIDTH - 205;
	y = 25;
	mlx_string_put(cub->mlx, cub->win, x, y, WHITE, "--- CONTROLS ---");
	draw_instructions_keys(cub, x, y + 25);
}

static void	draw_hint_bg(t_game *cub)
{
	draw_bg_rect(cub, (t_rect){WIDTH - 145, 5, 140, 20});
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img->img, 0, 0);
}

void	draw_instructions(t_game *cub)
{
	if (cub->instructions_visible)
		draw_instructions_text(cub);
	else
	{
		draw_hint_bg(cub);
		mlx_string_put(cub->mlx, cub->win, WIDTH - 140, 20,
			GRAY, "[I] Instructions");
	}
}
