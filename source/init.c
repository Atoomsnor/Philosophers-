/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:26:32 by roversch          #+#    #+#             */
/*   Updated: 2025/08/26 16:41:06 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	init_forks(t_monitor *monitor, pthread_mutex_t *fork)
{
	int	i;

	i = 0;
	while (i < monitor->amount)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
}

void	init_monitor(t_monitor *monitor, t_philo *phil, char **argv)
{
	monitor->philos = phil;
	monitor->amount = my_atol(argv[1]);
	monitor->dead = false; //maybe not needed?
	pthread_mutex_init(&monitor->dead_lock, NULL);
	pthread_mutex_init(&monitor->eat_lock, NULL);
}

void	init_philos(t_monitor *monitor, t_philo *phil, pthread_mutex_t *fork, char **argv)
{
	int	i;

	i = 0;
	while (i < monitor->amount)
	{
		phil[i].id = i + 1;
		phil[i].nbr_of_philos = monitor->amount;
		phil[i].time_to_die = my_atol(argv[2]);
		phil[i].time_to_eat = my_atol(argv[3]);
		phil[i].time_to_sleep = my_atol(argv[4]);
		if (argv[5])
			phil[i].nbr_times_to_eat = my_atol(argv[5]);
		else
			phil[i].nbr_times_to_eat = -1; // -1?
		phil[i].times_eaten = 0;
		phil[i].time_born = get_time(); //maybe put on start of thread init
		phil[i].last_eaten = phil[i].time_born;
		phil[i].dead = &monitor->dead;
		phil[i].l_fork = &fork[i];
		if (monitor->amount == 1) //only 1 philo means no rightfork
			phil[i].r_fork = NULL;
		else if (i == 0) //first philo wraps around for rightfork
			phil[i].r_fork = &fork[monitor->amount - 1];
		else
			phil[i].r_fork = &fork[i - 1];
		phil[i].dead_lock = &monitor->dead_lock;
		phil[i].eat_lock = &monitor->eat_lock;
		// printf("%d %d %d %d %d %d\n", phil[i].id, phil[i].nbr_of_philos, phil[i].time_to_die, phil[i].time_to_eat,
		// 	phil[i].time_to_sleep, phil[i].nbr_times_to_eat);
		i++;
	}
}

void	init_threads(t_monitor *monitor, t_philo *phil)
{
	int	i;

	i = 0;
	if (pthread_create(&monitor->thread, NULL, monitor_routine, monitor) != 0)
			printf("Die funciton goes here\n");
	
	while (i < monitor->amount)
	{
		if (pthread_create(&phil[i].thread, NULL, phil_routine, &phil[i]) != 0)
			printf("Die funciton goes here\n");
		i++;
	}
	i = 0;
	if (pthread_join(monitor->thread, NULL) != 0)
			printf("Die funciton goes here\n");
	while (i < monitor->amount)
	{
		if (pthread_join(phil[i].thread, NULL) != 0)
			printf("Die funciton goes here\n");
		i++;
	}
}