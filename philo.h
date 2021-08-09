#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

//struct to initialize the arguments from argv
typedef struct  s_set
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_meals;
    int id_index;
    int death;
    pthread_mutex_t *fork;
    pthread_mutex_t print;
    struct timeval start_time;
    int flag;
    
}               t_set;

typedef struct  s_philo
{
    t_set *set;
    int id;
    int meals;
    double last_meal;
}               t_philo;

//do_something.c
void    grab_forks(t_set *set, t_philo *philo, int fork_left, int fork_right);
void    eat_spaghetti(t_set *set, t_philo *philo);
void    drop_forks(t_set *set, int fork_left, int fork_right);
void    go_sleep(t_set *set, t_philo *philo);
void    go_think(t_set *set, t_philo *philo);


//utils
void    check_death(double time, double last_meal, t_set *set, t_philo *philo);
int death_calc(double time, double last_meal, int time_to_die);
double diff_time(struct timeval *start_time);
void	print_timestamp(int control, double time, int philo_id);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int check_arg(char **argv);

//set_settings.c
void    init_set(t_set *set);
void    set_set(char **argv, t_set *set);

