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


static void	*ft_free(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (NULL);
}

static int	fill_words(char **newstr, const char *phrase, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	while (*phrase)
	{
		while (*phrase && *phrase == c)
			phrase++;
		if (*phrase)
		{
			i = 0;
			while (phrase[i] && phrase[i] != c)
				i++;
			newstr[count] = ft_substr(phrase, 0, i);
			if (!newstr[count])
			{
				return (0);
			}
			count++;
			phrase += i;
		}
	}
	return (1);
}

static int	count_words(const char *phrase, char c, char **newstr)
{
	size_t	i;
	size_t	count;

	count = 0;
	while (*phrase)
	{
		while (*phrase && *phrase == c)
			phrase++;
		if (*phrase)
		{
			i = 0;
			while (phrase[i] && phrase[i] != c)
				i++;
			if (i && newstr)
			{
				newstr[count] = ft_substr(phrase, 0, i);
				if (!newstr[count])
					return (ft_free(newstr), 0);
			}
			count++;
			phrase += i;
		}
	}
	return (count);
}

static char	**ft_split(char const *s, char c)
{
	char	**newstr;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c, NULL);
	newstr = ft_calloc(words + 1, sizeof(char *));
	if (!newstr)
		return (NULL);
	if (!fill_words(newstr, s, c))
	{
		return (ft_free(newstr));
	}
	return (newstr);
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static bool	is_wspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && i < n - 1 && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static bool check_coordinates(char *str, int flag)
{
	int		i;
	int		l;
	char	**splited;
	char	**splited_comma;

	l = 0;
	i = 0;
	if (flag == 1)
	{
		printf("boa!!!!!\n");
		return (true);
	}
	else if (flag == 0)
	{
		if (!is_wspace(str[1]) || !ft_isdigit(str[2]))
		{
			printf("os espacos tao mal: ");
			return (false);
		}
		splited = ft_split(str, ' ');
		if (!splited)
			return (false);
		while (splited[i])
			i++;
		if (i > 2)
			return (false);
		i = 0;
		splited_comma = ft_split(splited[1], ' ');
		if (!splited_comma)
		{
			ft_free(splited);
			return (false);
		}
		while (splited_comma[i])
		{
			if (i > 3)
				return (false);
			while (splited_comma[i][l])
			{

				l++;
			}
			if (atoi(splited_comma[i]) > 255 || atoi(splited_comma[i]) < 0)
			{
				printf("atoi: ");
				return (false);
			}
			i++;
		}
		
	}
}



int main(int ac, char **av)
{
	if (ac != 2)
		printf("entao\n");
	if (ft_strncmp("SO", av[1], 2) == 0)
	{		
		if (!check_coordinates(av[1], 1))
			printf("fds1\n");
	}
	else if (ft_strncmp("NO", av[1], 2) == 0)
	{
		if (!check_coordinates(av[1], 1))
			printf("fds2\n"); 
	}
	else if (ft_strncmp("WE", av[1], 2) == 0)
	{
		if (!check_coordinates(av[1], 1))
			printf("fds3\n");
	}
	else if (ft_strncmp("EA", av[1], 2) == 0)
	{
		if (!check_coordinates(av[1], 1))
			printf("fds4\n");
	}
	else if (ft_strncmp("f", av[1], 1) == 0)
	{
		if (!check_coordinates(av[1], 0))
			printf("fds5\n");
	}
	else if (ft_strncmp("c", av[1], 1) == 0)
	{
		if (!check_coordinates(av[1], 0))
			printf("fds6\n");
	}
	else
		return (false);
}