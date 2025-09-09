/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:26:32 by roversch          #+#    #+#             */
/*   Updated: 2025/09/09 13:25:40 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Creates a fork mutex for each philo
void	init_forks(t_monitor *monitor, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < monitor->amount)
	{
		if (pthread_mutex_init(&fork[i], NULL) != 0)
			destroy_forks(monitor, i, "fork init error\n", 1);
		i++;
	}
}

//Sets up the monitor struct with flags and the mutex locks
void	init_monitor(t_monitor *monitor, t_philo *phil,
			pthread_mutex_t *fork, char **argv)
{
	monitor->philos = phil;
	monitor->forks = fork;
	monitor->amount = my_atol(argv[1]);
	monitor->dead = false;
	if (pthread_mutex_init(&monitor->eat_lock, NULL) != 0)
		destroy_all(monitor, 0, "eatlock init error\n", 1);
	if (pthread_mutex_init(&monitor->dead_lock, NULL) != 0)
		destroy_all(monitor, 0, "deadlock init error\n", 1);
	if (pthread_mutex_init(&monitor->print_lock, NULL) != 0)
		destroy_all(monitor, 0, "printlock init error\n", 1);
}

//Takes the user input to give to every philo struct
static void	init_input(t_philo *phil, char **argv)
{
	phil->time_to_die = my_atol(argv[2]);
	phil->time_to_eat = my_atol(argv[3]);
	phil->time_to_sleep = my_atol(argv[4]);
	if (argv[5])
		phil->nbr_times_to_eat = my_atol(argv[5]);
	else
		phil->nbr_times_to_eat = -1;
}

//Fills every philo struct and gives the mutex locks/forks
void	init_philos(t_monitor *monitor, t_philo *phil,
		pthread_mutex_t *fork, char **argv)
{
	int	i;

	i = 0;
	while (i < monitor->amount)
	{
		phil[i].id = i + 1;
		init_input(&phil[i], argv);
		phil[i].nbr_of_philos = monitor->amount;
		phil[i].times_eaten = 0;
		phil[i].time_born = get_time();
		phil[i].last_eaten = phil[i].time_born;
		phil[i].dead = &monitor->dead;
		phil[i].l_fork = &fork[i];
		if (monitor->amount == 1)
			phil[i].r_fork = NULL;
		else if (i == 0)
			phil[i].r_fork = &fork[monitor->amount - 1];
		else
			phil[i].r_fork = &fork[i - 1];
		phil[i].eat_lock = &monitor->eat_lock;
		phil[i].dead_lock = &monitor->dead_lock;
		phil[i].print_lock = &monitor->print_lock;
		i++;
	}
}

//Creates and later joins the philo and monitor threads
void	init_threads(t_monitor *monitor, t_philo *phil)
{
	int	i;

	i = 0;
	if (pthread_create(&monitor->thread, NULL, monitor_routine, monitor) != 1)
		destroy_all(monitor, 0, "pthread create error\n", 1);
	while (i < monitor->amount)
	{
		if (pthread_create(&phil[i].thread, NULL, phil_routine, &phil[i]) != 0)
			destroy_all(monitor, i, "pthread create error\n", 1);
		i++;
	}
	i = 0;
	if (pthread_join(monitor->thread, NULL) != 0)
		destroy_all(monitor, 0, "pthread join error\n", 1);
	while (i < monitor->amount)
	{
		if (pthread_join(phil[i].thread, NULL) != 0)
			destroy_all(monitor, 0, "pthread join error\n", 1);
		i++;
	}
}
