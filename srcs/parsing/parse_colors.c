/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:12:40 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/25 12:12:41 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_valid_color_str(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_color_value(char *str)
{
	char	**rgb;
	int		i;
	int		r;
	int		g;
	int		b;

	rgb = ft_split(str, ',');
	if (!rgb)
		return (-1);
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3 || !is_valid_color_str(rgb[0])
		|| !is_valid_color_str(rgb[1]) || !is_valid_color_str(rgb[2]))
		return (free_str_arr(rgb), -1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	free_str_arr(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static int	assign_color(char type, int color, t_game *cub)
{
	if (type == 'F')
	{
		if (cub->floor_color != -1)
			return (0);
		cub->floor_color = color;
	}
	else
	{
		if (cub->ceiling_color != -1)
			return (0);
		cub->ceiling_color = color;
	}
	return (1);
}

int	parse_color_line(char *line, char type, t_game *cub)
{
	char	**parts;
	int		count;
	int		color;

	parts = ft_split(line, ' ');
	if (!parts)
		return (0);
	count = 0;
	while (parts[count])
		count++;
	if (count != 2)
		return (free_str_arr(parts), 0);
	color = parse_color_value(parts[1]);
	free_str_arr(parts);
	if (color == -1)
		return (0);
	return (assign_color(type, color, cub));
}
