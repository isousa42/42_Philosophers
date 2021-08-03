#include "philo.h"

double dif_time()
{
    double dif_time;
	struct timeval time1;

	
    dif_time = (end->tv_sec - start->tv_sec) * 1000.0;
    dif_time += (end->tv_usec - start->tv_usec) / 1000.0;
    
    return (dif_time);
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
