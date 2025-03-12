/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:33:40 by mabenet           #+#    #+#             */
/*   Updated: 2025/03/12 16:33:57 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	print_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(STDERR_FILENO, &msg[i], 1);
		i++;
	}
	return (0);
}

static int	print_args_error(void)
{
	print_error("Error: Invalid arguments.\n\nUsage: ./philo ");
	print_error("number_of_philosophers time_to_die time_to_eat time_to");
	print_error("_sleep [number_of_times_each_philosopher_must_eat]\n\n");
	print_error("(Time in milliseconds)\n");
	return (0);
}

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5 && ac != 6)
		return (print_args_error());
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (print_args_error());
			j++;
		}
		i++;
	}
	return (1);
}
