#include "philo.h"

int	check_death(double last_meal, t_set *set, t_philo *philo)
{
	double	time;

	pthread_mutex_lock(&set->print_n_death);
	time = diff_time(&set->start_time);
	if (set->philo_is_dead)
		return (1);
	if (death_calc(set, time, last_meal, philo->id))
		return (1);
	pthread_mutex_unlock(&set->print_n_death);
	return (0);
}

int	death_calc(t_set *set, float time, float last_meal, int philo)
{
	if (time - (last_meal) > set->time_to_die)
	{
		print_timestamp(set, 4, diff_time(&set->start_time), philo);
		set->philo_is_dead = 1;
		return (1);
	}
	return (0);
}

void	print_timestamp(t_set *set, int control, double time, int philo_id)
{
	if (set->philo_is_dead)
		return ;
	if (control == 0)
	{
		printf("%.f %d has taken a fork\n", time, philo_id);
		printf("%.f %d has taken a fork\n", time, philo_id);
	}
	else if (control == 1)
		printf("%.f %d is eating\n", time, philo_id);
	else if (control == 2)
		printf("%.f %d is sleeping\n", time, philo_id);
	else if (control == 3)
		printf("%.f %d is thinking\n", time, philo_id);
	else if (control == 4)
		printf("%.f %d died\n", time, philo_id);
}

double	diff_time(struct timeval *start_time)
{
	double			diff_time;
	struct timeval	end_time;

	gettimeofday(&end_time, NULL);
	diff_time = (end_time.tv_sec - start_time->tv_sec) * 1000.0;
	diff_time += (end_time.tv_usec - start_time->tv_usec) / 1000.0;
	return (diff_time);
}

int	check_arg(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 12)
			return (1);
		j = 0;
		while (argv[i][j])
		{
			if (ft_isdigit((int)argv[i][j]) == 0)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
