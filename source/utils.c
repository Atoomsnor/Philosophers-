/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:07:53 by roversch          #+#    #+#             */
/*   Updated: 2025/09/03 13:22:45 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

//Ascii to long to transform the input
long	my_atol(const char *nptr)
{
	long	result;
	int		parity;
	int		i;

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
	if (!(nptr[i] == '\0') && !(nptr[i] == ' '))
		return (0);
	return (result * parity);
}

//Prints the error message and exits with the correct code
void	error_and_exit(char *error_msg, int exitcode)
{
	if (error_msg)
		printf("%s", error_msg);
	exit(exitcode);
}

//Destroy all locks and all forks
void	destroy_all(t_monitor *monitor, int amount,
			char *error_msg, int exitcode)
{
	int	i;

	i = 0;
	if (amount)
	{
		while (amount >= 0)
		{
			pthread_mutex_destroy(&monitor->forks[amount]);
			amount--;
		}
	}
	else
	{
		while (i < monitor->amount)
		{
			pthread_mutex_destroy(&monitor->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&monitor->eat_lock);
	pthread_mutex_destroy(&monitor->dead_lock);
	pthread_mutex_destroy(&monitor->print_lock);
	error_and_exit(error_msg, exitcode);
}

//Time function that uses sys/time and makes it into milliseconds
size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday Error\n");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

//Prints given action with time and phil id
void	print_message(t_philo *phil, char *action)
{
	size_t	time;

	pthread_mutex_lock(phil->print_lock);
	time = get_time() - phil->time_born;
	if (!if_dead(phil))
		printf("%zu %i %s\n", time, phil->id, action);
	pthread_mutex_unlock(phil->print_lock);
}
