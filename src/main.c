#include "../includes/philo.h"

void init_simulation(t_simulation *sim, char **argv) 
{
    sim->num_philosophers = atoi(argv[1]);
    sim->forks = malloc(sizeof(pthread_mutex_t) * sim->num_philosophers);
    sim->philosophers = malloc(sizeof(t_philosopher) * sim->num_philosophers);
    sim->time_to_die = atoi(argv[2]);
    sim->time_to_eat = atoi(argv[3]);
    sim->time_to_sleep = atoi(argv[4]);
    if (argv[5])
        sim->must_eat = atoi(argv[5]);
    else
        sim->must_eat = -1;

    int i = 0;
    while (i < sim->num_philosophers) {
        pthread_mutex_init(&sim->forks[i], NULL);
        sim->philosophers[i].id = i;
        sim->philosophers[i].left_fork = &sim->forks[i];
        sim->philosophers[i].right_fork = &sim->forks[(i + 1) % sim->num_philosophers];
        i++;
    }
}


void *routine(void *philosopher) 
{
    t_philosopher *philo = (t_philosopher *)philosopher;

    while (1) {
        // Penser
        printf("Philosophe %d est en train de penser.\n", philo->id);
        // Manger
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);

        printf("Philosophe %d mange.\n", philo->id);
        // attendre le temps de manger

        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);

        // Dormir
        printf("Philosophe %d dort.\n", philo->id);
        // attendre le temps de dormir
    }
    return NULL;
}

int main(int argc, char **argv) {
    t_simulation sim;

	if(parsing(argc, argv) == 1)
	{
		// Initialiser la simulation avec le nombre de philosophes
		init_simulation(&sim, argv);

		pthread_t threads[sim.num_philosophers];

        int i = 0;
        while (i < sim.num_philosophers) 
        {
            pthread_create(&threads[i], NULL, routine, &sim.philosophers[i]);
        i++;
        }

        i = 0; // Réinitialiser le compteur pour la prochaine boucle
        while (i < sim.num_philosophers) 
        {
            pthread_join(threads[i], NULL);
            i++;
        }
        cleanup_simulation(&sim);


	}
    else
    {
        printf("Erreur dans le parsing.\n");
        return 1;
    }

}
