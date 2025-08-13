/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:15:06 by roversch          #+#    #+#             */
/*   Updated: 2025/08/13 12:15:20 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <pthread.h>
#include <limits.h>
#include <stdio.h>

int	check_input(int argc, char **argv)
{
	int	i;
	int	num;

	if (argc < 5 || argc > 6)
		return (printf("Wrong amount of arguments\n"), 1);
	i = 1;
	while (i < argc)
	{
		num = my_atoi(argv[i]);
		if (i == 1 && (num < 1 || num > 200 ))
			return (printf("Argument error\n"), 0);
		else if (i != 1 && i != 5 && (num < 1 || num > INT_MAX))
			return (printf("Argument error2\n"), 0);
		i++;
	}
	return (1);
}

void	init_philos(t_philo *phil, char **argv)
{
	int	i;
	int	amount;

	i = 1;
	amount = my_atoi(argv[1]);
	while (i < amount)
	{
		phil[i].id = i;
		phil[i].nbr_of_philos = my_atoi(argv[1]);
		phil[i].time_to_die = my_atoi(argv[2]);
		phil[i].time_to_eat = my_atoi(argv[3]);
		phil[i].time_to_sleep = my_atoi(argv[4]);
		if (argv[5])
			phil[i].nbr_times_to_eat = my_atoi(argv[5]);
		else
			phil[i].nbr_times_to_eat = 0;
		printf("%d %d %d %d %d %d\n", phil[i].id, phil[i].nbr_of_philos, phil[i].time_to_die, phil[i].time_to_eat, phil[i].time_to_sleep, phil[i].nbr_times_to_eat);
		i++;
	}
}


int main(int argc, char **argv)
{
	t_philo	phil[200];

	if (!check_input(argc, argv))
		return (1);
	init_philos(phil, argv);
	printf("ye\n");
}