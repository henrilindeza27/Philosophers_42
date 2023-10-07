/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 10:17:18 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/07 14:55:15 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

long	ft_atoi(char *str)
{
	long	i;
	long	res;
	int		sign;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (sign * res);
}

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		ft_error("Error, getting time\n");
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	destroy_all(t_geral *geral)
{
	int	i;

	i = -1;
	while (++i < geral->nbr_of_philos)
		pthread_join(geral->philos[i].thread, NULL);
	pthread_mutex_destroy(&geral->write);
	pthread_mutex_destroy(&geral->w8);
	i = -1;
	while (++i < geral->nbr_of_philos)
		pthread_mutex_destroy(&geral->forks[i]);
	free(geral->philos);
	free(geral->forks);
}

void	print_message(size_t time, char *str, t_philo *philo)
{
	size_t	time_now;

	pthread_mutex_lock(&philo->p_geral->write);
	time_now = get_time() - time;
	printf("%zu %d %s\n", time_now, philo->id, str);
	pthread_mutex_unlock(&philo->p_geral->write);
}

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		lock_left_fork(philo);
		lock_right_fork(philo);
	}
	else
	{
		lock_right_fork(philo);
		lock_left_fork(philo);
	}
}
