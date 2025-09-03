/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:27:47 by roversch          #+#    #+#             */
/*   Updated: 2025/09/03 12:09:26 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

//Looks if the dead flag is set to true
int	if_dead(t_philo *phil)
{
	pthread_mutex_lock(phil->dead_lock);
	if (*phil->dead == true)
		return (pthread_mutex_unlock(phil->dead_lock), 1);
	return (pthread_mutex_unlock(phil->dead_lock), 0);
}

//Locks and unlocks forks to eat, sleeps for time_to_eat
static void	phil_eats(t_philo *phil)
{
	if (phil->id % 2 == 0)
	{
		pthread_mutex_lock(phil->l_fork);
		print_message(phil, "has taken a fork");
		pthread_mutex_lock(phil->r_fork);
		print_message(phil, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(phil->r_fork);
		print_message(phil, "has taken a fork");
		pthread_mutex_lock(phil->l_fork);
		print_message(phil, "has taken a fork");
	}
	pthread_mutex_lock(phil->eat_lock);
	print_message(phil, "is eating");
	phil->last_eaten = get_time();
	phil->times_eaten++;
	pthread_mutex_unlock(phil->eat_lock);
	usleep(phil->time_to_eat * 1000);
	pthread_mutex_unlock(phil->l_fork);
	pthread_mutex_unlock(phil->r_fork);
}

//Sleeps for time_to_sleep
static void	phil_sleeps(t_philo *phil)
{
	print_message(phil, "is sleeping");
	usleep(phil->time_to_sleep * 1000);
}

//Sends a message and acts as a queue before eating is possible
static void	phil_thinks(t_philo *phil)
{
	print_message(phil, "is thinking");
}

//Main routine loop, keeps going untill a death
void	*phil_routine(void *pointer)
{
	t_philo	*phil;

	phil = (t_philo *)pointer;
	if (phil->nbr_of_philos == 1)
	{
		pthread_mutex_lock(phil->l_fork);
		print_message(phil, "has taken a fork");
		usleep(phil->time_to_die);
		pthread_mutex_unlock(phil->l_fork);
		return (pointer);
	}
	if (phil->id % 2 == 0)
		usleep(phil->time_to_eat * 500);
	while (!if_dead(phil))
	{
		phil_eats(phil);
		phil_sleeps(phil);
		phil_thinks(phil);
	}
	return (pointer);
}
