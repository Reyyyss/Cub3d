#include "../../inc/cub3d.h"
#include <dirent.h>

static void	print_available_maps(void)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir("maps");
	if (!dir)
		return ;
	entry = readdir(dir);
	while (entry)
	{
		if (ft_strnstr(entry->d_name, ".cub", ft_strlen(entry->d_name)))
			ft_printf("    → maps/%s\n", entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
}

void	parsing_error(char *msg)
{
	ft_printf("\n  \033[1;31mError: %s\033[0m\n\n", msg);
	ft_printf("  \033[1;33mUsage:\033[0m ./cub3d maps/<choose map>\n");
	ft_printf("  \033[0;37mAvailable maps:\033[0m\n");
	print_available_maps();
	ft_printf("\n");
}

void	free_str_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*ft_strtrim_nl(char *str)
{
	int	len;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}

char	*pad_line(char *line, int width)
{
	char	*new_line;
	int		i;

	new_line = malloc(width + 1);
	if (!new_line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		new_line[i] = line[i];
		i++;
	}
	while (i < width)
	{
		new_line[i] = ' ';
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}
