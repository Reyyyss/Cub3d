/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:12:48 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/27 14:58:54 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_parsing_data(t_game *cub)
{
	cub->map = NULL;
	cub->map_rows = 0;
	cub->map_cols = 0;
	cub->tex_paths[TEX_N] = NULL;
	cub->tex_paths[TEX_E] = NULL;
	cub->tex_paths[TEX_S] = NULL;
	cub->tex_paths[TEX_W] = NULL;
	cub->floor_color = -1;
	cub->ceiling_color = -1;
	cub->player_start_dir = 0;
	cub->player_start_col = 0;
	cub->player_start_row = 0;
}

static bool	validate_filename(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (parsing_error("Invalid file name"), false);
	if (ft_strncmp(".cub", filename + len - 4, 4) != 0)
		return (parsing_error("Map file must end with .cub"), false);
	return (true);
}

bool	parse_cub_file(t_game *cub, char *filename)
{
	int	fd;

	if (!validate_filename(filename))
		return (false);
	init_parsing_data(cub);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (parsing_error("Cannot open file"), false);
	if (!parse_header(cub, fd))
	{
		close(fd);
		return (false);
	}
	if (!count_map_dimensions(cub, fd))
	{
		close(fd);
		return (parsing_error("No map found in file"), false);
	}
	close(fd);
	if (!load_map(cub, filename))
		return (false);
	if (!validate_map(cub))
		return (false);
	return (true);
}
