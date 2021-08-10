#include "philo.h"

void    *philo1(void *arg)
{
    t_set *set;
    t_philo *philo;
    philo = (t_philo *)arg;
    set = philo->set;
    
    init_thread(set, philo);
    while (philo->meals)
    {
        if (check_death(diff_time(&set->start_time), philo->last_meal, set, philo))
            break;
        if(grab_forks(set, philo, philo->id - 1, philo->id % set->nb_philo))
            break;
        if(eat_spaghetti(set, philo))
            break;
        if(drop_forks(set, philo->id - 1, philo->id % set->nb_philo, philo))
            break;
        if (check_death(diff_time(&set->start_time), philo->last_meal, set, philo))
            break;
        if (go_sleep(set, philo))
            break;
        if (check_death(diff_time(&set->start_time), philo->last_meal, set, philo))
            break;
        if (go_think(set, philo))
            break;
        if (check_death(diff_time(&set->start_time), philo->last_meal, set, philo))
            break;
        usleep(1000);
    }
    free(philo);
    return (NULL);
}

int main(int argc, char **argv)
{
    t_set set;

    t_philo *philo = NULL;
    pthread_t *id = NULL;

    if (argc < 5 || argc > 6 || (check_arg(argv) == 1))
    {
        printf("ERROR \n");
        return (0);
    }
    init_set(&set);
    set_set(argv, &set);
    if (set.nb_philo == 1)
    {
        usleep(set.time_to_die);
        print_timestamp(4, set.time_to_die, 1);
        return (0);
    }
    id = malloc(sizeof(pthread_t) * (set.nb_philo));
    set.fork = malloc(sizeof(pthread_mutex_t) * (set.nb_philo));
    init_mutex(&set);
    creat_and_join(&set, philo, id);
    destroy_mutex(&set);
    free(id);
    free(set.fork);
    return (0);
}