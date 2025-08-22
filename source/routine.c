/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:27:47 by roversch          #+#    #+#             */
/*   Updated: 2025/08/22 17:30:23 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	check_all_eaten(t_philo *philos)
{
	int	i;
	int	done;

	i = 0;
	done = 0;
	while (philos[0].nbr_of_philos > i)
	{
		if (philos[i].times_eaten >= philos[i].nbr_times_to_eat)
			done++;
		i++;
	}
	if (done == philos[0].nbr_of_philos)
	{
		philos->all_eaten = true;
		return (0);
	}
	return (1);
}

void	*monitor_routine(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (!check_all_eaten(philos))
			break ;
	}
	return (pointer);
}

void	*phil_routine(void *pointer)
{
	t_philo	*phil;
	int	loop = 0;
	
	phil = (t_philo *)pointer;
	//put all of this shit in a while loop that keeps going till something dies
	while (loop < 5) //phil->if_died == false || phil->all_eaten == false)
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
		print_message(phil, "is eating");
		usleep(phil->time_to_eat * 1000);
		phil->last_eaten = get_time();
		phil->times_eaten++;
		loop++;
		printf("loop: %i timeseaten: %i\n", loop, phil->times_eaten);
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
