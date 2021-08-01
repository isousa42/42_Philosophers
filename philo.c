#include "philo.h"

void    *philo1(void    *arg)
{
    t_set *ptr;

    ptr = (t_set *)arg;
     while (1)
    {
        sleep(1);
        printf("I'm Philo 1  -- %d \n", ptr->nb_philo);

    }
}

int main(int argc, char **argv)
{
    t_set set;
    pthread_t id;
    pthread_t id2;


    if (argc < 5 || argc > 6 || (check_arg(argv) == 1))
    {
        printf("ERROR \n");
        return (0);
    }
    init_set(&set);
    set_set(argv, &set);

    int i = 0;

    while (i < 2)
    {
        pthread_create(&id, NULL, philo1, &set);
        pthread_join(id, NULL);
        i++;


    }

    pthread_create(&id2, NULL, philo1, &set);   

    pthread_join(id, NULL);
    pthread_join(id2, NULL);


    


    return (0);
}