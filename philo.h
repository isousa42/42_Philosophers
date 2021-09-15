#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_set
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nb_meals;
	int				id_index;
	int				death;
	int				philo_is_dead;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_n_death;
	struct timeval	start_time;
	int				flag;
}					t_set;

typedef struct s_philo
{
	t_set	*set;
	int		id;
	int		meals;
	double	last_meal;
}				t_philo;

void	*philo1(void *arg);
int		grab_forks(t_set *set, t_philo *philo, int fork_left, int fork_right);
int		eat_spaghetti(t_set *set, t_philo *philo,
			int fork_left, int fork_right);
int		drop_forks(t_set *set, int fork_left, int fork_right, t_philo *philo);
int		go_sleep(t_set *set, t_philo *philo);
int		go_think(t_set *set, t_philo *philo);
int		check_death(double last_meal, t_set *set, t_philo *philo);
int		death_calc(t_set *set, float time, float last_meal, int philo);
double	diff_time(struct timeval *start_time);
void	print_timestamp(t_set *set, int control, double time, int philo_id);
int		ft_atoi(const char *str);
int		ft_isdigit(int c);
int		check_arg(char **argv);
void	init_set(t_set *set);
void	set_set(char **argv, t_set *set);
void	init_thread(t_set *set, t_philo *philo);
t_philo	*create_philo(t_set *set, int id_index);
void	creat_and_join(t_set *set, t_philo *philo, pthread_t *id);
void	init_mutex(t_set *set);
void	destroy_mutex(t_set *set);
void	destroy_mutex(t_set *set);
void	ft_bzero(void *str, size_t n);
int		inicialization(int argc, char **argv, t_set *set);
int		ft_strlen(char *str);
int		norme_func(double time, t_set *set, t_philo *philo);

#endif