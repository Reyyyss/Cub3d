/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: henrique-reis <henrique-reis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 17:11:29 by hcarrasq          #+#    #+#             */
/*   Updated: 2026/02/19 16:54:42 by henrique-re      ###   ########.fr       */
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

typedef struct s_assets
{
	int	exit_reached;
	int player;
	size_t	player_x;
	size_t	player_y;
	char	player_direction;
	int	existing_exits;
}	t_assets;

typedef struct s_map
{
	t_data data;
	t_assets assets;
	size_t	height;
	size_t	width;
	char	**map;
	char	**map_copy;
	void	*mlx;
	int		fd;
}	t_map;

t_map *initialize_values(t_map *map, char *map_name);
t_map *initialize_data(t_map *map);
bool check_images(t_map *map, int fd, int header_index);
void	fd_error(char *error_message);
t_map	*load_map(t_map *map, char *map_name);
void	*ft_free(char **str);
void	print_map(t_map *map);
bool	get_new_zero(char **map, int x, int y, int *pos);
t_map	*map_checker(t_map	*map);
void	liberator(char **str);
void	parsing_exit_function(t_map *map, int fd);
char	*pad_line(char *line, size_t width);
bool	char_checker(const char *s, int c);


#endif