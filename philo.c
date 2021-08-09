#include "philo.h"

// PHILO 1 AND IMPAR EATING ONLY WITH 1 FORK

void    init_thread(t_set *set, t_philo *philo)
{
    philo->last_meal = 0;
    
    if (philo->id == 0 && set->flag == 0)
    {
        gettimeofday(&(set->start_time), NULL);
        set->flag = 1;
    }

    philo->meals = set->nb_meals;
    philo->id = set->id_index + 1;
}


void    *philo1(void *arg)
{
    t_set *set;
    set = (t_set *)arg;
    t_philo philo;
    init_thread(set, &philo);

    // printf("%p\n", set);
    printf("%p\n", &(set->id_index));
    while (philo.meals)
    {
        //GRAB FORKS -- MAKE UPDATE !!!
        if (philo.id == 0)
            grab_forks(set, &philo, 0, set->nb_philo - 1);
        else
            grab_forks(set, &philo, philo.id, philo.id - 1);

        // EAT SPAGHETTI
        eat_spaghetti(set, &philo);

        // CHECK DEATH
        check_death(diff_time(&set->start_time), philo.last_meal, set, &philo);

        // DROP FORKS
        if (philo.id == 0)
            drop_forks(set, 0, set->nb_philo - 1);
        else
            drop_forks(set, philo.id, philo.id - 1);

        // SLEEPING
        go_sleep(set, &philo);

        // CHECK DEATH
        check_death(diff_time(&set->start_time), philo.last_meal, set, &philo);
        
        // THINKING
        go_think(set, &philo);

        // CHECK DEATH
        check_death(diff_time(&set->start_time), philo.last_meal, set, &philo);
    }
    return (NULL);
}

t_philo *create_philo(t_set *set, int id_index)
{
    t_philo *philo;

    philo = malloc(sizeof(t_philo));
    philo->set = set;
    
}

int main(int argc, char **argv)
{
    t_set set;
    t_philo *philo;
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
    set.fork = malloc(sizeof(pthread_mutex_t) * (set.nb_philo));
    int x = 0;
    while (x < set.nb_philo)
    {
        pthread_mutex_init(&(set.fork[x]), NULL);
        x++;
    }
    pthread_mutex_init(&(set.print), NULL);
    //create threads
    while (set.id_index < set.nb_philo)
    {
        philo = create_philo(&set, set.id_index);
        pthread_create(&(id[set.id_index]), NULL, philo1, &set);
        usleep(50);
        set.id_index++;
    }

    //join threads
    set.id_index = 0;
    while (set.id_index < set.nb_philo)
    {
        pthread_join(id[set.id_index], NULL);
        set.id_index++;
    }

    return (0);
}