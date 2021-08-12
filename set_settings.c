#include "philo.h"

void	init_thread(t_set *set, t_philo *philo)
{
	if (philo->id == 1 && set->flag == 0)
	{
		gettimeofday(&(set->start_time), NULL);
		set->flag = 1;
	}
}

t_philo	*create_philo(t_set *set, int id_index)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->set = set;
	philo->id = id_index;
	philo->meals = set->nb_meals;
	philo->last_meal = 0;
	return (philo);
}

void	creat_and_join(t_set *set, t_philo *philo, pthread_t *id)
{
	while (set->id_index < set->nb_philo)
	{
		philo = create_philo(set, set->id_index + 1);
		pthread_create(&(id[set->id_index]), NULL, philo1, (void *)philo);
		set->id_index++;
	}
	set->id_index = 0;
	while (set->id_index < set->nb_philo)
	{
		pthread_join(id[set->id_index], NULL);
		set->id_index++;
	}
}

void	init_mutex(t_set *set)
{
	int	x;

	x = 0;
	while (x < set->nb_philo)
	{
		pthread_mutex_init(&(set->fork[x]), NULL);
		x++;
	}
	pthread_mutex_init(&(set->print_n_death), NULL);
}

void	destroy_mutex(t_set *set)
{
	int	x;

	x = 0;
	while (x < set->nb_philo)
	{
		pthread_mutex_destroy(&(set->fork[x]));
		x++;
	}
	pthread_mutex_destroy(&(set->print_n_death));
}
