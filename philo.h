#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

//list of threads id
typedef struct	s_idlist
{
	pthread_t   *content;
	struct s_idlist	*next;
}				t_idlist;

//struct to initialize the arguments from argv
typedef struct  s_set
{
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_meals;
    struct s_idlist *id_list;
    
}               t_set;

//utils
double dif_time(struct timeval *start, struct timeval *end);
int	ft_atoi(const char *str);
int	ft_isdigit(int c);
int check_arg(char **argv);

//set_settings.c
void    init_set(t_set *set);
void    set_set(char **argv, t_set *set);

