/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:11:29 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/11/21 13:31:58 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <aio.h>
# include <stddef.h>	
# include <sys/time.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <stddef.h>
# include <pthread.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>
# include <stdbool.h>
# include <signal.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map
{
	t_data *data;
	size_t	height;
	char	**map;
	char	**map_copy;
	void	*mlx;
	int		fd;
}	t_map;


bool	validate_map_fd(char *map_name, t_map *map);
void	*ft_free(char **str);
t_map	*map_copy(int fd, char *map_name, t_map *map);

#endif