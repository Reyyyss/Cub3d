/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 17:00:19 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/11/29 17:29:44 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

bool	initialize_values(t_map *m)
{
	m->assets->exit_reached = 0;
	m->assets->collectibles_found = 0;
	m->assets->existing_collectibles = 0;
	m->assets->player = 0;
	m->height = 0;
	m->width = 0;
	m->fd = 0;
	m->map = NULL;
	m->map_copy = NULL;
	m->mlx = NULL;
}