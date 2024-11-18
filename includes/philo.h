#ifndef PHILO_H
# define PHILO_H

/*
** libraries
*/

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
/*structure*/

#include <pthread.h>

typedef struct s_philosopher {
    int id;
    int times_ate;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    // Ajoute d'autres champs selon les besoins
} t_philosopher;

typedef struct s_simulation {
    int num_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
	int must_eat;
    pthread_mutex_t *forks;  // Tableau de mutex pour les fourchettes
    t_philosopher *philosophers;
} t_simulation;

//fonction 
//main.c
void init_simulation(t_simulation *sim, char **argv);
void *routine(void *philosopher);

// parsing.c
int is_only_digits(const char *str);
int parsing(int ac, char **av);

//utils.c
void cleanup_simulation(t_simulation *sim);

# endif