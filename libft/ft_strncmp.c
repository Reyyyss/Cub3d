/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miovu <miovu@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 01:17:12 by chillhoneyy       #+#    #+#             */
/*   Updated: 2026/02/20 15:33:19 by miovu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	if (n == 0)
		return (0);
	while (*str1 == *str2 && n > 1 && *str1 != '\0')
	{
		++str1;
		++str2;
		--n;
	}
	return ((unsigned char)*str1 - (unsigned char)*str2);
}

/* #include <stdio.h>
int	main()
{
	const char	*str1 = "Hello";
	const char	*str2 = "HeLlo";
	size_t		i = 5;
	int			j;
	
	j = ft_strncmp(str1, str2, i);
	printf("Result: %d\n", j);
	return (0);
} */