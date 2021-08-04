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
