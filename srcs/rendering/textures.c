/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:13:24 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/25 12:13:25 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	set_texture(t_game *cub, t_image *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(cub->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
		return (0);
	return (1);
}

int	load_textures(t_game *cub)
{
	if (!set_texture(cub, &cub->wall_tex[TEX_N], cub->tex_paths[TEX_N]))
		return (0);
	if (!set_texture(cub, &cub->wall_tex[TEX_E], cub->tex_paths[TEX_E]))
		return (0);
	if (!set_texture(cub, &cub->wall_tex[TEX_S], cub->tex_paths[TEX_S]))
		return (0);
	if (!set_texture(cub, &cub->wall_tex[TEX_W], cub->tex_paths[TEX_W]))
		return (0);
	return (1);
}

int	get_texture_color(t_image *tex, int x, int y)
{
	char	*src;

	if (x < 0 || y < 0 || x >= tex->width || y >= tex->height)
		return (0);
	src = tex->addr + y * tex->line_len + x * (tex->bpp / 8);
	return (*(unsigned int *)src);
}
