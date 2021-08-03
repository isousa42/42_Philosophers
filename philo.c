#include "philo.h"

void    *philo1(void *arg)
{
    t_set *set;
    set = (t_set *)arg;

    t_philo philo;

    philo.meals = set->nb_meals;
    philo.id = set->id_index;

    while (philo.meals > 0)
    {
        pthread_mutex_lock(&set->fork);
        printf("Philo %d start eating\n", philo.id);
        philo.meals--;
        printf("Philo %d finished eating\n", philo.id);
        pthread_mutex_unlock(&set->fork);
        sleep(5);

    }

    return NULL;
}

int main(int argc, char **argv)
{
    t_set set;
    pthread_t *id = NULL;

    if (argc < 5 || argc > 6 || (check_arg(argv) == 1))
    {
        printf("ERROR \n");
        return (0);
    }
    init_set(&set);
    set_set(argv, &set);

    // allocate memory for id of philos
    id = malloc(sizeof(pthread_t) * (set.nb_philo));
    pthread_mutex_init(&(set.fork), NULL);
    //create threads
    while (set.id_index < 3)
    {
        pthread_create(&(id[set.id_index]), NULL, philo1, &set);
        sleep(1);
        set.id_index++;
    }

    //join threads
    set.id_index = 0;
    while (set.id_index < 3)
    {
        pthread_join(id[set.id_index], NULL);
        set.id_index++;
    }

    return (0);
}