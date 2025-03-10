#include "../includes/philo.h"


static void	set_color(t_philo *philo)
{
	if (philo->id % 7 == 1)
		printf("\033[0;31m");
	else if (philo->id % 7 == 2)
		printf("\033[0;32m");
	else if (philo->id % 7 == 3)
		printf("\033[0;33m");
	else if (philo->id % 7 == 4)
		printf("\033[0;34m");
	else if (philo->id % 7 == 5)
		printf("\033[0;35m");
	else if (philo->id % 7 == 6)
		printf("\033[0;36m");
	else if (philo->id % 7 == 0)
		printf("\033[0;37m");
}

void	print_task(t_philo *philo, char *msg)
{
	t_data			*data;
	long long		time;

	data = philo->data;
	pthread_mutex_lock(&data->printing);
	time = get_time_from(data->start_time);
	pthread_mutex_lock(&data->is_dead);
	if (data->is_a_philo_dead)
	{
		pthread_mutex_unlock(&data->printing);
		pthread_mutex_unlock(&data->is_dead);
		return ;
	}
	pthread_mutex_unlock(&data->is_dead);
	printf("%lld\t", time);
	set_color(philo);
	printf("%d %s", philo->id, msg);
	printf("\033[0;37m\n\033[0m");
	pthread_mutex_unlock(&data->printing);
}
