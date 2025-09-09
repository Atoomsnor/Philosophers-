/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:17:03 by roversch          #+#    #+#             */
/*   Updated: 2025/09/09 15:25:57 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Prints the error message and exits with the correct code
void	error_and_exit(char *error_msg, int exitcode)
{
	if (error_msg)
		printf("%s", error_msg);
	exit(exitcode);
}

void	destroy_locks(t_monitor *monitor,
			char *error_msg, int exitcode)
{
	pthread_mutex_destroy(&monitor->eat_lock);
	pthread_mutex_destroy(&monitor->dead_lock);
	pthread_mutex_destroy(&monitor->print_lock);
	error_and_exit(error_msg, exitcode);
}

//Destroy all locks and all forks
void	destroy_forks(t_monitor *monitor, int forks,
			char *error_msg, int exitcode)
{
	int	i;

	i = 0;
	if (forks)
	{
		while (forks >= 0)
		{
			pthread_mutex_destroy(&monitor->forks[forks]);
			forks--;
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
	destroy_locks(monitor, error_msg, exitcode);
}

void	destroy_threads(t_monitor *monitor, int created,
			char *error_msg, int exitcode)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&monitor->dead_lock);
	monitor->dead = true;
	pthread_mutex_unlock(&monitor->dead_lock);
	if (created > 0)
	{
		while (i <= created)
		{
			pthread_join(monitor->philos[i].thread, NULL);
			i++;
		}
		pthread_join(monitor->thread, NULL);
	}
	destroy_forks(monitor, 0, error_msg, exitcode);
}
