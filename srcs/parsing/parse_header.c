#include "../../inc/cub3d.h"

static int	get_tex_index(char *id)
{
	if (ft_strncmp(id, "NO", 3) == 0)
		return (TEX_N);
	if (ft_strncmp(id, "EA", 3) == 0)
		return (TEX_E);
	if (ft_strncmp(id, "SO", 3) == 0)
		return (TEX_S);
	if (ft_strncmp(id, "WE", 3) == 0)
		return (TEX_W);
	return (-1);
}

static int	parse_texture_line(char *line, t_game *cub)
{
	char	**parts;
	int		count;
	int		index;
	int		fd;

	parts = ft_split(line, ' ');
	if (!parts)
		return (0);
	count = 0;
	while (parts[count])
		count++;
	if (count != 2)
		return (free_str_arr(parts), 0);
	index = get_tex_index(parts[0]);
	if (index == -1 || cub->tex_paths[index])
		return (free_str_arr(parts), 0);
	fd = open(parts[1], O_RDONLY);
	if (fd < 0)
		return (free_str_arr(parts), 0);
	close(fd);
	cub->tex_paths[index] = ft_strdup(parts[1]);
	free_str_arr(parts);
	return (1);
}

static int	parse_header_line(char *line, t_game *cub)
{
	if (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture_line(line, cub));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color_line(line, 'F', cub));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color_line(line, 'C', cub));
	return (0);
}

int	parse_header(t_game *cub, int fd)
{
	char	*line;
	int		parsed;

	parsed = 0;
	while (parsed < 6)
	{
		line = get_next_line(fd);
		if (!line)
			return (parsing_error("Incomplete header"), 0);
		ft_strtrim_nl(line);
		if (line[0] == '\0')
		{
			free(line);
			continue ;
		}
		if (!parse_header_line(line, cub))
		{
			free(line);
			return (parsing_error("Invalid header element"), 0);
		}
		free(line);
		parsed++;
	}
	return (1);
}
