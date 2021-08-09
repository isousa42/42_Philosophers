#include "philo.h"

void    grab_forks(t_set *set, t_philo *philo, int fork_left, int fork_right)
{
    pthread_mutex_lock(&set->fork[fork_left]);
    pthread_mutex_lock(&set->fork[fork_right]);
    pthread_mutex_lock(&set->print);
    print_timestamp(0, diff_time(&set->start_time), philo->id);
    pthread_mutex_unlock(&set->print);
}

void    eat_spaghetti(t_set *set, t_philo *philo)
{
    pthread_mutex_lock(&set->print);
    philo->last_meal = diff_time(&set->start_time);
    print_timestamp(1, philo->last_meal, philo->id);
    pthread_mutex_unlock(&set->print);
    usleep(set->time_to_eat * 1000);
    philo->meals--;
}

void    drop_forks(t_set *set, int fork_left, int fork_right)
{
    pthread_mutex_unlock(&set->fork[fork_left]);
    pthread_mutex_unlock(&set->fork[fork_right]);
}

void    go_sleep(t_set *set, t_philo *philo)
{
    pthread_mutex_lock(&set->print);
    print_timestamp(2, diff_time(&set->start_time), philo->id);
    pthread_mutex_unlock(&set->print);
    usleep(set->time_to_sleep * 1000);
}

void    go_think(t_set *set, t_philo *philo)
{
    pthread_mutex_lock(&set->print);
    print_timestamp(3, diff_time(&set->start_time), philo->id);
    pthread_mutex_unlock(&set->print);
}