/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 12:13:02 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/25 12:13:03 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

double	deg_to_rad(double degrees)
{
	return (degrees * (M_PI / 180.0));
}

int	calculate_steps(double dx, double dy)
{
	if (fabs(dx) > fabs(dy))
		return ((int)fabs(dx));
	else
		return ((int)fabs(dy));
}

double	distance(t_dpoint *a, t_dpoint *b)
{
	return (sqrt((b->x - a->x) * (b->x - a->x)
			+ (b->y - a->y) * (b->y - a->y)));
}
