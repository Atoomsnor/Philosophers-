/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:15:06 by roversch          #+#    #+#             */
/*   Updated: 2025/08/26 16:39:54 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int	check_input(int argc, char **argv)
{
	int	i;
	int	amount;

	amount = my_atol(argv[1]);
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

int main(int argc, char **argv)
{
	t_monitor		monitor;
	t_philo			phil[MAX_PHILS];
	pthread_mutex_t	fork[MAX_PHILS];

	if (!check_input(argc, argv))
		return (printf("uh-oh\n"), 1);
	init_monitor(&monitor, phil, argv);
	init_forks(&monitor, fork); //we now need to clean forks
	init_philos(&monitor, phil, fork, argv); //we now need to clean phil and forks
	init_threads(&monitor, phil); //something can go wrong here so clean phil and forks,
	// printf("Die funciton goes here\n") //clean phil/forks and threads??? or time????
	// printf("ye\n");
}