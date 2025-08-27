/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:27:37 by roversch          #+#    #+#             */
/*   Updated: 2025/08/27 13:29:25 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	eat_check(t_philo *philos)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	if (philos[0].nbr_times_to_eat == -1)
		return (1);
	while (philos[0].nbr_of_philos > i)
	{
		if (philos[i].times_eaten >= philos[i].nbr_times_to_eat)
		{
			done++;
		}
		i++;
	}
	if (done == philos[0].nbr_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = true;
		pthread_mutex_unlock(philos[0].dead_lock);
		printf("all done eating\n");
		return (1);
	}
	return (0);
}

int	dead_check(t_philo *philos)
{
	(void)philos;
	return (0);
}

void	*monitor_routine(void *pointer)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)pointer;
	while (1)
	{
		if (eat_check(monitor->philos) == 1 || dead_check(monitor->philos) == 1)
		{
			break ;
		}
		usleep(1000);
	}
	return (pointer);
}