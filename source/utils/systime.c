/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   systime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/03 17:14:45 by roversch          #+#    #+#             */
/*   Updated: 2025/09/03 17:21:43 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>
#include <stdio.h>

//Time function that uses sys/time and makes it into milliseconds
size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday Error\n");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
