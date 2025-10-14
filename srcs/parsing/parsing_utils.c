/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcarrasq <hcarrasq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 18:36:53 by hcarrasq          #+#    #+#             */
/*   Updated: 2025/10/14 18:45:46 by hcarrasq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub.h"
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

bool	is_wspace(char *str)
{
	if ((*str >= 9 && *str <= 13) || *str == 32)
		return (true);
	return (false);
}
