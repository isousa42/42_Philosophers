#include "philo.h"

void    *philo1(void *arg)
{
    int *ptr;
    ptr = (int *)arg;

    printf("AQUI\n");    
    if ((*ptr) == 0)
    {
        printf("this is philo 1\n");
        sleep(5);
        printf("this is philo 1 for the 2n time\n");

    }
    if ((*ptr) == 1)
    {
        printf("this is philo 2\n");
        sleep(5);
        printf("this is philo 2 for the 2n time\n");
    }
    if ((*ptr) == 2)
    {
        printf("this is philo 3\n");
        sleep(5);
        printf("this is philo 3 for the 2n time\n");
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
    
    int i = 0;

    while (i < 3)
    {
        printf("CHEGOU\n");    

        pthread_create(&(id[i]), NULL, philo1, &i);
        sleep(1);
        
        i++;
    }

    i = 0;
    while (i < 3)
    {
        pthread_join(id[i], NULL);
        i++;
    }

    return (0);
}