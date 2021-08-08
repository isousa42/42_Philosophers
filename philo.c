#include "philo.h"

// PHILO 1 AND IMPAR EATING ONLY WITH 1 FORK

int check_death(double time, double last_meal, int time_to_die)
{
    if (time - (last_meal) > time_to_die)
        return (1);
    return (0);
}

void    *philo1(void *arg)
{
    t_set *set;
    set = (t_set *)arg;
    while(set->start);


    t_philo philo;
    double time = 0;
    double last_meal = 0;
    
    if (philo.id == 0 && set->flag == 0)
    {
        gettimeofday(&(set->start_time), NULL);
        set->flag = 1;
    }

    philo.meals = set->nb_meals;
    philo.id = set->id_index + 1;

    while (philo.meals)
    {
        if (philo.id == 0)
        {
            pthread_mutex_lock(&set->fork[0]);
            pthread_mutex_lock(&set->fork[set->nb_philo - 1]);
            pthread_mutex_lock(&set->print);
            //time = diff_time(&set->start_time);
            print_timestamp(0, diff_time(&set->start_time), philo.id);
            pthread_mutex_unlock(&set->print);
        }
        else
        {
            pthread_mutex_lock(&set->fork[philo.id]);
            pthread_mutex_lock(&set->fork[philo.id - 1]);
            pthread_mutex_lock(&set->print);
            //time = diff_time(&set->start_time);
            print_timestamp(0, diff_time(&set->start_time), philo.id);
            pthread_mutex_unlock(&set->print);
        }

        pthread_mutex_lock(&set->print);
        last_meal = diff_time(&set->start_time);
        print_timestamp(1, last_meal, philo.id);
        pthread_mutex_unlock(&set->print);
        usleep(set->time_to_eat * 1000);

        // CHECK DEATH
        //time = diff_time(&set->start_time);
        if (check_death(diff_time(&set->start_time), last_meal, set->time_to_die))
        {
            pthread_mutex_lock(&set->print);

            printf("TIME = %f, LAST_MEAL = %f\n", diff_time(&set->start_time), last_meal);
            print_timestamp(4, diff_time(&set->start_time), philo.id);
            pthread_mutex_unlock(&set->print);

            exit(0);
        }

        philo.meals--;
        if (philo.id == 0)
        {
            pthread_mutex_unlock(&set->fork[0]);
            pthread_mutex_unlock(&set->fork[set->nb_philo - 1]);
        }
        else
        {
            pthread_mutex_unlock(&set->fork[philo.id]);
            pthread_mutex_unlock(&set->fork[philo.id - 1]);
        }
        pthread_mutex_lock(&set->print);
        //time = diff_time(&set->start_time);
        print_timestamp(2, diff_time(&set->start_time), philo.id);
        pthread_mutex_unlock(&set->print);


// CHECK DEATH
        time = diff_time(&set->start_time);
        if (check_death(time, last_meal, set->time_to_die))
        {
            pthread_mutex_lock(&set->print);

            printf("TIME = %f, LAST_MEAL = %f\n", time, last_meal);
            print_timestamp(4, diff_time(&set->start_time), philo.id);
            pthread_mutex_unlock(&set->print);

            exit(0);
        }


        // PUT WHILE HERE (break when passes the time to usleep)
        usleep(set->time_to_sleep * 1000);
        pthread_mutex_lock(&set->print);
        time = diff_time(&set->start_time);
        print_timestamp(3, time, philo.id);
        pthread_mutex_unlock(&set->print);

        // CHECK DEATH
        time = diff_time(&set->start_time);
        if (check_death(time, last_meal, set->time_to_die))
        {
            pthread_mutex_lock(&set->print);

            printf("TIME = %f, LAST_MEAL = %f\n", time, last_meal);
            print_timestamp(4, diff_time(&set->start_time), philo.id);
            pthread_mutex_unlock(&set->print);

            exit(0);
        }

    }
    return (NULL);
}

int main(int argc, char **argv)
{
    t_set set;
    pthread_t *id = NULL;
    set.start = 1;

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
    set.start = 0;

    return (0);
}