/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:15:06 by roversch          #+#    #+#             */
/*   Updated: 2025/08/19 16:39:14 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int	check_input(int argc, int amount)
{
	int	i;

	//check for negative imput
	if (argc < 5 || argc > 6)
		return (printf("Wrong amount of arguments\n"), 0);
	i = 1;
	while (i < argc)
	{
		if (i == 1 && (amount < 1 || amount > 200 ))
			return (printf("Argument error\n"), 0);
		else if (i != 1 && i != 5 && (amount < 1 || amount > INT_MAX))
			return (printf("Argument error2\n"), 0);
		i++;
	}
	return (1);
}

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

void	*phil_routine(void *pointer)
{
	t_philo	*phil;
	
	phil = (t_philo *)pointer;
	//put all of this shit in a while loop that keeps going till everything dies
	while (1) //check if someone dies
	{
		// if (phil->time_to_die <= (get_time() - phil->last_eaten))
		// 	return (printf("bigphil nr: %d died\n", phil->id), pointer);
		// if (phil->nbr_times_to_eat > 0 && phil->times_eaten >= phil->nbr_times_to_eat)
		// 	return (printf("bigphil nr: %d finished eatin\n", phil->id), pointer);
		if (phil->id % 2 == 0)
			ft_usleep(1);
		printf("bigphil nr: %d is going\n", phil->id);
		//fork
		pthread_mutex_lock(phil->l_fork);
		print_message(phil, "has taken a fork");
		pthread_mutex_lock(phil->r_fork);
		print_message(phil, "has taken a fork");
		//eat
		print_message(phil, "is eating");
		ft_usleep(phil->time_to_eat); //stole this from some rando
		phil->last_eaten = get_time();
		phil->times_eaten++;
		pthread_mutex_unlock(phil->l_fork);
		pthread_mutex_unlock(phil->r_fork);
		//sleep
		print_message(phil, "is sleeping");
		ft_usleep(phil->time_to_sleep); //stole this from some rando
		//think
		print_message(phil, "is thinking");
		//die?
		//unlock

		printf("bigphil nr: %d is done\n", phil->id);
	}
	return (pointer);
}

void	init_threads(t_philo *phil, int amount)
{
	int	i;

	i = 0;
	while (i < amount)
	{
		if (pthread_create(&phil[i].thread, NULL, phil_routine, &phil[i]) != 0)
			printf("Die funciton goes here\n");
		i++;
	}
	i = 0;
	while (i < amount)
	{
		if (pthread_join(phil[i].thread, NULL) != 0)
			printf("Die funciton goes here\n");
		i++;
	}
}

int main(int argc, char **argv)
{
	t_philo			phil[MAX_PHILS];
	pthread_mutex_t	fork[MAX_PHILS];

	int	amount;

	amount = my_atol(argv[1]);
	if (!check_input(argc, amount))
		return (printf("uh-oh\n"), 1);
	init_forks(fork, amount); //we now need to clean forks
	init_philos(phil, fork, argv, amount); //we now need to clean phil and forks
	init_threads(phil, amount); //something can go wrong here so clean phil and forks,
	// printf("Die funciton goes here\n") //clean phil/forks and threads??? or time????
	// printf("ye\n");
}