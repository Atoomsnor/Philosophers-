/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 11:07:53 by roversch          #+#    #+#             */
/*   Updated: 2025/09/09 15:35:08 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Ascii to int to transform the input
int	my_atoi(const char *nptr)
{
	long	result;
	int		parity;
	int		i;

	result = 0;
	parity = 1;
	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\v' || nptr[i] == '\f' || nptr[i] == '\r')
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			parity = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	if (i > 10)
		return (-1);
	if (result > INT_MAX || result < INT_MIN)
		return (-1);
	return (result * parity);
}

//Sees if the character is numeric
int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	}
	return (1);
}

//Prints given action with time and phil id
void	print_message(t_philo *phil, char *action)
{
	size_t	time;

	pthread_mutex_lock(phil->print_lock);
	time = get_time() - phil->time_born;
	if (!if_dead(phil))
		printf("%zu %i %s\n", time, phil->id, action);
	pthread_mutex_unlock(phil->print_lock);
}
