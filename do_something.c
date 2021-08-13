#include "philo.h"

int	grab_forks(t_set *set, t_philo *philo, int fork_left, int fork_right)
{
	if (check_death(diff_time(&set->start_time), philo->last_meal, set, philo))
		return (1);
	if (philo->id % 2)
	{
		usleep(500);
		pthread_mutex_lock(&set->fork[fork_left]);
		pthread_mutex_lock(&set->fork[fork_right]);
	}
	else
	{
		usleep(200);
		pthread_mutex_lock(&set->fork[fork_right]);
		pthread_mutex_lock(&set->fork[fork_left]);
	}
	if (check_death(diff_time(&set->start_time), philo->last_meal, set, philo))
	{
		pthread_mutex_unlock(&set->fork[fork_left]);
		pthread_mutex_unlock(&set->fork[fork_right]);
		return (1);
	}
	pthread_mutex_lock(&set->print_n_death);
	print_timestamp(0, diff_time(&set->start_time), philo->id);
	pthread_mutex_unlock(&set->print_n_death);
	return (0);
}

int	eat_spaghetti(t_set *set, t_philo *philo, int fork_left, int fork_right)
{
	if (check_death(diff_time(&set->start_time), philo->last_meal, set, philo))
		return (1);
	pthread_mutex_lock(&set->print_n_death);
	philo->last_meal = diff_time(&set->start_time);
	print_timestamp(1, philo->last_meal, philo->id);
	pthread_mutex_unlock(&set->print_n_death);
	usleep(set->time_to_eat * 1000);
	philo->meals--;
	if (check_death(diff_time(&set->start_time), philo->last_meal, set, philo))
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
	if (check_death(diff_time(&set->start_time), philo->last_meal, set, philo))
		return (1);
	return (0);
}

int	go_sleep(t_set *set, t_philo *philo)
{
	if (check_death(diff_time(&set->start_time), philo->last_meal, set, philo))
		return (1);
	pthread_mutex_lock(&set->print_n_death);
	print_timestamp(2, diff_time(&set->start_time), philo->id);
	pthread_mutex_unlock(&set->print_n_death);
	usleep(set->time_to_sleep * 1000);
	if (check_death(diff_time(&set->start_time), philo->last_meal, set, philo))
		return (1);
	return (0);
}

int	go_think(t_set *set, t_philo *philo)
{
	if (check_death(diff_time(&set->start_time), philo->last_meal, set, philo))
		return (1);
	pthread_mutex_lock(&set->print_n_death);
	print_timestamp(3, diff_time(&set->start_time), philo->id);
	pthread_mutex_unlock(&set->print_n_death);
	return (0);
}
