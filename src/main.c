#include "../includes/philo.h"

static void	only_one_philo(t_data *data)
{
	printf("%lld\t%d has taken a fork\n", get_time_from(data->start_time), 1);
	usleep(data->time_to_die * 1000);
	printf("%lld\t%d has died\n", get_time_from(data->start_time), 1);
}

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philo;

	if (!check_args(ac, av))
		return (-1);
	init_data(ac, av, &data);
	philo = malloc(data.num_of_philos * sizeof(t_philo));
	if (!philo)
		return (-1);
	init_philos(&data, philo);
	if (data.num_of_philos == 1)
		return (only_one_philo(&data), free(philo), 0);
	if (!init_mutex(&data))
		return (free(philo), -1);
	if (!init_threads(&data, philo))
		return (destroy_mutex(&data), free(philo), -1);
	destroy_mutex(&data);
	free(philo);
	return (0);
}