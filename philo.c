#include "philo.h"

double dif_time(struct timeval *start, struct timeval *end)
{
    double dif_time;

    dif_time = (end->tv_sec - start->tv_sec) * 1000.0;
    dif_time += (end->tv_usec - start->tv_usec) / 1000.0;
    
    return (dif_time);
}

void    *just_test(void *arg)
{
    (void)arg;
    printf("philo is here! \n");

    return NULL;
}

void    *just(void *arg)
{
    (void)arg;
    printf("philo2 is here TOOO! \n");

    return NULL;
}

void     other_test(void)
{
    printf("he is NOT here... \n");

}

int main()
{
    //struct timeval start_time;
    //struct timeval end_time;
    //double time;

    pthread_t   philo_1;
    pthread_t   philo_2;

    pthread_create(&philo_1, NULL, just_test, NULL);
    pthread_create(&philo_2, NULL, just, NULL);


    //gettimeofday(&start_time, NULL);

    other_test();
    
    pthread_join(philo_1, NULL);
    pthread_join(philo_2, NULL);


    //gettimeofday(&end_time, NULL);
    //time = dif_time(&start_time, &end_time);
    //printf("time = %f \n", time);
    
    return (0);
}