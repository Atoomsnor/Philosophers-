/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:31:30 by roversch          #+#    #+#             */
/*   Updated: 2025/08/26 16:38:37 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>

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
	bool			*dead;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*eat_lock;
	pthread_mutex_t	*dead_lock;
}	t_philo;

typedef struct	s_monitor
{
	pthread_t	thread;
	int			amount;
	bool		dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
	t_philo		*philos;
}	t_monitor;

//	*init*	//
void	init_forks(t_monitor *monitor, pthread_mutex_t *fork);
void	init_monitor(t_monitor *monitor, t_philo *phil, char **argv);
void	init_philos(t_monitor *monitor, t_philo *phil, pthread_mutex_t *fork, char **argv);
void	init_threads(t_monitor *monitor, t_philo *phil);

//	*routine*	//
void	*monitor_routine(void *pointer);
void	*phil_routine(void *pointer);

//	*utils*	//
long	my_atol(const char *nptr);
size_t	get_time(void);
void	print_message(t_philo *phil, char *action);


#endif