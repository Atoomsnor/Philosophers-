/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roversch <roversch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 10:15:06 by roversch          #+#    #+#             */
/*   Updated: 2025/08/13 11:12:58 by roversch         ###   ########.fr       */
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

int main(int argc, char **argv)
{
	if (!check_input(argc, argv))
		return (1);
	printf("ye\n");
}