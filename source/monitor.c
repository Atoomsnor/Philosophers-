/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:27:37 by roversch          #+#    #+#             */
/*   Updated: 2025/09/03 13:24:29 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//Looks if all philos have eaten, sets dead flag
static int	all_eaten_check(t_philo *philos)
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
		*philos->dead = true;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

//Looks if last_eaten time is greater then time to die
static int	last_eaten_check(t_philo *philos)
{
	pthread_mutex_lock(philos->eat_lock);
	if (get_time() - philos->last_eaten > philos->time_to_die)
		return (pthread_mutex_unlock(philos->eat_lock), 1);
	return (pthread_mutex_unlock(philos->eat_lock), 0);
}

//Prints dead flag without using mutexes
static void	print_dead(t_philo *philos)
{
	size_t	time;

	time = get_time() - philos->time_born;
	printf("%zu %i died\n", time, philos->id);
}

//Looks to see if any philos starved, sets dead flag
static int	starve_check(t_philo *philos)
{
	int	i;

	i = 0;
	while (philos[i].nbr_of_philos > i)
	{
		if (last_eaten_check(&philos[i]) == 1)
		{
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = true;
			print_dead(&philos[i]);
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

//Catches the dead flag from eat and dead check
void	*monitor_routine(void *pointer)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)pointer;
	while (1)
	{
		if (all_eaten_check(monitor->philos) == 1
			|| starve_check(monitor->philos) == 1)
			break ;
		usleep(1000);
	}
	return (pointer);
}
