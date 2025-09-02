/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:27:37 by roversch          #+#    #+#             */
/*   Updated: 2025/09/02 19:29:45 by roversch         ###   ########.fr       */
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
		return (0);
	while (philos[0].nbr_of_philos > i)
	{
		pthread_mutex_lock(philos[i].eat_lock);
		if (philos[i].times_eaten >= philos[i].nbr_times_to_eat)
			done++;
		pthread_mutex_unlock(philos[i].eat_lock);
		i++;
	}
	if (done == philos[0].nbr_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		printf("all done eating\n");
		*philos->dead = true;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

int	meal_check(t_philo *philos)
{
	pthread_mutex_lock(philos->eat_lock);
	if (get_time() - philos->last_eaten > philos->time_to_die)
		return (pthread_mutex_unlock(philos->eat_lock), 1);
	return (pthread_mutex_unlock(philos->eat_lock), 0);
}

void	print_dead(t_philo *philos)
{
	size_t	time;

	// pthread_mutex_lock(philos->print_lock);
	time = get_time() - philos->time_born;
	printf("%zu %i died\n", time, philos->id);
	// pthread_mutex_unlock(philos->print_lock);
}

int	dead_check(t_philo *philos)
{
	int	i;

	i = 0;
	while (philos[i].nbr_of_philos > i)
	{
		if (meal_check(&philos[i]) == 1)
		{
			pthread_mutex_lock(philos[0].dead_lock);
			print_dead(&philos[i]);
			// print_message(&philos[i], "died");
			*philos->dead = true;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
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
