/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:27:47 by roversch          #+#    #+#             */
/*   Updated: 2025/08/27 14:20:49 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int	if_dead(t_philo *phil)
{
	pthread_mutex_lock(phil->dead_lock);
	if (*phil->dead == true)
	{
		// printf("flagged true\n");
		return (pthread_mutex_unlock(phil->dead_lock), 1);
	}
	return (pthread_mutex_unlock(phil->dead_lock), 0);
}

void	phil_eats(t_philo *phil)
{
	pthread_mutex_lock(phil->l_fork);
	print_message(phil, "has taken a fork");
	pthread_mutex_lock(phil->r_fork);
	print_message(phil, "has taken a fork");
	pthread_mutex_lock(phil->eat_lock);
	print_message(phil, "is eating");
	phil->last_eaten = get_time();
	phil->times_eaten++;
	pthread_mutex_unlock(phil->eat_lock);
	usleep(phil->time_to_eat * 1000);
	pthread_mutex_unlock(phil->l_fork);
	pthread_mutex_unlock(phil->r_fork);
}

void	phil_sleeps(t_philo *phil)
{
	print_message(phil, "is sleeping");
	usleep(phil->time_to_sleep * 1000); 
}

void	phil_thinks(t_philo *phil)
{
	print_message(phil, "is thinking");
}

void	*phil_routine(void *pointer)
{
	t_philo	*phil;
	
	phil = (t_philo *)pointer;

	phil->time_born = get_time();
	while (!if_dead(phil))
	{
		if (phil->id % 2 == 0)
			usleep(phil->time_to_eat * 500);
		// printf("bigphil nr: %d is going\n", phil->id);
		phil_eats(phil);
		phil_sleeps(phil);
		phil_thinks(phil);
		// printf("bigphil nr: %d is done\n", phil->id);
	}
	return (pointer);
}
