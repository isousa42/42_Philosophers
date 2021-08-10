#include "philo.h"

int    check_death(double time, double last_meal, t_set *set, t_philo *philo)
{
    time = diff_time(&set->start_time);
	if(set->philo_is_dead)
		return (1);
    else if (death_calc((int)time, (int)last_meal, set->time_to_die))
    {
		
        pthread_mutex_lock(&set->print_n_death);
		if(set->philo_is_dead)
		{
        	pthread_mutex_unlock(&set->print_n_death);
			return (1);
		}
		set->philo_is_dead = 1;
        print_timestamp(4, diff_time(&set->start_time), philo->id);
        pthread_mutex_unlock(&set->print_n_death);
		return(1);
    }
	else
		return (0);
}

int death_calc(int time, int last_meal, int time_to_die)
{
    if (time - (last_meal) > time_to_die)
        return (1);
    return (0);
}

void	print_timestamp(int control, double time, int philo_id)
{
	if (control == 0)
		printf("%.3f %d has taken a fork\n", time, philo_id);
	else if (control == 1)
		printf("%.3f %d is eating\n", time, philo_id);
	else if (control == 2)
		printf("%.3f %d is sleeping\n", time, philo_id);
	else if (control == 3)
		printf("%.3f %d is thinking\n", time, philo_id);
	else if (control == 4)
		printf("%.3f %d died\n", time, philo_id);
}

double diff_time(struct timeval *start_time)
{
    double diff_time;
	struct timeval end_time;

	gettimeofday(&end_time, NULL);
    diff_time = (end_time.tv_sec - start_time->tv_sec) * 1000.0;
    diff_time += (end_time.tv_usec - start_time->tv_usec) / 1000.0;
    
    return (diff_time);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	num;

	sign = 1;
	num = 0;
	while ((*str == 32) || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45)
	{
		sign *= -1;
		str++;
	}
	else if (*str == 43)
		str++;
	while (*str >= 48 && *str <= 57)
	{
		num = num * 10;
		num += (sign * (*(str++) - '0'));
		if (num > 2147483647)
			return (-1);
		if (num < -2147483648)
			return (0);
	}
	return (num);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int check_arg(char **argv)
{
    int i;
    int j;

    i = 1;
    while (argv[i])
    {
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

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
