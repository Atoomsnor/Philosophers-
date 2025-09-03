/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:31:30 by roversch          #+#    #+#             */
/*   Updated: 2025/09/03 17:21:32 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>

# define MAX_PHILS 200

typedef struct s_philo
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
	pthread_mutex_t	*print_lock;
}	t_philo;

typedef struct s_monitor
{
	pthread_t		thread;
	int				amount;
	bool			dead;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_monitor;

//	*main*	//

int		main(int argc, char **argv);

//	*init*	//

void	init_forks(t_monitor *monitor, pthread_mutex_t *fork);
/** 
 * Sets up the monitor struct with flags and the mutex locks
 * @param monitor struct containing the configuration of the program
 * @param phil array of philosophers
 * @param fork array of mutexes (forks)
 * @param argv program arguments
 * @return never returns
 */
void	init_monitor(t_monitor *monitor, t_philo *phil,
			pthread_mutex_t *fork, char **argv);
void	init_philos(t_monitor *monitor, t_philo *phil,
			pthread_mutex_t *fork, char **argv);
void	init_threads(t_monitor *monitor, t_philo *phil);

//	*routine*	//

void	*monitor_routine(void *pointer);
void	*phil_routine(void *pointer);
int		if_dead(t_philo *phil);

//	*utils*	//

// reaper

void	error_and_exit(char *error_msg, int exitcode);
void	destroy_all(t_monitor *monitor, int amount,
			char *error_msg, int exitcode);

// string_utils

long	my_atol(const char *nptr);
void	print_message(t_philo *phil, char *action);

// systime

size_t	get_time(void);

#endif