/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlindeza <hlindeza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 16:11:29 by hlindeza          #+#    #+#             */
/*   Updated: 2023/10/11 00:57:23 by hlindeza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosopher.h"

long	ft_atoi(char *str)
{
	long	i;
	long	res;
	int		sign;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
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

	if (gettimeofday(&time, NULL))
		return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	destroy_all(t_geral *geral)
{
	int	i;

	i = -1;
	while (++i < geral->nbr_of_philos)
		pthread_join(geral->philos[i].thread, 0);
	i = -1;
	while (++i < geral->nbr_of_philos)
		pthread_mutex_destroy(&geral->forks[i]);
	if (geral->locked)
		pthread_mutex_unlock(&geral->write);
	pthread_mutex_destroy(&geral->w8);
	pthread_mutex_destroy(&geral->write);
	pthread_mutex_destroy(&geral->eating);
	free(geral->forks);
	free(geral->philos);
}

void	ft_usleep(size_t time)
{
	size_t	st;

	st = get_time();
	while ((get_time() - st) < time)
	{
		usleep(time / 10);
	}
}

void	print_message(char *str, t_philo *philo, int f)
{
	size_t	time;

	if (!check_flag(philo->geral))
		return ;
	pthread_mutex_lock(&philo->geral->write);
	time = get_time();
	printf("%zu %d %s\n", time - philo->geral->start_time, philo->id, str);
	if (f)
		pthread_mutex_unlock(&philo->geral->write);
	else
		philo->geral->locked = 1;
}
