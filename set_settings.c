#include "philo.h"

void    init_set(t_set *set)
{
    set->nb_philo = 0;
    set->time_to_die = 0;
    set->time_to_eat = 0;
    set->time_to_sleep = 0;
    set->nb_meals = -1;
    set->id_index = 0;
    set->death = 0;
    set->flag = 0;
    set->fork = NULL;
    set->philo_is_dead = 0;
}

void    set_set(char **argv, t_set *set)
{
    set->nb_philo = ft_atoi(argv[1]);
    set->time_to_die = ft_atoi(argv[2]);
    set->time_to_eat = ft_atoi(argv[3]);
    set->time_to_sleep = ft_atoi(argv[4]);
    if (argv[5])
        set->nb_meals = ft_atoi(argv[5]);
}

void    init_thread(t_set *set, t_philo *philo)
{
    if (philo->id == 1 && set->flag == 0)
    {
        gettimeofday(&(set->start_time), NULL);
        set->flag = 1;
    }
}

t_philo *create_philo(t_set *set, int id_index)
{
    t_philo *philo;

    philo = malloc(sizeof(t_philo));
    philo->set = set;
    philo->id = id_index;
    philo->meals = set->nb_meals;
    philo->last_meal = 0;
    return (philo);
}

void    creat_and_join(t_set *set, t_philo *philo, pthread_t *id)
{
    while (set->id_index < set->nb_philo)
    {
        philo = create_philo(set, set->id_index + 1);
        pthread_create(&(id[set->id_index]), NULL, philo1, (void *)philo);
        set->id_index++;
    }
    set->id_index = 0;
    while (set->id_index < set->nb_philo)
    {
        pthread_join(id[set->id_index], NULL);
        set->id_index++;
    }
}

void    init_mutex(t_set *set)
{
    int x;

    x = 0;
    while (x < set->nb_philo)
    {
        pthread_mutex_init(&(set->fork[x]), NULL);
        x++;
    }
    pthread_mutex_init(&(set->print_n_death), NULL);
}

