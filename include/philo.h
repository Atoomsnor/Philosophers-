/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:31:30 by roversch          #+#    #+#             */
/*   Updated: 2025/08/19 15:50:27 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>

#ifndef PHILO_H
# define PHILO_H

# define MAX_PHILS 200

typedef struct	s_philo
{
	pthread_t		thread;
	int				id;
	int				nbr_of_philos;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	int				nbr_times_to_eat;
	int				times_eaten;
	size_t			time_born;
	size_t			last_eaten;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}	t_philo;



long		my_atol(const char *nptr);
size_t		get_time(void);
void	print_message(t_philo *phil, char *action);
void	ft_usleep(size_t time);

#endif