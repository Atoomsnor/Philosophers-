/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:31:30 by roversch          #+#    #+#             */
/*   Updated: 2025/08/13 12:06:03 by roversch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

typedef struct	s_philo
{
	int			id;
	int			nbr_of_philos;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nbr_times_to_eat;
}	t_philo;

int	check_input(int argc, char **argv);

int	my_atoi(const char *nptr);

#endif