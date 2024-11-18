#include "../includes/philo.h"

int is_only_digits(const char *str)
{
    int i;


	i = 0;;

    if (str[i] == '\0')
        return 0;
	 while (str[i] != '\0')
		{
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
        i++;
    }
    return 1;
}

int parsing(int ac, char **av) {
    int i = 1; // Commence à 1 pour ignorer le nom du programme
    if (ac < 5 || ac > 6) {
        printf("Erreur : Nombre d'arguments invalide.\n");
        return 0;
    }
    while (av[i]) {
        if (is_only_digits(av[i]) != 1) {
            printf("Erreur : Argument invalide.\n");
            return 0;
        }
        i++;
    }
    return 1;
}
