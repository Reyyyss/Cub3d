/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miovu <miovu@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 17:52:11 by miovu             #+#    #+#             */
/*   Updated: 2026/01/12 14:57:28 by miovu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	line = NULL;
	while (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE) > 0)
	{
		line = ft_strjoin1(line, buffer[fd]);
		if (!line)
			return (NULL);
		cleanbuff(buffer[fd]);
		if (line[ft_strlen2(line) - 1] == '\n')
			return (line);
	}
	return (line);
}

// int	main()
// {
// 	char	*line;
// 	int		fd;
// 	int		fd1;

// 	fd = open("test3.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("%s", line);
// 	free(line);
// 	fd1 = open("test4.txt", O_RDONLY);
// 	line = get_next_line(fd1);
// 	printf("%s", line);
// 	free(line);
// 	close(fd);
// 	close(fd1);
// }