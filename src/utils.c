#include "../includes/philo.h"

void cleanup_simulation(t_simulation *sim) {
    for (int i = 0; i < sim->num_philosophers; i++) {
        pthread_mutex_destroy(&sim->forks[i]);
    }
    free(sim->forks);
    free(sim->philosophers);
}
