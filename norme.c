#include "philo.h"

int	norme_func(double time, t_set *set, t_philo *philo)
{
	pthread_mutex_lock(&set->print_n_death);
	print_timestamp(set, 0, time, philo->id);
	pthread_mutex_unlock(&set->print_n_death);
	return (0);
}
