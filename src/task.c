/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabenet <mabenet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:33:18 by mabenet           #+#    #+#             */
/*   Updated: 2025/03/12 16:34:00 by mabenet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"


static int	p_eat3(t_philo *philo, t_data *data, int left, int right)
{
	if (philo->meals == data->wanted_meals)
	{
		pthread_mutex_unlock(&data->fork[left]);
		pthread_mutex_unlock(&data->fork[right]);
		return (0);
	}
	print_task(philo, "is eating");
	pthread_mutex_lock(&data->time);
	philo->meals++;
	pthread_mutex_unlock(&data->time);
	wait_time(data, data->time_to_eat);
	pthread_mutex_unlock(&data->fork[left]);
	pthread_mutex_unlock(&data->fork[right]);
	return (1);
}

static int	p_eat2(t_philo *philo, t_data *data, int left, int right)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&data->fork[right]);
	else
		pthread_mutex_lock(&data->fork[left]);
	print_task(philo, "has taken a fork");
	pthread_mutex_lock(&data->is_dead);
	if (data->is_a_philo_dead)
	{
		pthread_mutex_unlock(&data->fork[left]);
		pthread_mutex_unlock(&data->fork[right]);
		pthread_mutex_unlock(&data->is_dead);
		return (0);
	}
	pthread_mutex_unlock(&data->is_dead);
	pthread_mutex_lock(&data->time);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&data->time);
	if (!p_eat3(philo, data, left, right))
		return (0);
	return (1);
}

int	p_eat(t_philo *philo, t_data *data)
{
	int		left;
	int		right;

	left = philo->id - 1;
	right = philo->id;
	if (philo->id == data->num_of_philos)
		right = 0;
	pthread_mutex_lock(&data->is_dead);
	if (data->is_a_philo_dead)
		return (pthread_mutex_unlock(&data->is_dead), 0);
	pthread_mutex_unlock(&data->is_dead);
	if (philo->id % 2 == 1)
		pthread_mutex_lock(&data->fork[left]);
	else
		pthread_mutex_lock(&data->fork[right]);
	print_task(philo, "has taken a fork");
	if (!p_eat2(philo, data, left, right))
		return (0);
	return (1);
}

void	p_sleep(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_task(philo, "is sleeping");
	wait_time(data, data->time_to_sleep);
}
