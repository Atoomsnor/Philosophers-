/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:07:53 by roversch          #+#    #+#             */
/*   Updated: 2025/08/18 15:55:40 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

int	my_atoi(const char *nptr)
{
	int	result;
	int	parity;
	int	i;

	result = 0;
	parity = 1;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			parity = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * parity);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday Error\n");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_message(t_philo *phil, char *action)
{
	size_t	time;

	time = get_time() - phil->time_born;
	printf("%zu %i %s\n", time, phil->id, action);
}

void	ft_usleep(size_t time) //unsure
{
	size_t	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}
