#include "philo.h"

int main(int argc, char **argv)
{
    t_set set;

    if (argc < 5 || argc > 6 || (check_arg(argv) == 1))
    {
        printf("ERROR \n");
        return (0);
    }
    init_set(&set);
    set_set(argv, &set);
    

    return (0);
}