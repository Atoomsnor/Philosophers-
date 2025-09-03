/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:17:03 by roversch          #+#    #+#             */
/*   Updated: 2025/09/03 17:21:45 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

//Prints the error message and exits with the correct code
void	error_and_exit(char *error_msg, int exitcode)
{
	if (error_msg)
		printf("%s", error_msg);
	exit(exitcode);
}

//Destroy all locks and all forks
void	destroy_all(t_monitor *monitor, int amount,
			char *error_msg, int exitcode)
{
	int	i;

	i = 0;
	if (amount)
	{
		while (amount >= 0)
		{
			pthread_mutex_destroy(&monitor->forks[amount]);
			amount--;
		}
	}
	else
	{
		while (i < monitor->amount)
		{
			pthread_mutex_destroy(&monitor->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&monitor->eat_lock);
	pthread_mutex_destroy(&monitor->dead_lock);
	pthread_mutex_destroy(&monitor->print_lock);
	error_and_exit(error_msg, exitcode);
}
