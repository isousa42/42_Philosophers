#include "philo.h"

int	grab_forks(t_set *set, t_philo *philo, int fork_left, int fork_right)
{
	double	time;

	if (philo->id % 2 && !set->philo_is_dead)
	{
		pthread_mutex_lock(&set->fork[fork_left]);
		pthread_mutex_lock(&set->fork[fork_right]);
		time = diff_time(&set->start_time);
	}
	else if (!set->philo_is_dead)
	{
		pthread_mutex_lock(&set->fork[fork_right]);
		pthread_mutex_lock(&set->fork[fork_left]);
		time = diff_time(&set->start_time);
	}
	if (check_death(philo->last_meal, set, philo))
	{
		pthread_mutex_unlock(&set->fork[fork_left]);
		pthread_mutex_unlock(&set->fork[fork_right]);
		return (1);
	}
	norme_func(time, set, philo);
	return (0);
}

int	eat_spaghetti(t_set *set, t_philo *philo, int fork_left, int fork_right)
{
	if (check_death(philo->last_meal, set, philo) || set->philo_is_dead)
		return (1);
	pthread_mutex_lock(&set->print_n_death);
	philo->last_meal = diff_time(&set->start_time);
	print_timestamp(set, 1, philo->last_meal, philo->id);
	pthread_mutex_unlock(&set->print_n_death);
	while (diff_time(&set->start_time) - philo->last_meal < set->time_to_eat)
	{
		if (check_death(philo->last_meal, set, philo) || set->philo_is_dead)
			return (1);
	}
	philo->meals--;
	if (check_death(philo->last_meal, set, philo))
	{
		pthread_mutex_unlock(&set->fork[fork_left]);
		pthread_mutex_unlock(&set->fork[fork_right]);
		return (1);
	}
	return (0);
}

int	drop_forks(t_set *set, int fork_left, int fork_right, t_philo *philo)
{
	pthread_mutex_unlock(&set->fork[fork_left]);
	pthread_mutex_unlock(&set->fork[fork_right]);
	if (check_death(philo->last_meal, set, philo) || set->philo_is_dead)
		return (1);
	return (0);
}

int	go_sleep(t_set *set, t_philo *philo)
{
	double	start_sleep;

	if (check_death(philo->last_meal, set, philo) || set->philo_is_dead)
		return (1);
	pthread_mutex_lock(&set->print_n_death);
	print_timestamp(set, 2, diff_time(&set->start_time), philo->id);
	pthread_mutex_unlock(&set->print_n_death);
	start_sleep = diff_time(&set->start_time);
	while (diff_time(&set->start_time) - start_sleep < set->time_to_sleep)
	{
		if (check_death(philo->last_meal, set, philo) || set->philo_is_dead)
			return (1);
	}
	if (check_death(philo->last_meal, set, philo) || set->philo_is_dead)
		return (1);
	return (0);
}

int	go_think(t_set *set, t_philo *philo)
{
	if (check_death(philo->last_meal, set, philo) || set->philo_is_dead)
		return (1);
	pthread_mutex_lock(&set->print_n_death);
	print_timestamp(set, 3, diff_time(&set->start_time), philo->id);
	pthread_mutex_unlock(&set->print_n_death);
	if (check_death(philo->last_meal, set, philo) || set->philo_is_dead)
		return (1);
	return (0);
}
