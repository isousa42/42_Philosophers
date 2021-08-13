#include "philo.h"

void	init_set(t_set *set)
{
	set->nb_philo = 0;
	set->time_to_die = 0;
	set->time_to_eat = 0;
	set->time_to_sleep = 0;
	set->nb_meals = -1;
	set->id_index = 0;
	set->death = 0;
	set->flag = 0;
	set->fork = NULL;
	set->philo_is_dead = 0;
}

void	set_set(char **argv, t_set *set)
{
	set->nb_philo = ft_atoi(argv[1]);
	set->time_to_die = ft_atoi(argv[2]);
	set->time_to_eat = ft_atoi(argv[3]);
	set->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		set->nb_meals = ft_atoi(argv[5]);
}

void	*philo1(void *arg)
{
	t_set	*set;
	t_philo	*philo;

	philo = (t_philo *)arg;
	set = philo->set;
	init_thread(set, philo);
	while (philo->meals)
	{
		if (grab_forks(set, philo, philo->id - 1, philo->id % set->nb_philo))
			break ;
		if (eat_spaghetti(set, philo, philo->id - 1, philo->id % set->nb_philo))
			break ;
		if (drop_forks(set, philo->id - 1, philo->id % set->nb_philo, philo))
			break ;
		if (go_sleep(set, philo))
			break ;
		if (go_think(set, philo))
			break ;
		usleep(500);
	}
	pthread_mutex_unlock(&set->print_n_death);
	free(philo);
	return (NULL);
}

int	inicialization(int argc, char **argv, t_set *set)
{
	if (argc < 5 || argc > 6 || (check_arg(argv) == 1))
	{
		printf("ERROR \n");
		return (1);
	}
	init_set(set);
	set_set(argv, set);
	if (set->nb_philo == 1)
	{
		usleep(set->time_to_die);
		print_timestamp(4, set->time_to_die, 1);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_set		set;
	t_philo		*philo;
	pthread_t	*id;

	philo = NULL;
	id = NULL;
	if (inicialization(argc, argv, &set))
		return (0);
	id = malloc(sizeof(pthread_t) * (set.nb_philo));
	set.fork = malloc(sizeof(pthread_mutex_t) * (set.nb_philo));
	init_mutex(&set);
	creat_and_join(&set, philo, id);
	destroy_mutex(&set);
	free(id);
	free(set.fork);
	return (0);
}
