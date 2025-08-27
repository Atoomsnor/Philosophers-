/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 13:54:24 by roversch          #+#    #+#             */
/*   Updated: 2025/08/27 13:59:39 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

void	print_fork(t_philo *phil)
{
	size_t	time;

	pthread_mutex_lock(phil->print_lock);
	time = get_time() - phil->time_born;
	if (!*phil->dead)
		printf("%zu %i has taken a fork\n", time, phil->id);
	pthread_mutex_unlock(phil->print_lock);
}

void	print_eating(t_philo *phil)
{
	size_t	time;

	pthread_mutex_lock(phil->print_lock);
	time = get_time() - phil->time_born;
	if (!*phil->dead)
		printf("%zu %i is eating\n", time, phil->id);
	pthread_mutex_unlock(phil->print_lock);
}

void	print_sleeping(t_philo *phil)
{
	size_t	time;

	pthread_mutex_lock(phil->print_lock);
	time = get_time() - phil->time_born;
	if (!*phil->dead)
		printf("%zu %i is sleeping\n", time, phil->id);
	pthread_mutex_unlock(phil->print_lock);
}

void	print_thinking(t_philo *phil)
{
	size_t	time;

	pthread_mutex_lock(phil->print_lock);
	time = get_time() - phil->time_born;
	if (!*phil->dead)
		printf("%zu %i is thinking\n", time, phil->id);
	pthread_mutex_unlock(phil->print_lock);
}

void	print_died(t_philo *phil)
{
	size_t	time;

	pthread_mutex_lock(phil->print_lock);
	time = get_time() - phil->time_born;
	if (!*phil->dead)
		printf("%zu %i died\n", time, phil->id);
	pthread_mutex_unlock(phil->print_lock);
}