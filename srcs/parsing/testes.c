#include "cub.h"

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
	int	i;

	i = 0;
	if (flag == 1)
	{
		if (!is_wspace(str[2]) || is_wspace(str[3]))
			return (false);
		if (ft_strncmp(".xpm", str + strlen(str) - 4, 4) != 0)
			return (false);
		return (true);
	}
	else if (flag == 0)
	{
		if (!is_wspace(str[2]) || is_wspace(str[3]))
			return (false);
		while () // enquanto for um digito vou andar para frente com o i, se o len for maior que 3 entao ta errado pois o maximo e 255, depois de saber a len faco strndup com o len que obtive e faco atoi da string duplicada e verifico se e negativo ou maior que 255, faco quatro vezes devido aos quatro pontos, tenho tambem de verificar se sao 4 numeros porque precisam ser e se a seguir a todos os numeros em excecao do ultiumo ha um ponto pois tambem e necessario
	}
	return (true);
}

int main(int ac, char **av)
{
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