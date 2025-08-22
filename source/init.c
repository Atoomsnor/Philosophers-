/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 16:26:32 by roversch          #+#    #+#             */
/*   Updated: 2025/08/22 17:08:31 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	init_forks(pthread_mutex_t *fork, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		pthread_mutex_init(&fork[i], NULL);
		i++;
	}
	printf("Made %i sets of forks\n", i);
}

void	init_monitor(t_monitor *monitor, t_philo *phil)
{
	monitor->philos = phil;
}

void	init_philos(t_philo *phil, pthread_mutex_t *fork, char **argv, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		phil[i].id = i + 1;
		phil[i].nbr_of_philos = amount;
		phil[i].time_to_die = my_atol(argv[2]);
		phil[i].time_to_eat = my_atol(argv[3]);
		phil[i].time_to_sleep = my_atol(argv[4]);
		if (argv[5])
			phil[i].nbr_times_to_eat = my_atol(argv[5]);
		else
			phil[i].nbr_times_to_eat = 0;
		phil[i].times_eaten = 0;
		phil[i].time_born = get_time();
		phil[i].last_eaten = phil[i].time_born;
		phil[i].l_fork = &fork[i];
		if (amount == 1) //only 1 philo means no rightfork
			phil[i].r_fork = NULL;
		else if (i == 0) //first philo wraps around for rightfork
			phil[i].r_fork = &fork[amount - 1];
		else
			phil[i].r_fork = &fork[i - 1];
		// printf("%d %d %d %d %d %d\n", phil[i].id, phil[i].nbr_of_philos, phil[i].time_to_die, phil[i].time_to_eat,
		// 	phil[i].time_to_sleep, phil[i].nbr_times_to_eat);
		i++;
	}
}

void	init_threads(t_monitor *monitor, t_philo *phil, int amount)
{
	int	i;

	i = 0;
	if (pthread_create(&monitor->thread, NULL, monitor_routine, monitor->philos) != 0)
			printf("Die funciton goes here\n");
	
	while (i < amount)
	{
		if (pthread_create(&phil[i].thread, NULL, phil_routine, &phil[i]) != 0)
			printf("Die funciton goes here\n");
		i++;
	}
	i = 0;
	if (pthread_join(monitor->thread, NULL) != 0)
			printf("Die funciton goes here\n");
	while (i < amount)
	{
		if (pthread_join(phil[i].thread, NULL) != 0)
			printf("Die funciton goes here\n");
		i++;
	}
}