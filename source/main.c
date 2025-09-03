/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:15:06 by roversch          #+#    #+#             */
/*   Updated: 2025/09/03 13:22:13 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <limits.h>
#include <stdio.h>

//Looks to see if the input is valid according to the subject
static void	check_input(int argc, char **argv)
{
	int	i;
	int	amount;

	if (argc < 5 || argc > 6)
		error_and_exit("Argument error\n", 1);
	i = 1;
	while (i < argc)
	{
		amount = my_atol(argv[i]);
		if (i == 1 && (amount < 1 || amount > 200))
			error_and_exit("Argument error\n", 1);
		else if (i == 5 && (amount < 0 || amount > INT_MAX))
			error_and_exit("Argument error\n", 1);
		else if (i != 1 && i != 5 && (amount < 1 || amount > INT_MAX))
			error_and_exit("Argument error\n", 1);
		i++;
	}
}

//Start of program that sets up structs and goes through all inits
int	main(int argc, char **argv)
{
	t_monitor		monitor;
	t_philo			phil[MAX_PHILS];
	pthread_mutex_t	fork[MAX_PHILS];

	check_input(argc, argv);
	init_monitor(&monitor, phil, fork, argv);
	init_forks(&monitor, fork);
	init_philos(&monitor, phil, fork, argv);
	init_threads(&monitor, phil);
	destroy_all(&monitor, 0, NULL, 0);
}
