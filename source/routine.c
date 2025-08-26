/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:27:47 by roversch          #+#    #+#             */
/*   Updated: 2025/08/26 16:50:20 by roversch         ###   ########.fr       */
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
			// printf("done nr: %i\n", done);
		}
		i++;
		// printf("i++ %i\n", i);
	}
	if (done == philos[0].nbr_of_philos)
	{
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
			printf("phil died\n");
			monitor->dead = true;
			break ;
		}
		usleep(1000);
	}
	return (pointer);
}

int	if_dead(t_philo *phil)
{
	pthread_mutex_lock(phil->dead_lock);
	if (*phil->dead == true)
	{
		printf("flagged true\n");
		return (pthread_mutex_unlock(phil->dead_lock), 1);
	}
	return (pthread_mutex_unlock(phil->dead_lock), 0);
}

void	*phil_routine(void *pointer)
{
	t_philo	*phil;
	
	phil = (t_philo *)pointer;

	phil->time_born = get_time();
	//put all of this shit in a while loop that keeps going till something dies
	while (!if_dead(phil)) //phil->if_died == false || phil->all_eaten == false)
	{
		if (phil->id % 2 == 0)
			usleep(phil->time_to_eat * 500);
		printf("bigphil nr: %d is going\n", phil->id);
		//fork
		pthread_mutex_lock(phil->l_fork);
		print_message(phil, "has taken a fork");
		pthread_mutex_lock(phil->r_fork);
		print_message(phil, "has taken a fork");

		//eat
		pthread_mutex_lock(phil->eat_lock);
		print_message(phil, "is eating");
		usleep(phil->time_to_eat * 1000);
		phil->last_eaten = get_time();
		phil->times_eaten++;
		printf("timeseaten: %i\n", phil->times_eaten);
		pthread_mutex_unlock(phil->eat_lock);
		pthread_mutex_unlock(phil->l_fork);
		pthread_mutex_unlock(phil->r_fork);

		//sleep
		print_message(phil, "is sleeping");
		usleep(phil->time_to_sleep * 1000); 

		//think
		print_message(phil, "is thinking");
		//die?
		//unlock

		printf("bigphil nr: %d is done\n", phil->id);
	}
	return (pointer);
}
